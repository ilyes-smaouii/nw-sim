# Roadmap/things to work on
- Simulation engine
  - Scheduler ?
  - Event format and functionality to be specified
  - ?
  - Messaging protocol, adaptability to each protocol/Entity
- [TBC]

# Personal notes
- Should be as modular as possible
  - If a layer N module can work without depending on lower layers, this allows 
me to, say, start working on UDP without having to work on Ethernet/MAC/other
first.
- Layers obviously make assumptions on lower/other layers. So can protocols !
- Allow for debugging/research/introspection functionality. e.g. allow for artificial latency
- Roadmap, design choices, notes, big TO-DO's, etc. --> ?
- Use cases --> ?
- License ?
- entity_traits<> struct ?
- Dynamic traits ? (e.g. use an MTU that can change during runtime) --> for max code flexibility, need to use as many functions as possible (make it static/constexpr if needed)
- IP Entity wants to know its neighbors/network --> either contacts other entities through lower layers (ARP/other), or directly asks the handler
  - Maybe start out w/ predefined defaults, and later add flexibility ?
- Common API for all Protocol Entities, s.a. `handleMessage()` or something ? Or maybe make it all go through Handler, and Handler then dispatches to corresponding Protocol Entities ?
- \[\]

# Ideas/things to explore
- Impact of physical medium/other layers on applications
- Simple transmission, transmission w/ tracking of a few things
- Capabilities framework (protocol wise) (e.g. whether or not an entity is thread safe, or more specifically which functions are thread-safe ?)
- Automated abstraction of entities/layers --> program runs detailed simulation first, makes some specific measurements, and uses those measurements to run a simulation with a higher layer of abstraction (e.g. rate of packet loss, or latency distribution)
- Create custom protocols
- Using static methods vs. objects (probably depends on data reuse, considering memory/data is main differentiating factor between the two)
- Figure out types of capabilities/specs : protocol specs (functional POV), class specs (e.g. thread safety), etc.
- Associate each class in source code with a numbero/id/code
  - This later allows me to code for the specs/capabilities using both static and dynamic approaches, I think
- Event scheduler needs to be able to provide some guarantees on ordering
  - most straightforward, and possibly best solution --> process events in the same order they're added in
- Rather than keeping state in Protocol Entity classes themselves, use some sort of internal heap memory with maybe an internal map or something, and then just pass the corresponding state/pointer/address to the Protocol Entity method you're calling, so it can store relevant state data in there ? This probably works better with runtime-determined environments.
  - implies existence of addEntity() method for Handler/Environment
  - Requires implementation of custom memory allocation ?
- ?

# Ideas/things to explore for v0.1
- Add TTL ?
- Change gateway behavior for NwProtocol, to get closer to real networks, and allow for multiple hops