# network-simulator
Multi-layer multi-purpose network simulating modules

## Intro/context
I just got the idea of trying to create a program that could help simulate networks on all levels
(physical, link, etc.), and created this repo in anticipation.\
If done right, I should be able to simulate for anything, and all protocols, with the
ability to controll all parameters.
It's mostly just an idea for now though, I don't know if I'll actually pursue it. If I do and the
standard protocols are too complex to implement - or if the specifications are not accessible
enough -, maybe I could try to create my own protocols.

## Purpose
Mostly for fun/curiosity/coding practice

## File tree
- `src/` : source code written for this project, for now all in C++
- `lib/` : right now only contains a reference to another repo for additional functionality/helper code
- `tests/` : source code related to testing, specifically (I'm considering moving it to `src/`, though)
- A `doc/` for non-code documents that can be read to help other people or myself approach the whole project. In that folder :
  - `journal.md` : a simple journal to keep a log of activity
  - `directions.md` : serves as directions for the project (ideas to explore, notes for future reference, maybe also a roadmap of sorts ?)
  - `specs.md` : specifications for classes/other things in code
- `README.md` : file containing an introduction to the project with some context, explanation of the purpose, etc.
- `.cland` and `.clang-format` : mostly for code formatting and linting
- `CMakeLists.txt` : CMake file for building