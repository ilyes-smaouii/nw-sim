#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

#include "common.hpp"
// #include "handler.hpp"
// #include "engine.hpp" // [alt 1]
#include "events.hpp"
#include "messages.hpp"

/*
  The idea, here, is to define two protocols, NwProtocol and DLProtocol
  that are very simple versions of a network and datalink protocols.
  NwProtocol takes care of routing data through a network of NwProtocol
  entities, and DLProtcol has to dis-assemble and re-assemble messages which it
  can send to other DLProtocol entities, as it has the constraint of a maximum
  packet size
  */

namespace common_ns {
class Handler;
}

namespace protocols {

namespace cns = common_ns;

constexpr std::size_t DEFAULT_DL_MAX_PACKET_SIZE{128};

/*
  DLProtocol is some sort of datalink protocol : there's a limit on to how
  much data a single DLProtocol packet can carry.
 */
// TO-DO : implement
template <std::size_t MAX_PACKET_SZ> class DLProtocol {
public:
  using address_t = std::uint32_t;
  using return_t = cns::le_return_t;

  static constexpr std::size_t MAX_PACKET_SIZE{MAX_PACKET_SZ};

  DLProtocol();

  /*
    Checks whether addr is a valid DLProtocol address
   */
  static bool isValidAddress(address_t const &addr); // TO-DO : implement

  /*
    Send message msg to destination dest, identified by its DLProtocol address
   */
  return_t sendMessage(std::shared_ptr<cns::Message> msg,
                       address_t const &dest); // TO-DO : implement

  /*
    Process received message
    Message payload data should contain sender and receiver address, so no need
    to specify an address in the function call
    Message received here is actually only a fragment, which the DLProtocol
    entity can use to re-assemble a message detined for the higher layer
    NwProtocol entity
  */
  return_t
  receiveMessage(std::shared_ptr<cns::Message> msg); // TO-DO : implement

protected:
  address_t m_addr{};
};

/*
  NwProtocol is some sort of IP-like protocol : each entity has an address,
  and messages get routed through other NwProtocol entities to reach their
  destination. Other than that, no particular constraints.
 */
// TO-DO : implement
class NwProtocol {
public:
  using address_t = std::uint32_t;
  using return_t = cns::le_return_t;
  using entity_id_t = cns::entity_id_t;
  using dl_protocol_t = DLProtocol<DEFAULT_DL_MAX_PACKET_SIZE>;
  using dl_address_t = dl_protocol_t::address_t;
  // TO-DO : make a choice here
  // using engine_t = cns::Engine;   // [alt 1]
  using handler_t = cns::Handler; // [alt 2]
  using event_t = cns::Event;
  using message_t = cns::Message;

  // TO-DO : clarify header content
  struct Header {
    /*
      Sender address first so an NwProtocol entity can, in relevant cases,
      transfert/route a message without needlessly reading the rest of the
      header/message
    */
    address_t sender_addr;
    address_t receiver_addr;
  };

  NwProtocol(/* std::shared_ptr<engine_t> engine_ptr, [alt 1] */ address_t const
                 &address,
             dl_address_t const &attached_dl_address); // TO-DO : implement

  return_t setDLEntity(entity_id_t entity_id);

  /*
    Checks whether addr is a valid NwProtocol address
   */
  static bool isValidAddress(address_t const &addr);

  /*
    Returns the gateway address for the given destination address. For v0.1,
    I'll just assume all networds are of type A.B.C.D/16, and that the gateway
    is always A.B.0.1
  */
  address_t getGateway(address_t const &dest) const;

  /*
    Returns corresponding DL address for a given Nw address
   */
  dl_address_t getDLAddress(address_t const &nw_address) const;

  /*
    Send message msg to destination dest, identified by its NwProtocol address
   */
  return_t sendMessage(std::shared_ptr<cns::Message> msg_ptr,
                       address_t const &dest); // TO-DO : implement

  /*
    Process received message
    Message payload data should contain sender and receiver address, so no need
    to specify an address in the function call
   */
  std::shared_ptr<cns::Message>
  receiveMessage(std::shared_ptr<cns::Message> msg_ptr); // TO-DO : implement

protected:
  entity_id_t m_entity_id{};
  address_t m_addr{};
  dl_address_t m_attached_dl_address{};
  entity_id_t m_dl_entity_id{};
  // std::shared_ptr<engine_t> m_engine_ptr{}; // [alt 1]
  std::shared_ptr<handler_t> m_handler_ptr{};
};

} // namespace protocols
