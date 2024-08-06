//
// Created by Tanmay Bansal on 04/08/2024.
//

#ifndef CONTEXT_H
#define CONTEXT_H

#include "Entity.h"
#include "EventManager.h"
#include "Pool.h"
#include "Group.h"

#include <unordered_map>
#include <vector>
#include <typeindex>

namespace SparTECS {
    class Context {
    public:
        Context() = default;

        Entity createEntity();
        bool entityExists(Entity entity) const;
        void destroyEntity(Entity entity);

        template <typename Component>
        Component& addComponent(Entity entity, Component component);

        template <typename Component>
        void removeComponent(Entity entity);

        template <typename Component>
        Component& getComponent(Entity entity);

        template <typename Component>
        bool hasComponent(Entity entity) const;

        EventManager& getEventManager();

        template <typename... Components>
        Group<Components...>& initialiseGroup();

        template <typename... Components>
        Group<Components...>& getGroup();

    private:
        std::vector<Entity> entities;
        Entity next;
        size_t available = 0;
        EventManager eventManager;

        std::unordered_map<std::type_index, std::unique_ptr<BasePool>> pools;
        std::unordered_map<std::type_index, std::unique_ptr<BaseGroup>> groups;

        template <typename Component>
        Pool<Component>& getPool();

        template <typename... Components>
        Group<Components...>& getGroupInternal();
    };
}

#include "Context.tpp"

#endif //CONTEXT_H