<!-- [TBC] -->
<!-- [TO-DO : write proper specs] -->

# Entities

## Protocol Entities
Classes representing various network protocols;
Contain knowledges of protocols, and retain state if deemed relevant/necessary;

## Handlers
Aggregates, combines and coordinates Protocol Entities;
Representation of the environment that contains the Protocol Entities;

## Simulation Engine
Receives Events from Handler/Protocol Entities, adds them to an internal queue, and executes them using internal Scheduler;

## Events
Commun unit of execution; typically involves a Protocol Entity or a Handler (the Receiver), and a Message;

## Messages
Contains data through wich Protocol Entities and Handlers can communicate;4

# Typical program
Has a single Message queue where Messages can be produced and consumed - or their payload, at least.
Starts Simulation Engine, 