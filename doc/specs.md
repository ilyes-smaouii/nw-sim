<!-- [TBC] -->
<!-- [TO-DO : write proper specs] -->

# Entities

## Protocol Entities
Classes representing various network protocols.
Contain knowledges of protocols, and retain state if deemed relevant/necessary.

## Handlers
Aggregates, combines and coordinates Protocol Entities.
Representation of the environment that contains the Protocol Entities.
Middleman between Simulation Engine and Protocol Entities; as thus, also serves as a sort of dispatcher.

## Simulation Engine
Receives Events from Handler/Protocol Entities, adds them to an internal queue, and executes them using internal Scheduler.

## Events
Commun unit of execution; typically involves a Protocol Entity or a Handler (the Receiver), and a Message.

## Messages
Contains data through wich Protocol Entities and Handlers can communicate.

# Typical program
1. Start Simulation Engine.
2. Initialize Handler/Environment.
3. Add/load and initialize Protocol Entities.
4. Trigger Events, themselves causing Messages to be processed by different Protocol Entites, through the Simulation Engine.