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
    class BaseGroup {
    public:
        virtual ~BaseGroup() = default;
        virtual void addEntity(Entity entity) = 0;
        virtual void removeEntity(Entity entity) = 0;
    };

    template <typename... Components>
    class Group : public BaseGroup {
    public:
        Group() = default;

        void addEntity(Entity entity) override;
        void removeEntity(Entity entity) override;

        std::unordered_set<Entity>& getEntities();
    private:
        std::unordered_set<Entity> entities;
    };
}

#include "Group.tpp"

#endif //GROUP_H
