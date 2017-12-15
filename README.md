# Sim-city-1 ReadMe

## Pre-requisites

Sim-city-1 is designed to run on a linux system that has `SFML 2.3.2` installed.
Such systems can be found at Maari-A and Maari-C classes in Maarintalo.

To install SFML at your own system, please visit the official SFML website at
https://www.sfml-dev.org

For *Windows* users, it is advised to download Virtualbox, install Ubuntu and the necessary parts to run the software.

For *Mac users*, the terminal should be sufficient, as we have also tested and ran our program in Mac OS X.

## Setup

To run Sim-city-1, simply navigate to the project root directory using your unix terminal and then
run the following command:

	'make run-main'

This command will compile the source files and make an executable called 'sim-city-1'. The command will also
run the executable. The executable can be found in the src directory. The program can be run again from
there or you can simply use the 'make run-main' command again. You can clean the src directory using the 'make clean'
command, which will remove object files and executables from the src directory.

## Simulation instructions

To get started, simply run the program and read the welcome message on the console. That should get you started!

Detailed instructions is included in the `readme.md`, which can be found in the `doc` folder.

## Other foldiers and files

The project root directory contains the following folders:

  * `plan/` -- Here is our project plan.

  * `doc/` -- Here are the documentation sources related to our project.

  * `src/` -- Here are the C++ source files.

  * `README.md` -- The file you are now reading.

  * `Makefile`	-- Makefile to be used with the unix program called make.

## Credits
- Harti Hänninen, Industrial Engineering and Management
- Risto Koverola, Computer Science and Engineering
- Ilari Rauhala, Engineering Physics and Mathematics
- Tianzhong Pan, Industrial Engineering and Management

On 15th December, 2017 at Espoo, Otaniemi.
