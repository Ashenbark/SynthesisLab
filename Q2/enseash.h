#include <unistd.h> 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

static void consolePrint (const char *s);
#define READSIZE 50

static void consolePrint (const char*);

static char* consoleRead(void);

static void execute(char*);
