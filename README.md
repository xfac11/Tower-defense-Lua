Tower defense game made in C++ using Irrlicht 1.8.5 with Lua scripting.

The game is entirely made up with lua scripts and the C++ side is only used to expose functions to lua side. 

## Build using cmake and visual studio

1. Use cmake -S . -B build to configure.
2. cmake --build build -t tests to build it and then.
3. Open the solution file called TowerDefense.
4. Change the start up project to be the "app" project.
5. Press f5 to run it.
