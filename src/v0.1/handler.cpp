#include <iostream>
#include <memory>

#include "common.hpp"
#include "events.hpp"
#include "handler.hpp"
#include "messages.hpp"
#include "protocols.hpp"

namespace common_ns {

// TO-DO : use helper Header classes for different types of messages

Handler::Handler(std::shared_ptr<queue_t> event_queue_ptr)
    : m_event_queue_ptr(event_queue_ptr) {};

le_return_t Handler::logMessage(std::shared_ptr<Message> msg_ptr) const {
  std::cout << "Received message :\n" << msg_ptr->toString() << std::endl;
  return RETURN_CODE::SUCCESS;
}

le_return_t Handler::addEvent(entity_id_t originating_entity_id,
                              const event_t &event) {
  // TO-DO : implement
  auto const &event_type = event.getEventType();
  auto entity_info_iter = m_entities.find(originating_entity_id);
  if (entity_info_iter == m_entities.end()) {
    return RETURN_CODE::FAILURE; // originating_entity_id not found in
                                 // m_entities
  }
  auto const &type_number = entity_info_iter->second.m_entity_type_number;
  if (isTypeMatchingTypeNumber<nw_protocol_t>(type_number)) {
    // TO-DO : finish implementing
    if (event_type == event_t::EventType::SEND_MSG) {
      auto nw_entity_info_iter = m_nw_entities.find(originating_entity_id);
      if (nw_entity_info_iter == m_nw_entities.end()) {
        return RETURN_CODE::FAILURE;
      }
      entity_id_t const &attached_dl_entity_id =
          nw_entity_info_iter->second.m_dl_entity_id;
      // TO-DO : extract next hop address
      auto msg_ptr = event.getMessage();
      auto next_hop_address = msg_ptr->getDataAs<nw_protocol_t::address_t>(0);
      auto nw_dest_entity_info_iter = m_nw_entities.find(originating_entity_id);
      if (nw_entity_info_iter == m_nw_entities.end()) {
        return RETURN_CODE::FAILURE;
      }
      entity_id_t const &attached_dest_dl_entity_id =
          nw_entity_info_iter->second.m_dl_entity_id;
      // sender DL address | dest DL address | original payload minus
      // (next_hop_address)
      std::size_t res_size = 2 * sizeof(dl_protocol_t::address_t) +
                             msg_ptr->size() - sizeof(nw_protocol_t);
      auto res_msg = std::make_shared<Message>(res_size);
      res_msg->appendData(attached_dl_entity_id);
      res_msg->appendData(attached_dest_dl_entity_id);
      res_msg->appendData(msg_ptr->data() + sizeof(nw_protocol_t::address_t),
                          msg_ptr->size() - sizeof(nw_protocol_t::address_t));
      m_event_queue_ptr->enqueue(Event(Event::EventType::SEND_MSG, res_msg));
    } else if (event_type == event_t::EventType::RECV_MSG) {
      // Message received by NwProtocol --> log it
      logMessage(event.getMessage());
    }
  } else if (isTypeMatchingTypeNumber<dl_protocol_t>(type_number)) {
    if (event_type == event_t::EventType::SEND_MSG) {
      ;
    };
  } else {
    return RETURN_CODE::FAILURE;
  }
  return RETURN_CODE::SUCCESS;
}

} // namespace common_ns