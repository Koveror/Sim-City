# Sim-City-1 Documentation

## Overview


## Software structure

### Class structure
Our class structure roughly follows the initial architecture described in the project plan. We've made some small changes, and currently our class strucutre is divided in the following way:

#### main
- UI
- time simulation
- calls graph

#### graph
- stores vertices and their relations as edges
- stores vehicles and updates them
- uses Dijkstra algorithm to find route for cars

#### vertex
- represents one tile in game world and a vertex in graph
- stores traffic light information

#### edge
- represents relation between two vertices
- stores also weight

#### vehicle
- stores size, position, destination and route of single vehicle
- move vehicle when `move` function is called

#### texturemanager
- handles loading textures for tile types (grass, road, building)

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
Exception handling is used when user wants to change the rates that 1) change lights and 2) buildings spawn vehicles, as both of these require user input. The try catch loop ensures that if user enters invalid argument or invalid value, the software throws an error, forcing to retry, or type -1 to cancel the operation.

#### Rule of three
Rule of three is enforced in every part of software: For example, see vehicle.cpp.

#### Dynamic binding and virtual classes/functions
Vehicle class uses dynamic binding, as we have derived classes for vehicles. For example, virtual destructor is required for base class Vehicle.

### Known bugs
TBA



## Testing
*how the different modules in software were tested, description of the methods and outcomes*
Due to scheduling problems, unit testing was done using <cassert> and in a separate test function in main.cpp, which can be called while running the main program (instructions can be found in main.cpp. Unit testing was used to ensure that individual functions work appropriately. Unfortunately, there was no time to set third-party unit testing C++ frameworks such as google test or CPPunit.

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
