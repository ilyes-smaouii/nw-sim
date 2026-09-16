#pragma once

#include "common.hpp"
#include "messages.hpp"

#include <memory>

namespace common_ns {

class Event {

public:
  using msg_t = Message;

  entity_id_t const &getEntityId() const;
  msg_t const &getMessage() const;

protected:
  entity_id_t m_entity_id{};
  std::shared_ptr<msg_t> m_message{};
};

} // namespace common_ns