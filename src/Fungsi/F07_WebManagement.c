#include "website.h"
#include "load.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void back(WebDatabase* db, int langkah)
{
    int idx_tab_aktif = db->Tab.current_tab - 1;
    TabState *tab_aktif = &db->Tab.daftar_tab[idx_tab_aktif];

    // Sedang di HOME dan tidak ada riwayat sebelumnya
    if (tab_aktif->current_web_idx == -1) 
    {
        printf("\nERROR: BACK TIDAK BISA DIGUNAKAN LAGI KARENA TIDAK ADA HALAMAN SEBELUMNYA!\n");

    }

    // Langkah mundur melebihi batas indeks pertama (kembali ke HOME)
    else if (tab_aktif->current_web_idx - langkah < 0) 
    {
        // Ubah halaman menjadi di HOME
        tab_aktif->current_web_idx = -1; 
        printf("\nBACK : Kembali ke HOME\n");

    }

    // Mundur beberapa langkah ke website sebelumnya
    else 
    {
        tab_aktif->current_web_idx -= langkah; // Mundur sebanyak X langkah
        int idx_web = tab_aktif->current_web_idx;
        
        printf("\nBACK : Kembali ke website %s\n", tab_aktif->daftar_web[idx_web].web_url);
        printf("%s\n", tab_aktif->daftar_web[idx_web].content);
    }
}

void forward(WebDatabase* db, int langkah) 
{
    int idx_tab_aktif = db->Tab.current_tab - 1;
    TabState *tab_aktif = &db->Tab.daftar_tab[idx_tab_aktif];

    // Langkah maju melebihi jumlah halaman yang ada di riwayat depan
    if (tab_aktif->current_web_idx + langkah >= tab_aktif->web_count) 
    {
        printf("\nERROR: FORWARD TIDAK BISA DIJALANKAN KARENA TIDAK ADA HALAMAN SELANJUTNYA!\n");
        
        if (tab_aktif->web_count > 0) {
            int idx_akhir = tab_aktif->web_count - 1; // Langsung arahkan ke web paling ujung
            tab_aktif->current_web_idx = idx_akhir;
            printf("\n(Konten web paling akhir: %s)\n", tab_aktif->daftar_web[idx_akhir].web_url);
            printf("%s\n", tab_aktif->daftar_web[idx_akhir].content);
        } else {
            printf("\n(Konten web paling akhir: HOME)\n");
        }

    }

    // Bisa maju beberapa langkah ke depan
    else 
    {
        tab_aktif->current_web_idx += langkah; // Maju sebanyak X langkah
        int idx_web = tab_aktif->current_web_idx;
        
        printf("\nFORWARD : Maju ke website %s\n", tab_aktif->daftar_web[idx_web].web_url);
        printf("%s\n", tab_aktif->daftar_web[idx_web].content);

    }
}