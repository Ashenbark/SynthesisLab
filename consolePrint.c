#include "consolePrint.h"


static void consolePrint (const char *s)
{
    write (STDOUT_FILENO, s, strlen(s));
}
