#include "save.h"
#include "website.h"
#include "load.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void CommandRouter1(char* command, WebDatabase *db)
{
    RemoveNewline(command);

    if(strcmp(command, "newtab") == 0)
    {
        newtab(db);
    }else if(strcmp(command, "closetab")==0)
    {
        closetab(db);
    }else if(strcmp(command, "checktab") == 0)
    {
        checktab(db);
    }else if(strcmp(command, "nexttab") == 0)
    {
        nexttab(db, 1);
    }else if(strcmp(command, "prevtab") == 0)
    {
        prevtab(db, 1);
    }else if(strcmp(command, "back") == 0)
    {
        back(db, 1);
    }else if(strcmp(command, "forward") == 0)
    {
        forward(db, 1);
    }else if (strcmp(command, "view_tab_history") == 0)
    {
        view_tab_history(db);
    }else if(strcmp(command, "discover") == 0)
    {
        Discover(db);
    }
}

void CommandRouter2(char* command, char* extra, WebDatabase *db, LoadConfig *config)  
{
    RemoveNewline(extra); 
    
    if(strcmp(command, "open") == 0)
    {
        open(db, extra);
    }
    else if(strcmp(command, "nexttab") == 0)
    {
        int langkah;
        if (sscanf(extra, "%d", &langkah) != 1) 
        {
            printf("\nERROR: Argumen harus berupa angka integer!\n");
        } else {
            nexttab(db, langkah);
        }
    }
    else if(strcmp(command, "prevtab") == 0)
    {
        int langkah;
        if (sscanf(extra, "%d", &langkah) != 1) 
        {
            printf("\nERROR: Argumen harus berupa angka integer!\n");
        } else {
            prevtab(db, langkah);
        }
    }else if(strcmp(command, "search") == 0)
    {
        Search(extra);
    }else if(strcmp(command, "back") == 0)
    {
        back(db, atoi(extra));
    }else if(strcmp(command, "forward") == 0)
    {
        forward(db, atoi(extra));
    }else if(strcmp(command, "save") == 0)
    {
        SaveData(db, config, extra);
    }else if(strcmp(command, "load") == 0)
    {
        LoadConfigFile(config, db, extra);
    }else if(strcmp(command, "openlinked") == 0)
    {
        int nomor_tautan;
        if (sscanf(extra, "%d", &nomor_tautan) != 1) 
        {
            printf("\nERROR: Argumen harus berupa angka integer!\n");
        } 
        else 
        {
            // Ambil indeks tab aktif (convert dari 1-indexed ke 0-indexed)
            int idx_tab_aktif = db->Tab.current_tab - 1; 
            TabState *tab_sekarang = &db->Tab.daftar_tab[idx_tab_aktif];

            int idx_halaman_sekarang = tab_sekarang->current_web_idx;
            int current_active_id = -1;

            // PROTEKSI: Jika current_web_idx == -1 berarti user berada di HOME, ID tetap -1
            if (idx_halaman_sekarang >= 0 && tab_sekarang->web_count > 0)
            {
                current_active_id = tab_sekarang->daftar_web[idx_halaman_sekarang].id;
            }

            OpenLinked(db, current_active_id, nomor_tautan);
        }
    }else if(strcmp(command, "add_page") == 0)
    {
        add_page(db, extra);

    }else if(strcmp(command, "edit_page") == 0)
    {
        edit_page(db, extra);

    }else if(strcmp(command, "delete_page") == 0)
    {
        delete_page(db, extra);
        
    }
}