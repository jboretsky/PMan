#include <time.h>
#include <unistd.h>

#include "./commandService.h"
#include "./processList.h"

void process_input(struct process* processes, char** input) {
	if (!input[0]) {
		return;
	}
	if (strcmp(input[0], "bg") == 0) {
		memmove(input, input+1, sizeof(char*)*100);
		fork_process(processes, input);
	} else if (strcmp(input[0], "bglist") == 0) {
		print_list(processes);
	} else if (strcmp(input[0], "pstat") == 0) {
		pstat(processes, input);
	} else if (strcmp(input[0], "bgkill") == 0) {
		send_signal(SIGKILL, input, processes);
	} else if (strcmp(input[0], "bgstop") == 0) {
		send_signal(SIGSTOP, input, processes);
	} else if (strcmp(input[0], "bgstart") == 0) {
		send_signal(SIGCONT, input, processes);
	} else {
		printf("%s:   command not found\n", input[0]);
	}
	return;
}

pid_t check_pid(struct process* processes, char** input) {
	if (!input[1]) {
		printf("Error: No pid was provided.\n");
		return -1;
	}
	if (!find(processes, atoi(input[1]))) {
		printf("Error: process %s does not exist.\n", input[1]);
		return -1;
	}

	return atoi(input[1]);
}

void send_signal(int signal, char** input, struct process* processes) {
	pid_t pid;
	pid = check_pid(processes, input);
	if (pid > 0) {
		kill(pid, signal);
	}
}

void pstat(struct process* processes, char** input) {
	pid_t pid;
	pid = check_pid(processes, input);
	if (pid > 0) {
		print_stats(pid);
        print_status(pid);
	}
}

void print_status(int pid) {
    char str[25];
	sprintf(str, "/proc/%d/status", pid);

	FILE* fp = fopen(str, "rb");

	char* file_contents = (char *)calloc(500, sizeof(char));
    char c;
    while (c = fgetc(fp) != EOF) {
        strncat(file_contents, &c, 1);
    }
    printf("%s\n", file_contents);

    char* tok;
    int toklength;
	tok = strtok(file_contents, "\n");
    int i = 0;
	for (i = 0; i < 50; ++i) {
        char* currToken = strtok(NULL, "\n");
        if (!currToken) break;
        if (i == 30 || i == 31) printf("%d, %s\n",i, currToken);
	}
    free(file_contents);
    return;
}

void print_stats(int pid) {
	char str[25];
	char **stats = (char **)malloc(sizeof(char*)*60);
	sprintf(str, "/proc/%d/stat", pid);

	FILE* fp;
	fp = fopen(str, "r");

	char *file_contents = malloc(sizeof(char)*500);
	fgets(file_contents, sizeof(char)*500, fp);

    char *tok;
	int toklength;
	tok = strtok(file_contents, " ");
	int i = 0;
	while(tok !=NULL) {
		toklength = strlen(tok);
		stats[i] = malloc(sizeof(char)*(toklength + 1));
		strcpy(stats[i],tok);
		tok = strtok(NULL, " ");
        ++i;
	}
    stats[i] = 0;

	printf("comm: %s\n", stats[1]);
	printf("state: %s\n", stats[2]);
	printf("utime: %lu\n", atoi(stats[13]) / sysconf(_SC_CLK_TCK));
	printf("stime: %lu\n", atoi(stats[14]) / sysconf(_SC_CLK_TCK));
	printf("rss: %s\n", stats[23]);

    for (i=0; stats[i]; i++) {
        free(stats[i]);
    }
    free(stats);
    free(file_contents);
	fclose(fp);
	return;
}

void fork_process(struct process* processes, char** input) {
	if (!input[0]) return;
	pid_t fpid;
	fpid = fork();
	if (fpid < 0) {
		printf("error in fork!\n");
	} else if (fpid == 0) {
		if (execvp(input[0], input) < 0) {
			printf("Error: execution of %s failed. Is this a real program?\n", input[0]);
			exit(0);
		}
	} else {
		push_back(processes, fpid);
	}
}

