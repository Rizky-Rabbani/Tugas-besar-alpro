#include "website.h"
#include "load.h"
#include <stdio.h>
#include <string.h>

void CommandRouter1(char* command, WebDatabase *db)
{
    printf("%s command router 1 menerima\n", command);
}

void CommandRouter2(char* command, char* extra, WebDatabase *db) {

    RemoveNewline(extra); 
    
    if(strcmp(command, "open") == 0)
    {
        open(db, extra);
    }
}
