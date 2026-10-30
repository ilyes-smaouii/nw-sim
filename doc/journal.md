# 2025-08-18
Created the repo
# 2025-10-04
Started to think a bit about some approaches I could take on here.
\
Update : found out some projects with a similar premise already exist. Doesn't change much though,
this was mostly meant as project for personal learning and exploration.

# 2026-04-20
Starting up again

# 2026-04-24
Some ideas for use cases :
- \[L1-L7\] device communicating with another \[L1-L7\] device, with several [L3] devices in-between. Simple HTTP exchange should be enough.
  - Allows to test for everything, and particulary L3
  - Config files for L3 network topology ?
- Same or similar, but with at least one \[L1-L3\] pair somewhere in the middle, to experiment with changing network conditions (intereferences, etc.)
- Same or similar, but with at least one \[L1-L3\] pair somewhere in the middle, to experiment with man-in-the-middle attacks ?
- ?

# 2026-04-28
Still in early drafting staged, but it's starting to have some structure.
Added generic layer entities, MAC and IP addresses - well at least basic functionalities -, and some other stuff I guess.

# 2026-05-11
Haven't written here in a long time, but I've been writing some code, and mostly pondering about paradigm/architecture choices, and it's maybe not as straightforward as I initially expected. Mainly :
- Do the Entities I implement communicate directly with each other using designated functions, or do they pass messages via a Handler, which takes care of "connecting" the different Entities with each other, and dipatching messages properly ?
- Do I use the call chains/the call stack for propagating messages, or do I use some sort of event loop ?
- Do I make the program single threaded or multi-threaded ?
- What kind of Messages do different Entities use to transmit data ? Simple buffer whose data gets copied every time it's used ? Adaptable single buffer built with encapsulation in mind ? Some generic class which could add functionality above that of a simple memory buffer ?
- How much is determined at compile time vs. during runtime ?
- For genericity, do I rely more on `concept`s, or do I use base classes and inheritance ?
- How much genericity do I go for in the start before actually implementing my first use case ? (i.e. right balance between premature optimization and iterative approach)
- etc.
\
For example, the way things were going, `IPv4HandlerBase`'s `handleEncapuslatedMsg()`, which would be called from an `IPv4EntityBase`, would possibly process the messsage, and then go on and call another `IPv4EntityBase`'s `handleDecapsulatedMsg`, which would itself go back to calling the handler's `handleEncapuslatedMsg()` function, and so on and so forth. While relatively simple to implement, this would result in a growing call stack, which doesn't seem ideal. I'm thus now considering switching to some sort of event loop.
\
\
For now, this reasoning mostly happens in my mind, but it's starting to be a lot, and I should probably start to organize it written form, at least on paper or something.
\
Anyway, I started this project mostly with the intent of learning about different topics - software architecture, networking protocols, threading, etc. - , so as long as I learn something and make some progress, all these challenges are welcome.

# 2026-06-08
Another idea/thought I've had : should I keep the layers-oriented architecture, or switch to a more generic one ? \
Maybe make the `Handler` the entity that manages/checks interfaces rather than using concepts/other stuff in the rest of the code ?

# 2026-07-10
Currently reorganizing my files. \
Created a `doc/` folder to contain the journal, potentially a roadmap, some documentation and any such documents that are not actual code and can help approach the project. \
Created a distinct `journal.md` file for the journal and moved previous entries from `README.md` to that file. \

# 2026-08-01
Been doing some thinking on some general principles and architecture/design choices these days, and each thought just creates several new questions I don't have the answers to.
Some thoughts/leads to expand on :
- There should be classes/entities for each protocol. This entity should know about the corresponding protocol - say IP -, so it can process messages/data accordingly.
  - e.g. IPv4 Entity, MAC Entity, TCP Entity, etc.
- There should probably be an event scheduler somewhere, as that allows for much more flexibility.
- Not quite sure yet about whether Protocol Entities should be considered stateless or stateful. Maybe allow for both, and then have sort of specs/capabilities framework - analogous to `traits` in C++ - so code can account for both ?
  - an IP Entity class, for example, could be seen as stateful, as it can have a routing table/gateway config.
  - on the other hand, some data could be stored/managed by the Handler/Environment, and then just be passed on to the Protocol Entity methods on every call, though that kinda seems like cheating.
- There should be some sort of Handler/Environment objects that serve as sorts of orchestrator for messages, events, Protocol Entities, etc. Not sure whether they should be kept separate from event scheduling functionality, or if that should be part of the Handler/Environment functionality.
- Some things to keep in mind through all this : I'm trying to aim flexibility, maintainability/extendability, as well as traceability. Protocol Entities should probably remain as small as possible, and remain constrained to protocol functionality. The Handler/Environment can then take care of logging.
- Some thought should be put into event ordering and predictability. Say a Protocol Entity receives some data it's supposed to encode, but it needs to fragment it do so. It schedules a distinct event for each fragment, but if the scheduler doesn't guarantee to keep event order, the fragments could be processed in the wrong order. Maybe the scheduler should give some sort of its "clients" some sort of "keep order" option when they add events to the queue.
  - Or, you know, I could just make simple event scheduler that processes all events in the same order they were added in
- if I do make some sort of `traits`-like framework, maybe it should be mostly used by the Handler/Environment; seems like that's where the responsability for that functionality should be. At least regarding checks. The Protocol Entities should still be provide information on their respective traits. One way to do that would be to use templates, as with C++ `traits`.
  - Small issue if I want to make it a compile-time thing --> at some point, I'd like to be able to use config files to populate Environments with Protocol Entities, which means some information will only be known at runtime. This could be handled with if or switch blocks, but I don't know, that doesn't seem ideal. Maybe there's just no other way 🤷.
Anyway, I'll continue this later.

# 2026-09-09
Back on this project after a long break. I think I've spent too long trying to properly design the architecture and a good frame of work for this project, so I'll try to read my notes back to avoid missing on important stuff, and I'll try to actually write some code, so I can finally start iterating; if there are things I wanna change later on, and I have to rewrite things from scratch, I'll just rewrite them.
I've written some basic specifications to guide myself, I can improve them later.

# 2026-09-16
Adding a `roadmap.md` file to the `/doc` directory.
I think I got too held up on memory management and performance issues last time, I'll try to build some working features first, and I can improve those aspects later.
Update : wrote some code in header files, so v0.1 - what I decided to call this early proof of concept-type version - is starting to take form.

# 2026-10-30
Started writing some code, and the more progress I make, the more unforeseen issues I run into. \
Turns out even v0.1 is not as straightforward as I thought. Might need to take a step back and go back to abstract design/architecture before I go back to writing code. \
Anyway, at least it's starting to take some form, though there's probably still a long way before I get to a working v0.1 prototype. \
It's very messy and highly unefficient in how it handles most operations that pass data around, but that's kind of the point of v0.1 : start with a bad but working prototype, which can serve as a starting point for better versions.