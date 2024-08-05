//
// Created by Tanmay Bansal on 04/08/2024.
//

#ifndef POOL_H
#define POOL_H

#include "Entity.h"

#include <vector>
#include <unordered_map>
#include <cassert>

namespace SparTECS {

    template <typename Component>
    class Pool {
    public:
        Pool();

        Component& add(Entity entity, Component component);
        void remove(Entity entity);
        Component& get(Entity entity);
        bool has(Entity entity) const;

    private:
        std::vector<Component> dense;
        std::vector<size_t> sparse;
    };

} // namespace SparTECS

#include "Pool.tpp"

#endif //POOL_H
