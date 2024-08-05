//
// Created by Tanmay Bansal on 04/08/2024.
//

#include "Entity.h"

namespace SparTECS {

    uint16_t getIndex(Entity entity) {
        return static_cast<uint16_t>(entity & INDEX_MASK);
    }

    uint16_t getVersion(Entity entity) {
        return static_cast<uint16_t>((entity >> VERSION_SHIFT) & INDEX_MASK);
    }

    Entity buildEntity(uint16_t index, uint16_t version) {
        return (static_cast<Entity>(version) << VERSION_SHIFT) | index;
    }

    bool isNullEntity(Entity entity) {
        return getIndex(entity) == NULL_INDEX && getVersion(entity) == NULL_VERSION;
    }

} // namespace SparTECS