#include <unistd.h> 
#include <string.h>
#include <stdlib.h>

#define READSIZE 50

static void consolePrint (const char*);

static char* consoleRead(void);

static void execute(char*);
