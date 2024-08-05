//
// Created by Tanmay Bansal on 04/08/2024.
//

#ifndef CONTEXT_TPP
#define CONTEXT_TPP

#include "Events.h"

#include <iostream>

namespace SparTECS {

    inline Entity Context::createEntity() {

        Entity entity;
        if (available) {

            auto nextIndex = getIndex(next);
            auto nextVersion = getVersion(next);

            auto entityIndex = getIndex(entities[nextIndex]);
            auto entityVersion = getVersion(entities[nextIndex]);

            entity = buildEntity(nextIndex, entityVersion);

            entities[nextIndex] = entity;
            next = buildEntity(entityIndex, nextVersion);

            --available;
        } else {
            entity = buildEntity(entities.size(), 0);


            entities.push_back(entity);
        }

        eventManager.emit<InternalEvents::EntityCreatedEvent>({entity});
        return entity;
    }

    inline bool Context::entityExists(Entity entity) const {
        return getIndex(entity) < entities.size() && getVersion(entity) == getVersion(entities[getIndex(entity)]);
    }

    inline void Context::destroyEntity(Entity entity) {
        auto entityIndex = getIndex(entity);
        auto entityVersion = getVersion(entity);
        auto nextIndex = getIndex(next);
        auto nextVersion = getVersion(next);

        // Swap the indices of next and entity, and increment the version of the entity
        entities[entityIndex] = buildEntity(nextIndex, entityVersion + 1);
        next = buildEntity(entityIndex, nextVersion);

        ++available;

        eventManager.emit<InternalEvents::EntityDestroyedEvent>({entity});
    }

    template <typename Component>
    Component& Context::addComponent(Entity entity, Component component) {
        Component& addedComponent = getPool<Component>().add(entity, component);
        eventManager.emit<InternalEvents::ComponentAddedEvent<Component>>({entity});
        return addedComponent;
    }

    template <typename Component>
    void Context::removeComponent(Entity entity) {
        getPool<Component>().remove(entity);
        eventManager.emit<InternalEvents::ComponentRemovedEvent<Component>>({entity});
    }

    template <typename Component>
    Component& Context::getComponent(Entity entity) {
        return getPool<Component>().get(entity);
    }

    template <typename Component>
    bool Context::hasComponent(Entity entity) const {
        return getPool<Component>().has(entity);
    }

    inline EventManager& Context::getEventManager() {
        return eventManager;
    }

    template <typename Component>
    Pool<Component>& Context::getPool() const {
        static Pool<Component> pool;
        return pool;
    }

    template <typename... Components>
    Group<Components...>& Context::initialiseGroup() {
        auto& group = getGroup<Components...>();

        // Add a listener for each ComponentAddedEvent for each component type
        (eventManager.addListener<InternalEvents::ComponentAddedEvent<Components>>([&group, this](const auto& event) {
            if ((this->hasComponent<Components>(event.entity) && ...)) {
                group.addEntity(event.entity);
            }
        }), ...);

        // Add a listener for each ComponentRemovedEvent for each component type
        (eventManager.addListener<InternalEvents::ComponentRemovedEvent<Components>>([&group](const auto& event) {
            group.removeEntity(event.entity);
        }), ...);

        // Add a listener for EntityDestroyedEvent
        eventManager.addListener<InternalEvents::EntityDestroyedEvent>([&group](const auto& event) {
            group.removeEntity(event.entity);
        });

        return group;
    }

    template<typename... Components>
    Group<Components...>& Context::getGroup() {
        static Group<Components...> group;
        return group;
    }
;

} // namespace SparTECS

#endif //CONTEXT_TPP