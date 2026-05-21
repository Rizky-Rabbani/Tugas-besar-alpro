#include "website.h"
#include "load.h"
#include "save.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ExitPage(WebDatabase *db, LoadConfig *config)
{
    char input;
    char folder[100]; 

    printf("\nSave data before exiting? (y/n)\n\n");
    printf(">>> ");

    // PERBAIKAN: Gunakan spasi sebelum %c untuk mengabaikan sisa whitespace/Enter di buffer
    scanf(" %c", &input); 

    // PERBAIKAN: Bandingkan karakter secara langsung menggunakan operator '=='
    if (input == 'y' || input == 'Y')
    {
        printf("\nplease input the save folder: \n");
        printf("\n>>> ");
        
        scanf("%s", folder); 
        
        SaveData(db, config, folder);
        return;
    }
    else if (input == 'n' || input == 'N')
    {
        return;
    }
    else
    {
        puts("Pilihan tidak valid. Keluar tanpa menyimpan.");
        return;
    }
}