#include "website.h"
#include "load.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void open(WebDatabase *db, char* link) {
    int i, j;
    int found = 0;

    for(i = 0; i < db->website_count; i++) {
        if(strcmp(link, db->Database[i].web_url) == 0) 
        {
            // Fungsi open utama
            printf("\n%s\n", db->Database[i].content);
            InputTab(db, db->Database[i]);

            
            found = 1;
            
            // Fungsi linkedpages
            printf("\nLinked pages :\n");
            int nomor_tautan = 1;
            for(j = 0; j < db->website_count; j++) 
            {
                if(db->matrix[i][j] == 1) {
                    printf("[%d] %s\n", nomor_tautan, db->Database[j].web_url);
                    nomor_tautan++;
                    
                }
                
            }

            if(nomor_tautan == 1) 
            {
                printf("(Tidak ada website yang tertaut)\n");
                
            }
            return;
            
        }
    }
    
    if(!found)
    {
        printf("URL %s tidak ditemukan.\n", link);
        
    }
}
