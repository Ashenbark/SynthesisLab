#include <unistd.h> 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define READSIZE 50
#define PROMPTSIZE 50

static void consolePrint (const char*);

static char* consoleRead(void);

static int execute(char*);

void checkStatus(int);
