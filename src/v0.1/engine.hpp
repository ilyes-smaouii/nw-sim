#pragma once

#include "common.hpp"
// #include "messages.hpp"
#include "events.hpp"

#include <array>

namespace common_ns {

template <std::size_t MAX_QUEUE_SIZE> class EventQueue {
public:
  using event_t = Event;

  bool isEmpty() { return m_head == m_tail; }
  bool isFull() { return (m_tail + 1) % MAX_QUEUE_SIZE == m_head; }
  std::size_t getSize() {
    return (m_tail - m_head + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
  }

  bool enqueue(const event_t &event);
  event_t &pop();

protected:
  std::size_t m_head{0};
  std::size_t m_tail{0};
  std::array<event_t, MAX_QUEUE_SIZE> m_queue{};
};

class Engine {
public:
  using queue_t = EventQueue<1000>;

  Engine();

  return_t run();
  return_t addEvent(const Event &event);
  return_t clearQueue();

protected:
  queue_t m_event_queue{};
};

} // namespace common_ns