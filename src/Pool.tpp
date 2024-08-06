//
// Created by Tanmay Bansal on 04/08/2024.
//

#ifndef POOL_TPP
#define POOL_TPP

namespace SparTECS {

    template <typename T>
    Pool<T>::Pool() {
        sparse.resize(INDEX_MASK + 1, NULL_SPARSE_INDEX);
    }

    template <typename T>
    T& Pool<T>::add(Entity entity, T component) {
        size_t index = getIndex(entity);
        if (index >= sparse.size()) {
            sparse.resize(index + 1, NULL_SPARSE_INDEX);
        }
        dense.push_back(component);
        sparse[index] = dense.size() - 1;
        return dense.back();
    }

    template <typename Component>
    void Pool<Component>::remove(Entity entity) {
        size_t index = sparse[getIndex(entity)];
        dense[index] = dense.back();
        dense.pop_back();
        sparse[getIndex(entity)] = NULL_SPARSE_INDEX;
    }

    template <typename Component>
    Component& Pool<Component>::get(Entity entity) {
        return dense[sparse[getIndex(entity)]];
    }

    template <typename Component>
    bool Pool<Component>::has(Entity entity) const {
        return sparse[getIndex(entity)] != NULL_SPARSE_INDEX;
    }

} // namespace SparTECS

#endif //POOL_TPP
