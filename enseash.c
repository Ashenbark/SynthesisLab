#include "enseash.h"

static void consolePrint (const char *s)
{
    write(STDOUT_FILENO, s, strlen(s));
}

static char* consoleRead(){
	char * reading = malloc(READSIZE);
	int lenght = read(STDIN_FILENO, reading, READSIZE);
	reading[lenght-1] = '\0';
	
	return reading;
}
	
static int execute(char* command, struct timespec * start, struct timespec * stop){
	char* cmd_exit = "exit";
	int status;
	
	if(strncmp(command, cmd_exit, strlen(cmd_exit))==0) {
		consolePrint("Bye bye...\n");
		exit(EXIT_SUCCESS);
	}
	
	clock_gettime(CLOCK_REALTIME, start);
	
	pid_t pid = fork();
	if (pid==0){
		int asOutput = 0;
		int asInput = 0;
		char * filename;
		
		char * token_array[COMMANDSIZE];

		// We extract the first token
		char * token = strtok(command, " ");

		// Then loop through the string to extract all other tokens

		int i = 0;
		while( token != NULL ) {
			if (asOutput == 1 || asInput == 1) {
				filename = token;
			} 
			
			token_array[i] = token;
			
			if (strcmp(token, ">") == 0) {
			  asOutput = 1;
			  token_array[i] = NULL;
			}
			if (strcmp(token, "<") == 0) {
			  asInput = 1;
			  token_array[i] = NULL;
			}
			
			token = strtok(NULL, " ");
			i++;
		}
		
		// Finally we put a NULL as the last element of the array
		token_array[i] = NULL;
		
		if (asOutput == 1) {
			// reroot the output to a new file descriptor
			mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
			int descriptor = creat(filename, mode);
			dup2(descriptor, 1);
		}
		
		execvp(token_array[0], token_array);
	
		consolePrint("Error: invalid command\n");
	
		exit(EXIT_SUCCESS);
	}
	
	waitpid(pid, &status, 0);
	clock_gettime(CLOCK_REALTIME, stop);
	return status;
} 
	
void checkStatus(int status, struct timespec * start, struct timespec * stop){
	char prompt[PROMPTSIZE];
	double counter = (stop->tv_nsec - start->tv_nsec)/1e6;
	
	if (WIFEXITED(status)){
		sprintf(prompt, "ensea [exit:%d|%.0lf ms] %% ", WEXITSTATUS(status), counter);
	}
	
	else if (WIFSIGNALED(status)) {
		sprintf(prompt, "ensea [sign:%d|%.0lf ms] %% ", WTERMSIG(status), counter);
	}
	
	else {
		sprintf(prompt,"ensea %% ");
	}
	
	consolePrint(prompt);
	return;
}

int main(){

	char* command;
	int ex_status;
	struct timespec start, stop;
	
	consolePrint("Welcome to ENSEA Tiny Shell.\nPour quitter, tapez 'exit'\n");
	consolePrint("ensea \% ");
	
	while(1){
		command = consoleRead();
		ex_status = execute(command, &start, &stop);
		checkStatus(ex_status, &start, &stop);
	}
	
	return 0;
}
