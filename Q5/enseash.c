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
		execlp(command, command, (char *) NULL);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	clock_gettime(CLOCK_REALTIME, stop);
	return status;
} 

void checkStatus(int status, struct timespec * start, struct timespec * stop){
	// Check and displays the exit status of a child process.
	
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
	int exec_status;
	struct timespec start, stop;

	consolePrint("Welcome to ENSEA Tiny Shell.\nPour quitter, tapez 'exit'\nensea \% ");
	while(1){
		command = consoleRead();
		exec_status = execute(command, &start, &stop);
		checkStatus(exec_status, &start, &stop);
	}
	return 0;
}
