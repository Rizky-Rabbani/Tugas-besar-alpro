#include "load.h"
#include "website.h"
#include <stdio.h>

extern void SeedLCG(); 

int main() {
    WebDatabase db;
    LoadConfig config;
    char *folder_data = "config"; // Nama folder tempat file CSV berada

    // Inisialisasi database agar kosong (isi 0)
    InitWebDatabase(&db);

    // Load data pertama kali
    if (!LoadData(&db, &config, folder_data)) {
        printf("Gagal memuat data awal!\n");
        return 1;
    }

    SeedLCG();

    // Inisialisasi Tab
    InitTab(&db);

    // Masuk ke fungsi home
    home(&db);

    // Kalo udah selesai, Bebaskan memori sebelum keluar
    FreeWebDatabase(&db);

    return 0;
}
