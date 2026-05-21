#include "save.h"
#include "website.h"
#include "load.h"
#include "command_router.h"
#include <stdio.h>
#include <string.h>

void home(WebDatabase *db, LoadConfig *config)
{
    char input[100];
    char command[100];
    char extra[100];
    int jumlah_kata = 0;
    int running = 1; // Variabel kontrol perulangan

    // Mengubah teks penyambut menjadi Kuning Emas Bold
    printf("\033[1;33m");
    puts("\n\n\t\t===Selamat Datang di CENTURION===");
    
    // Mengubah sub-teks menjadi Putih Terang Bold agar ada hirarki visual
    printf("\033[1;37m");
    puts("\t  WEBSITE KOMPONEN ELEKTRONIK FAVORIT ANAK ITB");
    
    // Kembalikan ke normal jika ingin ASCII art merah di bawahnya mengaturnya sendiri
    printf("\033[0m");
    printCenturion();

    while(running) 
    {
        printf("\n\n>>> ");

        if(fgets(input, sizeof(input), stdin))
        {
            // Menghilangkan newline
            input[strcspn(input, "\n")] = 0;

            // Jika input kosong (hanya enter), sscanf akan mengembalikan nilai < 1
            jumlah_kata = sscanf(input, "%s %s", command, extra);

            if (jumlah_kata < 1) 
            {
                continue; 
            }

            // Pengecekan keluar sesuai spesifikasi F11
            if (strcmp(command, "exit") == 0) 
            {
                ExitPage(db, config);
                running = 0; 
                printGoodBye();
                continue;
            }

            // Kalo input 1 kata, program ngarahin ke command router 1
            if(jumlah_kata == 1) 
            {
                CommandRouter1(command, db);
            }
            // Kalo input 2 kata, program ngarahin ke command router 2
            else if(jumlah_kata == 2) 
            {
                if (strcmp(command, "open") == 0) 
                {
                    if (!ValidasiURL(extra)) 
                    {
                        printf("\nERROR: Format URL tidak valid sesuai aturan E01!\n");
                        // Menghentikan alur agar tidak masuk ke CommandRouter2
                        continue; 
                    }
                }

                CommandRouter2(command, extra, db, config);
            }
            // Penanganan input tidak valid 
            else 
            {
                puts("Masukan tidak valid.");
            }
        }
    }
}