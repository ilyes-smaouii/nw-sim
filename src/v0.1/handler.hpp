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

constexpr std::size_t MAX_DL_PACKET_SIZE{protocols::DEFAULT_DL_MAX_PACKET_SIZE};

// Forward declaration ?
// TO-DO : check whether this should be here/what that's about
class Engine;

// TO-DO : desc + implementation

class Handler {
  using queue_t = EventQueue<MAX_EVENT_QUEUE_SIZE>;
  using nw_protocol_t = protocols::NwProtocol;
  using dl_protocol_t = protocols::DLProtocol<MAX_EVENT_QUEUE_SIZE>;
  
#define APPLY_ON_ALL_HANDLED_ENTITY_TYPES(X)                                   \
  X(1, nw_protocol_t) X(2, dl_protocol_t)
public:
#define DEF_PROTOCOL_TYPE(entity_type_number, protocol_t)                      \
  using protocol_t_##entity_type_number = protocol_t;
  APPLY_ON_ALL_HANDLED_ENTITY_TYPES(DEF_PROTOCOL_TYPE)
#undef DEF_PROTOCOL_TYPE
  using event_t = Event;

  template <typename T> std::uint32_t getTypeNumber();

#define DEFINE_ENTITY_TYPE(entity_type_number, protocol_t)                     \
  template <> std::uint32_t getTypeNumber<protocol_t>() {                      \
    return entity_type_number;                                                 \
  }
  APPLY_ON_ALL_HANDLED_ENTITY_TYPES(DEFINE_ENTITY_TYPE)
#undef DEFINE_ENTITY_TYPE

  template <typename T>
  constexpr bool isTypeMatchingTypeNumber(std::uint32_t type_number) {
    return (type_number == getTypeNumber<T>());
  };

  struct EntityInfo {
    std::weak_ptr<void *> m_entity_ptr;
    std::uint32_t m_entity_type_number;
  };

  struct NwEntityInfo {
    entity_id_t m_dl_entity_id{};
  };

  Handler(std::shared_ptr<queue_t> event_queue_ptr);

  le_return_t
  addAttachedEntities(nw_protocol_t const &nw_entity,
                      dl_protocol_t const
                          &dl_entity); // TO-DO : implement
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
  le_return_t logMessage(std::shared_ptr<Message> msg_ptr) const;
  /*
  Handle Event from Engine/Scheduler
   */
  le_return_t handleEvent(const event_t &event); // TO-DO : implement

  /*
    Add a new event
   */
  le_return_t addEvent(entity_id_t originating_entity_id,
                       const event_t &event); // TO-DO : implement

protected:
  std::unordered_map<entity_id_t, EntityInfo> m_entities{};
  std::unordered_map<entity_id_t, NwEntityInfo> m_nw_entities{};
  std::shared_ptr<queue_t> m_event_queue_ptr{};

#undef APPLY_ON_ALL_HANDLED_ENTITY_TYPES
};

} // namespace common_ns