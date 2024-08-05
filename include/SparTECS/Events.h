//
// Created by Tanmay Bansal on 05/08/2024.
//

#ifndef EVENTS_H
#define EVENTS_H

#include "EventManager.h"

namespace SparTECS {
    namespace InternalEvents {
        struct EntityCreatedEvent {
            Entity entity;
        };

        struct EntityDestroyedEvent {
            Entity entity;
        };

        template <typename Component>
        struct ComponentAddedEvent {
            Entity entity;
        };

        template <typename Component>
        struct ComponentRemovedEvent {
            Entity entity;
        };
    } // namespace InternalEvents
} // namespace SparTECS

#endif //EVENTS_H
