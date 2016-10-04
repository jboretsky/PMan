#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "./processList.h" // linked list and functions
#include "./commandUtility.h" // command parsing and handling

char** tokenize_input(char** commandInput, char* input) {
    char *tok;
	int commandLength;
	tok = strtok(input, " ");
	int inputIndex = 0;
	while(tok !=NULL) {
		commandLength = strlen(tok);
		commandInput[inputIndex] = calloc((commandLength + 1), sizeof(char));
		strcpy(commandInput[inputIndex++],tok);
		tok = strtok(NULL, " ");
	}
	commandInput[inputIndex] = 0;
	return commandInput;
}

int main(int argc, char *argv[]) {

    char *commands[] = {"bg"};
	char **programArgs;
	
	struct process* processes = create_list();

    char *input;
    char *prompt = "PMan > ";

    while(1) {
        char **commandInput = calloc(100, sizeof(char*));
		remove_terminated_processes(processes);
        input = readline(prompt);    
		tokenize_input(commandInput, input);
		process_input(processes, commandInput);
        
        int i;
        for (i = 0; commandInput[i] != 0; ++i) {
            free(commandInput[i]);
        }
        free(commandInput);
        free(input);
	}
    return 0;
}
