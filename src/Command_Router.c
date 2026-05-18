#include "website.h"
#include "load.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define LCG_A 1103515245
#define LCG_C 12345
#define LCG_M 2147483648

static unsigned long long lcg_seed = 1;

void SeedLCG() {
    lcg_seed = (unsigned long long)time(NULL);
}

unsigned int LCG_Rand() {
    lcg_seed = (LCG_A * lcg_seed + LCG_C) % LCG_M;
    return (unsigned int)lcg_seed;
}

void Discover(WebDatabase *db) {
    int total_pages = db->web_page_count; 

    if (total_pages == 0) {
        printf("Database kosong. Tidak ada halaman untuk ditampilkan.\n");
        return;
    }

    printf("\nBerikut adalah beberapa halaman yang mungkin menarik untukmu:\n");

    if (total_pages <= 5) {
        for (int i = 0; i < total_pages; i++) {
            printf("- %s\n", db->web_pages[i].url); 
        }
        return;
    }

    int chosen_indices[5];
    int chosen_count = 0;

    while (chosen_count < 5) {
        int random_index = LCG_Rand() % total_pages;
        int is_duplicate = 0;
        
        for (int i = 0; i < chosen_count; i++) {
            if (chosen_indices[i] == random_index) {
                is_duplicate = 1;
                break;
            }
        }

        if (!is_duplicate) {
            chosen_indices[chosen_count] = random_index;
            chosen_count++;
        }
    }

    for (int i = 0; i < 5; i++) {
        int idx = chosen_indices[i];
        printf("- %s\n", db->web_pages[idx].url);
    }
}

void CommandRouter1(char* command, WebDatabase *db)
{
    RemoveNewline(command);

    if(strcmp(command, "newtab") == 0)
    {
        newtab(db);
    }
    else if(strcmp(command, "closetab") == 0)
    {
        closetab(db);
    }
    else if(strcmp(command, "checktab") == 0)
    {
        checktab(db);
    }
    else if(strcmp(command, "nexttab") == 0)
    {
        nexttab(db, 1);
    }
    else if(strcmp(command, "prevtab") == 0)
    {
        prevtab(db, 1);
    }
    else if(strcmp(command, "back") == 0)
    {
        back(db, 1);
    }
    else if(strcmp(command, "forward") == 0)
    {
        forward(db, 1);
    }
    else if (strcmp(command, "view_tab_history") == 0)
    {
        view_tab_history(db);
    }
    else if (strcmp(command, "discover") == 0)
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
    }
    else if(strcmp(command, "search") == 0)
    {
        Search(extra);
    }
    else if(strcmp(command, "back") == 0)
    {
        back(db, atoi(extra));
    }
    else if(strcmp(command, "forward") == 0)
    {
        forward(db, atoi(extra));
    }
}
