#include <iostream>

#include "common.hpp"
#include "engine.hpp"

namespace common_ns {

Engine::Engine(std::shared_ptr<queue_t> event_queue_ptr)
    : m_event_queue_ptr(event_queue_ptr) {}

le_return_t Engine::run() {
  while (true) {
    if (!m_event_queue_ptr->isEmpty()) {
      Event &event = m_event_queue_ptr->pop();
      // Process the event here
      // auto &entity_id = event.getEntityId();
      auto msg = event.getMessage();
      // std::cout << "Processing event for entity ID: " << entity_id <<
      // std::endl;
      std::cout << "Message: " << msg->toString() << std::endl;
    }
  }
}

} // namespace common_ns