#ifndef COMMANDSERVICE
#define COMMANDSERVICE

#include <string.h>
#include <signal.h>

#include "./processList.h"

void process_input(struct process* processes, char** input);

void send_signal(int signal, char** input, struct process* processes);

void pstat(struct process* processes, char** input);

void print_status(int pid);

void print_stats(int pid);

void fork_process(struct process* processes, char** input);

#endif
