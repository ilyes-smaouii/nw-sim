#pragma once

#include "common.hpp"
#include "messages.hpp"

#include <array>
#include <cstdint>
#include <memory>

namespace common_ns {

// TO-DO : desc + implementation
// TO-DO : figure out universal spec for Events : should be suitable for
// entities transmitting both downwards and upwards, and all other uses

class Event {

public:
  using msg_t = Message;

  enum class EventType : std::uint32_t {
    DEFAULT = 0,
    SEND_MSG =
        1, // Layer N+1 wants to send/encode message, sends it through Layer N
    RECV_MSG = 2, // Layer N has received/decoded message, and transmits it to
                  // Layer N+1
  };

  struct Header {
    // entity_id_t m_originating_entity_id{}; // entity that created the Event
    EventType m_event_type{};
  };

  Event(/* entity_id_t const &originating_entity_id,  */ EventType event_type,
        std::shared_ptr<Message> msg);

  std::shared_ptr<msg_t> getMessage() const;
  EventType const &getEventType() const;

protected:
  Header m_header{};
  std::shared_ptr<msg_t> m_msg{};
};

template <std::size_t MAX_QUEUE_SIZE> class EventQueue {
public:
  using event_t = Event;

  EventQueue();
  
  bool isEmpty() { return m_head == m_tail; }
  bool isFull() { return (m_tail + 1) % MAX_QUEUE_SIZE == m_head; }
  std::size_t getSize() {
    return (m_tail - m_head + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
  }

  bool enqueue(const event_t &event) {
    ;
  }
  event_t &pop() {
    // TO-DO : implement
  }

protected:
  std::size_t m_head{0};
  std::size_t m_tail{0};
  std::array<event_t, MAX_QUEUE_SIZE> m_queue{};
};

} // namespace common_ns