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

static void execute(char* command){
	int status;
	
	pid_t pid = fork();
	if (pid==0){
		execlp(command, command, (char *) NULL);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	return ;
} 


int main(){
	char* command;

	consolePrint("Welcome to ENSEA Tiny Shell.\nPour quitter, tapez 'exit'\n");
	while(1){
		consolePrint("ensea \% ");
		command = consoleRead();
		execute(command);
	}
}
