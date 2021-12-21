#include "enseash.h"

static void consolePrint (const char *s)
{
    write(STDOUT_FILENO, s, strlen(s));
}

int main(){

	consolePrint("Welcome to ENSEA Tiny Shell.\nPour quitter, tapez 'exit'\n");
	consolePrint("ensea \% ");

	return 0;
}
