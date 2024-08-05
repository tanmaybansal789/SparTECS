//
// Created by Tanmay Bansal on 04/08/2024.
//

#ifndef EVENTMANAGER_TPP
#define EVENTMANAGER_TPP

namespace SparTECS {

    inline EventManager::EventManager() : nextListenerId(0) {}

    template <typename Event>
    EventManager::ListenerId EventManager::addListener(const Listener<Event>& listener) {
        auto eventId = getEventId<Event>();
        eventListeners.emplace(eventId, std::make_pair(nextListenerId, [listener](const void* baseEvent) {
            listener(*static_cast<const Event*>(baseEvent));
        }));
        return nextListenerId++;
    }

    template <typename Event>
    void EventManager::emit(const Event& event) {
        auto eventId = getEventId<Event>();
        auto range = eventListeners.equal_range(eventId);
        for (auto it = range.first; it != range.second; ++it) {
            it->second.second(&event);
        }
    }

    template <typename Event>
    void EventManager::removeListener(ListenerId listenerId) {
        for (auto it = eventListeners.begin(); it != eventListeners.end(); ) {
            if (it->second.first == listenerId) {
                it = eventListeners.erase(it);
            } else {
                ++it;
            }
        }
    }

    template <typename Event>
    EventManager::EventId EventManager::getEventId() {
        static const EventId id = nextEventId++;
        return id;
    }

} // namespace SparTECS

#endif //EVENTMANAGER_TPP
