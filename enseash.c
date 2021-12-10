#include "enseash.h"

static void consolePrint (const char *s){
    write(STDOUT_FILENO, s, strlen(s));
}

static char* consoleRead(){
	char* reading = malloc(50);
	read(STDIN_FILENO, reading, 50);
	return reading;
}


int main(int argc ,char *argv [ ]){
	
	consolePrint("Welcome to ENSEA Tiny Shell.\nPour quitter, tapez 'exit'. \nensea \% ");
	while(1){
		consoleRead();
		
		consolePrint("ensea \% ");
	}
}
