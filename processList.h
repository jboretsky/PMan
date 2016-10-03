#ifndef PROCESSLIST
#define PROCESSLIST

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

struct process {
	int pid;
	int state;
	char* command;
	struct process* next;
};

struct process* create_list();

void push_back(struct process* head, int pid);

void remove_terminated_processes(struct process* head);

void print_list(struct process* head); 

bool find(struct process* head, int pid);

#endif
