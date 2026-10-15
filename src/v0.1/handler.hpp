#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <utility>

#include "common.hpp"
#include "events.hpp"
#include "messages.hpp"
#include "protocols.hpp"

// #include "engine.hpp"

namespace common_ns {

constexpr std::size_t MAX_DL_PACKET_SIZE{64};

// Forward declaration ?
// TO-DO : check whether this should be here/what that's about
class Engine;

// TO-DO : desc + implementation
class Handler {
#define APPLY_ON_ALL_HANDLED_ENTITY_TYPES(X)                                   \
  X(1, protocols::NwProtocol) X(2, protocols::DLProtocol<MAX_DL_PACKET_SIZE>)
public:
#define DEF_PROTOCOL_TYPE(entity_type, protocol_t)                             \
  using protocol_t_##entity_type = protocol_t;
  APPLY_ON_ALL_HANDLED_ENTITY_TYPES(DEF_PROTOCOL_TYPE)
#undef X
  using event_t = Event;

  struct EntityInfo {
    std::weak_ptr<void *> m_entity_ptr;
    std::uint32_t m_entity_type;
  };

  Handler();

  std::pair<le_return_t, entity_id_t>
  addEntity(const protocol_t_1 &entity); // TO-DO : implement
  /*
    TO-DO : finish comment
   */
  template <typename... Args>
  std::pair<le_return_t, entity_id_t> emplaceEntity(Args &&...args) {
    // TO-DO : implement
  }
  le_return_t removeEntity(entity_id_t entity_id); // TO-DO : implement
  /*
  Handle Message from Entity
   */
  le_return_t handleMessage(entity_id_t entity_id,
                            const Message &msg); // TO-DO : implement
  /*
  Handle Event from Engine/Scheduler
   */
  le_return_t handleEvent(const event_t &event); // TO-DO : implement

protected:
  std::unordered_map<entity_id_t, EntityInfo> m_entities{};

#undef APPLY_ON_ALL_HANDLED_ENTITY_TYPES
};

} // namespace common_ns