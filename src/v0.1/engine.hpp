#pragma once

#include <array>
#include <memory>

#include "common.hpp"
// #include "messages.hpp"
#include "events.hpp"

namespace common_ns {

// TO-DO : desc + implementation

// TO-DO : desc + implementation
class Engine {
public:
  using queue_t = EventQueue<MAX_EVENT_QUEUE_SIZE>;

  Engine(std::shared_ptr<queue_t> event_queue_ptr);

  /*
    Constantly checks Event Queue for new events to execute
   */
  le_return_t run();
  le_return_t addEvent(const Event &event);
  le_return_t clearQueue();

protected:
  std::shared_ptr<queue_t> m_event_queue_ptr;
};

} // namespace common_ns