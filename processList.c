#include "./processList.h"

struct process* create_list() {
	struct process* list = malloc(sizeof(struct process));
	list->pid = -1;
	list->next = NULL;
	return list;
}

void push_back(struct process* head, int pid) {
	while (head->next) {
		head = head->next;	
	}
	head->next = malloc(sizeof(struct process));
	head->next->pid = pid;
	head->next->next = NULL;
}

void remove_terminated_processes(struct process* head) {
	while(head->next) {
		pid_t currProcess = head->next->pid;
		pid_t ret = waitpid(currProcess, NULL, WNOHANG);
		if (ret == currProcess) {
			printf("Process %d has terminated.\n", currProcess);
			struct process* tmp = head->next;
			head->next = head->next->next;
			free(tmp);
		} else {
			head = head->next;
		}
	}
}

void print_list(struct process* head) {
	head = head->next;
	int job_count = 0;
	while(head != NULL) {
		++job_count;
		// may want to write function to do this since it will be
		// done for pstat also!
		char exe[1024];
		char str[100];
		sprintf(str, "/proc/%d/exe", head->pid);
		int ret = readlink(str, exe, sizeof(exe)-1);
		if (ret == -1) {
			printf("Error reading process name");
		}
		exe[ret] = 0;
		printf("%d %s\n", head->pid, exe);
		head = head->next;
	}
	printf("Total background jobs: %d\n", job_count);
}

bool find(struct process* head, int pid) {
	head = head->next;
	while (head) {
		if (head->pid == pid) return true;
		head = head->next;
	}
	return false;
}
