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

static int execute(char* command){
	char* cmd_exit = "exit";
	int status;
	
	if(strncmp(command, cmd_exit, strlen(cmd_exit))==0) {
		consolePrint("Bye bye...\n");
		exit(EXIT_SUCCESS);
	}
	
	pid_t pid = fork();
	if (pid==0){
		execlp(command, command, (char *) NULL);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	return status;
} 

void checkStatus(int status){
	// Check and displays the exit status of a child process.
	
	char prompt[PROMPTSIZE];
	
	if (WIFEXITED(status)){
		sprintf(prompt, "ensea [exit:%d] %% ", WEXITSTATUS(status));
	}
	
	else if (WIFSIGNALED(status)) {
		sprintf(prompt, "ensea [sign:%d] %% ", WTERMSIG(status));
	}
	
	else {
		sprintf(prompt,"ensea %% ");
	}
	
	consolePrint(prompt);
	return;
}


int main(){
	char* command;
	int exec_status;

	consolePrint("Welcome to ENSEA Tiny Shell.\nPour quitter, tapez 'exit'\nensea \% ");
	while(1){
		command = consoleRead();
		exec_status = execute(command);
		checkStatus(exec_status);
	}
}
