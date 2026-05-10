#include "website.h"
#include <stdio.h>
#include <string.h>

void CommandRouter1(char* command)
{
    printf("%s command router 1 menerima", command);
}

void CommandRouter2(char* command, char* extra)
{
    printf("%s %s command router 2 menerima", command, extra);
}
