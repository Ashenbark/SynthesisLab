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
	return WEXITSTATUS(status);

} 
	
int main(int argc ,char *argv [ ]){
	char* command;
	int ex_status;
	char prompt[PROMPTSIZE];
	
	consolePrint("Welcome to ENSEA Tiny Shell.\nPour quitter, tapez 'exit'\n");
	consolePrint("ensea \% ");
	
	while(1){
		command = consoleRead();
		ex_status = execute(command);
		sprintf(prompt, "ensea [exit:%d] %% ", ex_status);
		consolePrint(prompt);
	}
	
	return 0;
}
