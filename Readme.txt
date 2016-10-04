# Compilling and running

To compile the project, simply type make and run ./PMan

# Program structure

I split up different concerns into files. There are three files associated with this program:

1. PMan.c

This is where main is defined. It runs the main loop. The main loop is in charge of delegating different actions to other areas of our program.

2. ProcessList.c

This file contains all things related to our process list, which is a linkedlist that stores only pids. It has all the usual functions for add/removing things from linked lists, but also some commands are executed in here as well. For example, the bglist command is defined in processList, because it iterates through each pid, and lists the program name of that pid.

3. CommandUtility.c

The command utility file deals with parsing and reading commands, and calling the appropriate functions, which are also contained in this file. It provides most of the functionality associated with the commands. For example, it contains our function to create new processes, to print a pids stats, and to send stop/start/kill signals to our processes.


# Other notes

- ProcessList and CommandUtility each have header files associated with them.
