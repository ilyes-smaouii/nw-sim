#include <memory>

// #include "common.hpp"
#include "events.hpp"
#include "messages.hpp"

namespace common_ns {

Event::Event(
    /* entity_id_t const &originating_entity_id, */ EventType event_type,
    std::shared_ptr<Message> msg)
    : m_header(/* originating_entity_id ,*/ event_type), m_msg(msg) {}

std::shared_ptr<Event::msg_t> Event::getMessage() const { return m_msg; }

Event::EventType const& Event::getEventType() const { return m_header.m_event_type; }

} // namespace common_ns