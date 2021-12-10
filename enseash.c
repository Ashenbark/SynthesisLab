#include "enseash.h"

static void consolePrint (const char *s)
{
    write(STDOUT_FILENO, s, strlen(s));
}


int main(int argc ,char *argv [ ]){
	consolePrint("test\n ");
}
