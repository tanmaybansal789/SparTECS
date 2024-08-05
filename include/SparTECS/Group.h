//
// Created by Tanmay Bansal on 05/08/2024.
//

#ifndef GROUP_H
#define GROUP_H

#include "Entity.h"
#include "Context.h"

#include <unordered_set>
#include <iostream>

namespace SparTECS {
    template <typename... Components>
    class Group {
    public:
        Group() = default;

        void addEntity(Entity entity);
        void removeEntity(Entity entity);

        std::unordered_set<Entity>& getEntities();
    private:
        std::unordered_set<Entity> entities;
    };
}

#include "Group.tpp"

#endif //GROUP_H
