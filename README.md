Sim-city-1 ReadMe

`Setup:`
Sim-city-1 is designed to run on a linux system that has sfml 2.3.2 installed.
Such systems can be found at for example Maari-A and Maari-C classes in Maarintalo.

To run Sim-city-1, simply navigate to the project root directory using your unix terminal and then
run the following command:

	'make run-main'

This command will compile the source files and make an executable called 'sim-city-1'. The command will also
run the executable. The executable can be found in the src directory. The program can be run again from
there or you can simply use the 'make run-main' command again. You can clean the src directory using the 'make clean'
command, which will remove object files and executables from the src directory.

The project root directory should contain the following folders:

  * `plan/` -- Here is our project plan.

  * `doc/` -- Here are the documentation sources related to our project.

  * `src/` -- Here are the C++ source files.

  * `README.md` -- The file you are now reading.

  * `Makefile`	-- Makefile to be used with the unix program called make.