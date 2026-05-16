#include "website.h"
#include "load.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void back(WebDatabase* db) {
    int idx_tab_aktif = db->Tab.current_tab - 1;
    TabState *tab_aktif = &db->Tab.daftar_tab[idx_tab_aktif];

    if (tab_aktif->current_web_idx == -1) 
    {
        printf("\nERROR: BACK TIDAK BISA DIGUNAKAN LAGI KARENA TIDAK ADA HALAMAN SEBELUMNYA!\n");

    }
    else if (tab_aktif->current_web_idx == 0) 
    {
        tab_aktif->current_web_idx = -1; 
        printf("\nBACK : Kembali ke website HOME\n");

    }
    else 
    {
        tab_aktif->current_web_idx--; 
        int idx_web = tab_aktif->current_web_idx;
        
        printf("\nBACK : Kembali ke website %s\n", tab_aktif->daftar_web[idx_web].web_url);
        printf("%s\n", tab_aktif->daftar_web[idx_web].content);

    }
}

void forward(WebDatabase* db) {
    int idx_tab_aktif = db->Tab.current_tab - 1;
    TabState *tab_aktif = &db->Tab.daftar_tab[idx_tab_aktif];

    if (tab_aktif->current_web_idx >= tab_aktif->web_count - 1) 
    {
        printf("\nERROR: FORWARD TIDAK BISA DIJALANKAN KARENA TIDAK ADA HALAMAN SELANJUTNYA!\n");
        
        if (tab_aktif->web_count > 0) {
            int idx_akhir = tab_aktif->current_web_idx;
            printf("\n(Konten web paling akhir: %s)\n", tab_aktif->daftar_web[idx_akhir].web_url);
            printf("%s\n", tab_aktif->daftar_web[idx_akhir].content);
        } else {
            printf("\n(Konten web paling akhir: HOME)\n");
        }
        
    }
    else 
    {
        tab_aktif->current_web_idx++; // Maju 1 indeks
        int idx_web = tab_aktif->current_web_idx;
        
        printf("\nFORWARD : Maju ke website %s\n", tab_aktif->daftar_web[idx_web].web_url);
        printf("%s\n", tab_aktif->daftar_web[idx_web].content);

    }
}


