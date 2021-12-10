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
	char* cmd_exit = "exit";
	
	if(strncmp(command, cmd_exit, strlen(cmd_exit))==0) {
		consolePrint("Bye bye...\n");
		exit(EXIT_SUCCESS);
	}
	else {
		pid_t pid = fork();
		if (pid==0){
			execlp(command, command, (char *) NULL);
		}
	}
} 
	
int main(int argc ,char *argv [ ]){
	char* command;
	
	consolePrint("Welcome to ENSEA Tiny Shell.\nPour quitter, tapez 'exit'\n");
	
	while(1){
		consolePrint("ensea \% ");
		command = consoleRead();
		execute(command);
	}
}
