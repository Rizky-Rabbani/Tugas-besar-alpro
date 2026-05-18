#include "load.h"
#include "website.h"
#include <stdio.h>

int main() {
    WebDatabase db;
    LoadConfig config;
    char *folder_data = "config"; // Nama folder tempat file CSV berada

    // 1. Inisialisasi database agar kosong (isi 0)
    InitWebDatabase(&db);

    // 2. Load data pertama kali
    if (!LoadData(&db, &config, folder_data)) {
        printf("Gagal memuat data awal!\n");
        return 1;
    }

    // Inisialisasi Tab
    InitTab(&db);

    // 3. Masuk ke fungsi home
    home(&db);

    // 4. Bebaskan memori sebelum keluar (Sangat Penting!)
    FreeWebDatabase(&db);

    return 0;
}
