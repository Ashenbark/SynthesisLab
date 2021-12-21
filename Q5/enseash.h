#include <unistd.h> 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>

#define READSIZE 50
#define PROMPTSIZE 50

static void consolePrint (const char*);

static char* consoleRead(void);

static int execute(char*, struct timespec *, struct timespec *);

void checkStatus(int, struct timespec *, struct timespec *);
