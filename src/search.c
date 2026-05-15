#include "website.h"
#include "load.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void open(WebDatabase *db, char* link) {
    int i;

    for(i = 0; i < 9; i++) {

        if(strcmp(link, db->Database[i].web_url) == 0) 
        {
            printf("\n%s\n", db->Database[i].content);
            return;
        }
    }
    printf("URL %s tidak ditemukan.\n", link);
}
