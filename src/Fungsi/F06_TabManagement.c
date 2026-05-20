#include "website.h"
#include "load.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void createtab(TabState* tab, int n)
{
    tab->id = n;
    sprintf(tab->nama_tab, "TAB%d", n);
    tab->web_count = 0;
    tab->current_web_idx = -1;
}

void InitTab(WebDatabase* db)
{   
    createtab(&db->Tab.daftar_tab[0], 1);
    db->Tab.current_tab = 1;
    db->Tab.tab_count = 1;
    db->Tab.tab_terakhir = 1;
}

void newtab(WebDatabase* db)
{
    if(db->Tab.tab_count == TABS_MAX_AMOUNT)
    {
        printf("\nERROR: Jumlah tab tidak bisa melebihi batas maksimum!\n");
    }
    else
    {
        db->Tab.tab_terakhir++; 
        db->Tab.tab_count++;    
        db->Tab.current_tab = db->Tab.tab_count; 
        
    
        createtab(&db->Tab.daftar_tab[db->Tab.tab_count - 1], db->Tab.tab_terakhir);

        printf("\nTab baru (TAB%d) berhasil dibuat!\n", db->Tab.tab_terakhir);
    }
}
void majuintab(WebDatabase* db)
{
    int i;

    for(i=db->Tab.current_tab-1 ; i<db->Tab.tab_count - 1 ; i++)
    {
        db->Tab.daftar_tab[i] = db->Tab.daftar_tab[i+1];
    }
}

void closetab(WebDatabase* db)
{
    if(db->Tab.tab_count == 1)
    {
        printf("\nERROR: Tidak bisa menutup tab, tab minimal berjumlah 1!\n");

    }
    
    else if(db->Tab.current_tab == db->Tab.tab_count)
    {
        printf("\n%s berhasil ditutup\n", db->Tab.daftar_tab[db->Tab.current_tab-1].nama_tab);
        db->Tab.tab_count--;
        db->Tab.current_tab--;
    }
    
    else
    {
        majuintab(db);

        db->Tab.tab_count--;

    }

}

void checktab(WebDatabase* db)
{
    int i;

    printf("list of tab(s) : \n");

    for(i=0 ; i<db->Tab.tab_count ; i++)
    {
        printf("[%d] %s\n", i+1, db->Tab.daftar_tab[i].nama_tab);
    }

    printf("Current tab : %s", db->Tab.daftar_tab[db->Tab.current_tab-1].nama_tab);
}

void InputTab(WebDatabase* db, WebSite web) {
    int idx_tab_aktif = db->Tab.current_tab - 1;
    TabState *tab_aktif = &db->Tab.daftar_tab[idx_tab_aktif];

    if (tab_aktif->web_count < TABS_MAX_AMOUNT) 
    {
        tab_aktif->daftar_web[tab_aktif->web_count] = web;
        tab_aktif->web_count++;

    } else 
    {
        int i;
        for (i = 0; i < TABS_MAX_AMOUNT - 1; i++) {
            tab_aktif->daftar_web[i] = tab_aktif->daftar_web[i + 1];
        }
        tab_aktif->daftar_web[TABS_MAX_AMOUNT - 1] = web;

    }
    tab_aktif->current_web_idx = tab_aktif->web_count - 1;
    
}

void nexttab(WebDatabase* db, int langkah)
{
    if (db->Tab.current_tab + langkah > db->Tab.tab_count)
    {
        printf("\nERROR: Langkah melebihi jumlah tab yang tersedia!\n");
    }
    else
    {
        db->Tab.current_tab += langkah;
        int idx = db->Tab.current_tab - 1;
        printf("\nBerpindah ke %s\n", db->Tab.daftar_tab[idx].nama_tab);
    }
}

void prevtab(WebDatabase* db, int langkah)
{
    if (db->Tab.current_tab - langkah < 1)
    {
        printf("\nERROR: Langkah melebihi batas tab pertama!\n");
    }
    else
    {
        db->Tab.current_tab -= langkah;
        int idx = db->Tab.current_tab - 1;
        printf("\nBerpindah ke %s\n", db->Tab.daftar_tab[idx].nama_tab);
    }
}
