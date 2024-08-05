#ifndef CONTEXT_H
#define CONTEXT_H

#include "Entity.h"
#include "EventManager.h"
#include "Pool.h"

#include <vector>
#include <stack>
#include <algorithm>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>

#include "Group.h"

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

        template <typename... Components>
        Group<Components...>& initialiseGroup();

        template <typename... Components>
        Group<Components...>& getGroup();

        EventManager& getEventManager();

    private:
        template <typename Component>
        Pool<Component>& getPool() const;

    private:
        std::vector<Entity> entities;
        Entity next = buildEntity(NULL_INDEX, NULL_VERSION);
        size_t available = 0;

        EventManager eventManager;
    };

} // namespace SparTECS

#include "Context.tpp"

#endif //CONTEXT_H