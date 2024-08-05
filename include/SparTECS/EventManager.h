//
// Created by Tanmay Bansal on 04/08/2024.
//
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "Entity.h"

#include <unordered_map>
#include <vector>
#include <functional>

namespace SparTECS {

    class EventManager {
    public:
        using EventId = size_t;
        using ListenerId = size_t;

        template <typename Event>
        using Listener = std::function<void(const Event&)>;

        EventManager();

        template <typename Event>
        ListenerId addListener(const Listener<Event>& listener);

        template <typename Event>
        void emit(const Event& event);

        template <typename Event>
        void removeListener(ListenerId listenerId);

    private:
        template <typename Event>
        EventId getEventId();

        EventId nextEventId = 0;
        ListenerId nextListenerId = 0;
        std::unordered_multimap<EventId, std::pair<ListenerId, std::function<void(const void*)>>> eventListeners;
    };

} // namespace SparTECS

#include "EventManager.tpp"

#endif // EVENTMANAGER_H
