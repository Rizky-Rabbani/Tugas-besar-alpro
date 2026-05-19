#include "website.h"
#include "load.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void CommandRouter1(char* command, WebDatabase *db)
{
    RemoveNewline(command);

    if(strcmp(command, "newtab") == 0)
    {
        newtab(db);

    }else if(strcmp(command, "closetab")==0)
    {
        closetab(db);

    }else if(strcmp(command, "checktab") == 0)
    {
        checktab(db);

    }else if(strcmp(command, "nexttab") == 0)
    {
        nexttab(db, 1);

    }else if(strcmp(command, "prevtab") == 0)
    {
        prevtab(db, 1);

    }else if(strcmp(command, "back") == 0)
    {
        back(db, 1);

    }else if(strcmp(command, "forward") == 0)
    {
        forward(db, 1);

    }else if (strcmp(command, "view_tab_history") == 0)
    {
        view_tab_history(db);

    }else if (strcmp(command, "discover") == 0)
    {
        Discover(db);
    }

}

void CommandRouter2(char* command, char* extra, WebDatabase *db) {
    RemoveNewline(extra); 
    
    if(strcmp(command, "open") == 0)
    {
        open(db, extra);
    }
    else if(strcmp(command, "nexttab") == 0)
    {
        int langkah;

        if (sscanf(extra, "%d", &langkah) != 1) 
        {
            printf("\nERROR: Argumen harus berupa angka integer!\n");

        } else {
            nexttab(db, langkah);
        }
    }
    else if(strcmp(command, "prevtab") == 0)
    {
        int langkah;
        if (sscanf(extra, "%d", &langkah) != 1) 
        {
            printf("\nERROR: Argumen harus berupa angka integer!\n");

        } else {
            prevtab(db, langkah);
        }
    }else if(strcmp(command, "search") == 0)
    {
        Search(extra);

    }else if(strcmp(command, "back") == 0)
    {
        back(db, atoi(extra));

    }else if(strcmp(command, "forward") == 0)
    {
        forward(db, atoi(extra));

    }
    else if(strcmp(command, "save") == 0)
    {
        SaveData(db, extra);
    }
}
