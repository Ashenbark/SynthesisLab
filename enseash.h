#include <unistd.h> 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define READSIZE 50
#define PROMPTSIZE 50
#define COMMANDSIZE 20

static void consolePrint (const char*);

static char* consoleRead(void);

static int execute(char*, struct timespec *, struct timespec *);

void checkStatus(int, struct timespec *, struct timespec *);
