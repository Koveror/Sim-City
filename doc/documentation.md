# Sim-City-1 Documentation

## Overview


## Software structure

### Class structure
Our class structure is diveded in following way
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
- stores information

#### edge
- represents relation between two vertices
- stores also weight

#### vehicle
- stores size, position, destination and route of single vehicle
- move vehicle when `move` function is called

## Instructions for building and using the software
To run Sim-city-1, simply navigate to the project root directory using your unix terminal and then run `make run-main` command. This command will compile the source files and make an executable called **sim-city-1**. The command will also run the executable. The executable can be found in the src directory. The program can be run again from there or you can simply use the `make run-main` command again. You can clean the src directory using the `make clean` command, which will remove object files and executables from the src directory.

To use our software you have to have SFML library installed on your machine.

### How to use the software
To add tiles on map, first choose which kind of tile you want to add using keyboard. Pressing **R** adds roads, **B** buildings and **G** grass (empty tile). When you have map ready and want cars to start spawning press **V**. Press **I** to toggle automatic traffic light control. You can also use right mouse button to manually switch traffic lights in any intersection. Letter **O** changes the rate that automatic traffic light control changes lights and **I** changes the rate that buildings spawn cars. Game speed can be changed using numbers **1** (1x), **2** (4x) and **3** (8x).

To save your current map psess **S** and follow instructions on the console. To load press **L** and also follow instructions on the console.

## Testing
*how the different modules in software were tested, description of the methods and outcomes*

## Work log
