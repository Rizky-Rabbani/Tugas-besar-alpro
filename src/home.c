#include "website.h"
#include "load.h"
#include <stdio.h>
#include <string.h>

void home(WebDatabase *db)
{
    char input[100];
    char command[100];
    char extra[100];
    int jumlah_kata = 0;
    int running = 1; // Variabel kontrol perulangan

    puts("\n\n                ===Selamat Datang di Home Interface===");
    puts("Ketik 'help' untuk menunjukkan beberapa command yang bisa dipakai!!");
    printAnya();

    while(running) 
    {
        printf("\n>>> ");

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
                // Panggil prosedur penanganan exit (D05 - Save option) 
                // Harus dibuat

                running = 0; 
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
                CommandRouter2(command, extra, db);
            }
            // Penanganan input tidak valid 
            else 
            {
                puts("Masukan tidak valid.");
            }
        }
    }
}
