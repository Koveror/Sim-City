# Sim-City-1 Documentation

## Overview
Our software, as the name suggests, is a traffic simulator that models a small city with a map of streets and vehicles that go along the streets.

Each vehicle will have a source building and a destination building in the city map where they are travelling to; Pathfinding is done using Dijkstra's algorithm. Sources and destinations are randomly generated in the city map, and the sources has a exponential distribution for the frequency at which cars will be leaving. The rate can be also modified via user interface.

The roads have traffic lights at intersections (if more than 3 streets intersecting) to help cars avoid collisions.

The user interface allows interactive addition and removal of traffic sources/destinations and streets.

Users can save and load their created maps. Currently the map size is limited to 16x12, and load functions excepts the maps to be the exact size.

## Software structure
In this section, we will have a detailed look on our software structure.

### Class structure
Our class structure roughly follows the initial architecture described in the project plan. As stated in the project plan, the software uses `SFML 2.3.2` graphics (external) library

We've made some small changes, and currently our class structure can be figured out from the software architecture:
![architecture](doc/architecture.png)

#### main
- UI
- time simulation
- calls graph

#### graph
- stores vertices and their relations as edges
- stores vehicles and updates them
- uses Dijkstra algorithm to find route for cars

#### vertex
- represents one tile in game world and a vertex in graph (stores tile information)
- stores traffic light information, with the help from tools

#### edge
- represents relation between two vertices
- stores also weight

#### vehicle
- stores size, position, destination and route of single vehicle
- move vehicle when `move` function is called

#### texturemanager
- handles loading textures for tile types (grass, road, building).

#### tools
- additional enumerations and class Pos to help other classes and their functions.

## Instructions for building and using the software
To run Sim-city-1, simply navigate to the project root directory using your unix terminal and then run `make run-main` command. This command will compile the source files and make an executable called **sim-city-1**. The command will also run the executable. The executable can be found in the src directory. The program can be run again from there or you can simply use the `make run-main` command again. You can clean the src directory using the `make clean` command, which will remove object files and executables from the src directory.

To use our software you have to have SFML library installed on your machine.

### How to use the software
Once the software is running, the console will print out a welcome message. You can press **H** to have all available commands printed out to the console. Detailed instructions are also below this paragraph:

To add tiles on map, first choose which kind of tile you want to add using keyboard. Pressing **R** adds roads, **B** buildings and **G** grass (empty tile). When you have map ready and want cars to start spawning press **V**.

Press **T** to toggle automatic traffic light control. You can also use right mouse button to manually switch traffic lights in any intersection. Letter **O** changes the rate that automatic traffic light control changes lights and **I** changes the rate that buildings spawn vehicles.

Game speed can be changed using numbers **1** (1x), **2** (4x) and **3** (8x).

To save your current map psess **S** and follow instructions on the console. To load press **L** and also follow instructions on the console.

### Use of C++ features
In this section we will quickly go through of use of C++ features that were required in the project.

#### Containers
For containers, we used mainly vector standard containers. Vectors provide random access, which is very useful, and our code does not require too much memory. List container was also used in Graph when storing vehicles. In addition to typical std vector and list, we used std priority queue for Dijkstra's algorithm for vehicle pathfinding. Priority queue is required in order to get Dijkstra's algorithm to work slightly more efficient than using other methods.

#### Smart Pointers
We use smart pointers for storing vehicles as our graph class stores vehicles. With shared ptr, we don't have to manually manage memory, which is notorious in C++.

#### Exception handling
Exception handling is used when user wants to change the rates that 1) change lights and 2) buildings spawn vehicles, as both of these require user input. The try catch loop ensures that if user enters invalid argument or invalid value, the software throws an error, forcing to retry, or type -1 to cancel the operation. Exception handling is also used when the user wants to load a map.

#### Rule of three
Rule of three is enforced in every part of software: For example, see vehicle.cpp.

#### Dynamic binding and virtual classes/functions
Vehicle class uses dynamic binding, as we have derived classes for vehicles. For example, virtual destructor is required for base class Vehicle.

### Known bugs
- Currently vehicles go through each other; in other words, collision detection doesn't work properly.
- Different vehicles do not have textures, the only aspect to distinguish the difference is the vehicle size.

## Testing
Due to scheduling problems, unit testing was done using <cassert> and in a separate test function in main.cpp, which can be called while running the main program (instructions can be found in main.cpp). Unit testing was used to ensure that individual functions work appropriately.
Unfortunately, there was no time to set third-party unit testing C++ frameworks such as google test or CPPunit. However, as our software evolved from the beginning to the end, debugging was very intensive as the codes was being developed.

In addition to unit testing, Valgrind was used to check for memory leaks. We concluded that only SFML parts are leaking memory, and only 10 bytes in 1 block was definitely lost. Rest are still reachable. Below is the latest valgrind with `--leak-check=full`.

```
==18565== HEAP SUMMARY:
==18565==     in use at exit: 143,697 bytes in 1,309 blocks
==18565==   total heap usage: 1,751 allocs, 442 frees, 334,295 bytes allocated
==18565== 
==18565== 10 bytes in 1 blocks are definitely lost in loss record 63 of 216
==18565==    at 0x4C2DB8F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==18565==    by 0x50C9489: strdup (strdup.c:42)
==18565==    by 0x418328: xstrdup (in /usr/bin/make)
==18565==    by 0x423FC6: target_environment (in /usr/bin/make)
==18565==    by 0x4148D4: ??? (in /usr/bin/make)
==18565==    by 0x4152B3: ??? (in /usr/bin/make)
==18565==    by 0x415BD2: new_job (in /usr/bin/make)
==18565==    by 0x420D9E: ??? (in /usr/bin/make)
==18565==    by 0x4210AE: update_goal_chain (in /usr/bin/make)
==18565==    by 0x407780: main (in /usr/bin/make)
==18565== 
==18565== LEAK SUMMARY:
==18565==    definitely lost: 10 bytes in 1 blocks
==18565==    indirectly lost: 0 bytes in 0 blocks
==18565==      possibly lost: 0 bytes in 0 blocks
==18565==    still reachable: 143,687 bytes in 1,308 blocks
==18565==         suppressed: 0 bytes in 0 blocks
==18565== Reachable blocks (those to which a pointer was found) are not shown.
==18565== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==18565== 
==18565== For counts of detected and suppressed errors, rerun with: -v
==18565== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

## Work log
