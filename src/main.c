#include "save.h"
#include "load.h"
#include "website.h"
#include "history.h"
#include "command_router.h"
#include <stdio.h>

int main() {

    // Deklarasi Variabel
    WebDatabase db;
    LoadConfig config;
    char *folder_data = "config"; // Nama folder tempat file CSV berada

    // Inisialisasi database agar kosong (isi 0)
    InitWebDatabase(&db);
    SeedLCG(&db, &config);

    // Load data pertama kali
    if (!LoadData(&db, &config, folder_data)) {
        printf("Gagal memuat data awal!\n");
        return 1;
    }

    // Inisialisasi Tab
    InitTab(&db);
    SetupCommandRouterMap();
    InitGlobalHistory(&db);

    // Masuk ke fungsi home
    home(&db, &config); 

    // Bebaskan memori sebelum keluar 
    FreeWebDatabase(&db);

    return 0;
}