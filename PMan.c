#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "./processList.h" // linked list and functions
#include "./commandService.h" // command parsing and handling

char** tokenize_input(char** commandInput, char* input) {
    char *tok;
	int commandLength;
	tok = strtok(input, " ");
	int inputIndex = 0;
	while(tok !=NULL) {
		commandLength = strlen(tok);
		commandInput[inputIndex] = malloc(sizeof(char)*(commandLength + 1));
		commandInput[inputIndex++] = tok;
		tok = strtok(NULL, " ");
	}
	commandInput[inputIndex] = 0;
	return commandInput;
}

int main(int argc, char *argv[]) {

    char *commands[] = {"bg"};
	char **commandInput = malloc(sizeof(char*) * 100);
	char **programArgs;
	
	struct process* processes = create_list();

    char *input;
    char *prompt = "PMan > ";

    while(1) {
		remove_terminated_processes(processes);
        input = readline(prompt);    
		tokenize_input(commandInput, input);
		process_input(processes, commandInput);
	}
    return 0;
}
