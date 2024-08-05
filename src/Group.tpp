//
// Created by Tanmay Bansal on 05/08/2024.
//

#ifndef GROUP_TPP
#define GROUP_TPP

namespace SparTECS {

    template <typename... Components>
    void Group<Components...>::addEntity(Entity entity) {
        entities.insert(entity);
    }

    template <typename... Components>
    void Group<Components...>::removeEntity(Entity entity) {
        if (entities.contains(entity)) {
            entities.erase(entity);
        }
    }

    template <typename... Components>
    std::unordered_set<Entity>& Group<Components...>::getEntities() {
        return entities;
    }

}

#endif //GROUP_TPP
