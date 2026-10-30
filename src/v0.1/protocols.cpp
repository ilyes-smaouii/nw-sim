#pragma once

#include <memory>

// #include "common.hpp"
// #include "messages.hpp"
#include "common.hpp"
#include "engine.hpp"  // [alt 1]
#include "handler.hpp" // [alt 2]
#include "messages.hpp"
#include "protocols.hpp"

namespace protocols {

namespace cns = common_ns;

NwProtocol::NwProtocol(/* std::shared_ptr<engine_t> engine_ptr, */
                       address_t const &address,
                       dl_address_t const &attached_dl_address)
    : /* m_engine_ptr(engine_ptr), */ m_addr{address},
      m_attached_dl_address(attached_dl_address) {
  // TO-DO : implement
}

NwProtocol::return_t NwProtocol::setDLEntity(entity_id_t entity_id) {
  m_dl_entity_id = entity_id;
  return cns::RETURN_CODE::SUCCESS;
}

bool NwProtocol::isValidAddress(address_t const &addr) {
  return (addr & 0xFFFF0000) > 0;
}

NwProtocol::address_t NwProtocol::getGateway(address_t const &dest) const {
  return (dest & 0xFFFF0000) | 0x00000001;
}

NwProtocol::return_t
NwProtocol::sendMessage(std::shared_ptr<cns::Message> msg_ptr,
                        address_t const &dest) {
  // TO-DO : finish implementation (metadata about DL entity, etc.)

  address_t const next_hop_addr = getGateway(dest);
  // std::size_t res_size = sizeof(Header) + msg_ptr->size();
  // auto res_msg_ptr = std::make_shared<cns::Message>(res_size);
  // res_msg_ptr->appendData(Header{m_addr, dest});
  // res_msg_ptr->appendDataFromMsg(
  //     *msg_ptr); // append original message payload data

  // [alt 1] [Engine]
  // dl_address_t dl_dest_address = getDLAddress(next_hop_addr);
  // TO-DO : fill out event with necessary data
  // return m_engine_ptr->addEvent(
  //     event); // add Event that will transmit message to the attached DL
  //     Entity
  // [alt 2] [Handler]
  std::size_t res_size = sizeof(next_hop_addr) + msg_ptr->size();
  auto res_msg = std::make_shared<cns::Message>(res_size);
  res_msg->appendData(next_hop_addr);
  res_msg->appendDataFromMsg(*msg_ptr);
  event_t event{event_t::EventType::SEND_MSG, res_msg};
  // TO-DO : fill out event with necessary data
  return m_handler_ptr->addEvent(
      m_entity_id,
      event); // add Event that will transmit message to the attached DL Entity
}

std::shared_ptr<cns::Message>
NwProtocol::receiveMessage(std::shared_ptr<cns::Message> msg_ptr) {
  // TO-DO : implement
  // sender addr | receiver addr | payload data
  auto header = reinterpret_cast<Header const *>(msg_ptr->data());
  address_t const &sender_addr = header->sender_addr;
  address_t const &receiver_addr = header->receiver_addr;
  if (receiver_addr != m_addr) [[unlikely]] { // TO-DO : unlikely ?
    address_t const next_hop = getGateway(receiver_addr);
    // Message not intended for this entity, drop it
    return {};
  }
  return {};
}

} // namespace protocols