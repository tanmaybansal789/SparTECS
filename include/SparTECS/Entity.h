//
// Created by Tanmay Bansal on 04/08/2024.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>
#include <limits>

namespace SparTECS {

    using Entity = uint32_t;

    constexpr uint32_t INDEX_MASK = std::numeric_limits<uint16_t>::max();
    constexpr uint32_t VERSION_SHIFT = 16;
    constexpr uint16_t NULL_INDEX = std::numeric_limits<uint16_t>::max();
    constexpr size_t NULL_SPARSE_INDEX = std::numeric_limits<size_t>::max();
    constexpr uint16_t NULL_VERSION = std::numeric_limits<uint16_t>::max();

    uint16_t getIndex(Entity entity);
    uint16_t getVersion(Entity entity);
    Entity buildEntity(uint16_t index, uint16_t version);
    bool isNullEntity(Entity entity);

} // namespace SparTECS

#endif //ENTITY_H
