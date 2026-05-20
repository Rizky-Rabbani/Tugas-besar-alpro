#include "website.h"
#include "load.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void view_tab_history(WebDatabase* db) 
{
    int i;
    int idx_tab_aktif = db->Tab.current_tab - 1;
    TabState *tab_aktif = &db->Tab.daftar_tab[idx_tab_aktif];

    if (tab_aktif->web_count == 0) {
        printf("\nRiwayat tab kosong. Anda berada di HOME.\n");
        return;
    }

    printf("\n--- Riwayat Kunjungan %s ---\n", tab_aktif->nama_tab);
    

    for (i = 0; i < tab_aktif->web_count; i++) 
    {
        if (i == tab_aktif->current_web_idx) 
        {
            printf("[%d] \033[1;32m%s\033[0m \033[1;31m<- YOU ARE HERE\033[0m\n", i + 1, tab_aktif->daftar_web[i].web_url);
        } else 
        {
            printf("[%d] %s\n", i + 1, tab_aktif->daftar_web[i].web_url);
        }
    }

    if (tab_aktif->current_web_idx != -1) 
    {
        int idx_aktif = tab_aktif->current_web_idx;
        printf("\n%s\n", tab_aktif->daftar_web[idx_aktif].content);

    } else 
    {
        printf("\n<<Konten HOME>>\n");

    }
}