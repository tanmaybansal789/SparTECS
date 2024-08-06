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

    class BasePool {
    public:
        virtual ~BasePool() = default;
        virtual void remove(Entity entity) = 0;
        virtual bool has(Entity entity) const = 0;
    };

    template <typename Component>
    class Pool : public BasePool{
    public:
        Pool();

        Component& add(Entity entity, Component component);
        void remove(Entity entity) override;
        Component& get(Entity entity);
        bool has(Entity entity) const override;

    private:
        std::vector<Component> dense;
        std::vector<size_t> sparse;
    };

} // namespace SparTECS

#include "Pool.tpp"

#endif //POOL_H
