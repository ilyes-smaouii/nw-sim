#include <iostream>

#include "common.hpp"
#include "engine.hpp"

namespace common_ns {

Engine::Engine() : m_event_queue() {}

le_return_t Engine::run() {
  while (true) {
    if (!m_event_queue.isEmpty()) {
      Event &event = m_event_queue.pop();
      // Process the event here
      auto &entity_id = event.getEntityId();
      auto &msg = event.getMessage();
      std::cout << "Processing event for entity ID: " << entity_id << std::endl;
      std::cout << "Message: " << msg.toString() << std::endl;
    }
  }
}

} // namespace common_ns