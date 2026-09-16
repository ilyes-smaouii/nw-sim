#pragma once

#include "common.hpp"
#include "events.hpp"
#include "messages.hpp"
#include "protocols.hpp"

// #include "engine.hpp"

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <utility>

namespace common_ns {

class Engine;

class Handler {
#define APPLY_ON_ALL_HANDLED_ENTITY_TYPES(X)                                   \
  X(1, protocols::ProtocolA) X(2, protocols::ProtocolB)
public:
#define X(entity_type, protocol_t) using protocol_t_##entity_type = protocol_t;
  APPLY_ON_ALL_HANDLED_ENTITY_TYPES(X)
#undef X
  using event_t = Event;

  struct EntityInfo {
    std::weak_ptr<void *> m_entity_ptr;
    std::uint32_t m_entity_type;
  };

  Handler();

  std::pair<return_t, entity_id_t> addEntity(const protocol_t_1 &entity);
  template <typename... Args>
  std::pair<return_t, entity_id_t> emplaceEntity(Args &&...args) {
    // TO-DO : implement
  }
  return_t removeEntity(entity_id_t entity_id);
  /*
  Handle Message from Entity
   */
  return_t handleMessage(entity_id_t entity_id, const Message &msg);
  /*
  Handle Event from Engine/Scheduler
   */
  return_t handleEvent(const event_t &event);

protected:
  std::unordered_map<entity_id_t, EntityInfo> m_entities{};

#undef APPLY_ON_ALL_HANDLED_ENTITY_TYPES
};

} // namespace common_ns