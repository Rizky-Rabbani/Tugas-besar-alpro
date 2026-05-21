#include "website.h"
#include "load.h"
#include "save.h"
#include "command_router.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// --------------------// FUNGSI DASAT ADT MAP // -------------------- //
void InitCommandMap(CommandMap *map) {
    map->router1_size = 0;
    map->router2_size = 0;
}

// Fungsi untuk mendaftarkan command 1 kata (Router 1)
void RegisterCommand1(CommandMap *map, char *name, CmdFunc1 func) {
    if (map->router1_size < 20) {
        strcpy(map->router1_table[map->router1_size].command_name, name);
        map->router1_table[map->router1_size].function_ptr = func;
        map->router1_size++;
    }
}

// Fungsi untuk mendaftarkan command 2 kata (Router 2)
void RegisterCommand2(CommandMap *map, char *name, CmdFunc2 func) {
    if (map->router2_size < 20) {
        strcpy(map->router2_table[map->router2_size].command_name, name);
        map->router2_table[map->router2_size].function_ptr = func;
        map->router2_size++;
    }
}

// --------------------// FUNGSI WRAPPER UNTUK COMMAND ROUTER // -------------------- //
// Wrapper Router 1 
void WrapNewTab(WebDatabase *db) { newtab(db); }
void WrapCloseTab(WebDatabase *db) { closetab(db); }
void WrapCheckTab(WebDatabase *db) { checktab(db); }
void WrapDiscover(WebDatabase *db) { Discover(db); }
void WrapViewHistory(WebDatabase *db) { view_tab_history(db); }
void WrapBack1(WebDatabase *db) { back(db, 1); }
void WrapForward1(WebDatabase *db) { forward(db, 1); }
void WrapNextTab1(WebDatabase *db) { nexttab(db, 1); }
void WrapPrevTab1(WebDatabase *db) { prevtab(db, 1); }
void WrapViewHistoryGlobal(WebDatabase *db) { PrintGlobalHistory(db); }

// Wrapper Router 2 
void WrapOpen(char *extra, WebDatabase *db, LoadConfig *config) { open(db, extra); }
void WrapSearch(char *extra, WebDatabase *db, LoadConfig *config) { Search(extra); }
void WrapSave(char *extra, WebDatabase *db, LoadConfig *config) { SaveData(db, config, extra); }
void WrapLoad(char *extra, WebDatabase *db, LoadConfig *config) { LoadConfigFile(config, db, extra); }
void WrapBackN(char *extra, WebDatabase *db, LoadConfig *config) { back(db, atoi(extra)); }
void WrapForwardN(char *extra, WebDatabase *db, LoadConfig *config) { forward(db, atoi(extra)); }
void WrapAddPage(char *extra, WebDatabase *db, LoadConfig *config) { add_page(db, extra); }
void WrapEditPage(char *extra, WebDatabase *db, LoadConfig *config) { edit_page(db, extra); }
void WrapDeletePage(char *extra, WebDatabase *db, LoadConfig *config) { delete_page(db, extra); }

void WrapOpenLinked(char *extra, WebDatabase *db, LoadConfig *config) {
    int nomor_tautan;
    if (sscanf(extra, "%d", &nomor_tautan) == 1) {
        int idx_tab_aktif = db->Tab.current_tab - 1;
        TabState *tab_sekarang = &db->Tab.daftar_tab[idx_tab_aktif];
        int current_active_id = -1;
        if (tab_sekarang->current_web_idx >= 0 && tab_sekarang->web_count > 0) {
            current_active_id = tab_sekarang->daftar_web[tab_sekarang->current_web_idx].id;
        }
        OpenLinked(db, current_active_id, nomor_tautan);
    } else {
        printf("\nERROR: Argumen harus berupa angka integer!\n");
    }
}


// --------------------// FUNGSI INTI // -------------------- //

// Deklarasikan variabel global map router di command_router.c
CommandMap cmd_map;

// Fungsi konfigurasi awal untuk mendaftarkan seluruh command 
void SetupCommandRouterMap() {
    InitCommandMap(&cmd_map);

    // Registrasi Router 1 (Key -> Value Function)
    RegisterCommand1(&cmd_map, "newtab", WrapNewTab);
    RegisterCommand1(&cmd_map, "closetab", WrapCloseTab);
    RegisterCommand1(&cmd_map, "checktab", WrapCheckTab);
    RegisterCommand1(&cmd_map, "discover", WrapDiscover);
    RegisterCommand1(&cmd_map, "view_tab_history", WrapViewHistory);
    RegisterCommand1(&cmd_map, "back", WrapBack1);
    RegisterCommand1(&cmd_map, "forward", WrapForward1);
    RegisterCommand1(&cmd_map, "nexttab", WrapNextTab1);
    RegisterCommand1(&cmd_map, "prevtab", WrapPrevTab1);
    RegisterCommand1(&cmd_map, "history", WrapViewHistoryGlobal);

    // Registrasi Router 2 (Key -> Value Function)
    RegisterCommand2(&cmd_map, "open", WrapOpen);
    RegisterCommand2(&cmd_map, "search", WrapSearch);
    RegisterCommand2(&cmd_map, "save", WrapSave);
    RegisterCommand2(&cmd_map, "load", WrapLoad);
    RegisterCommand2(&cmd_map, "back", WrapBackN);
    RegisterCommand2(&cmd_map, "forward", WrapForwardN);
    RegisterCommand2(&cmd_map, "openlinked", WrapOpenLinked);
    RegisterCommand2(&cmd_map, "add_page", WrapAddPage);
    RegisterCommand2(&cmd_map, "edit_page", WrapEditPage);
    RegisterCommand2(&cmd_map, "delete_page", WrapDeletePage);
}

void CommandRouter1(char* command, WebDatabase *db)
{
    RemoveNewline(command);

    // MAP LOOKUP: Cari fungsi berdasarkan Key
    for (int i = 0; i < cmd_map.router1_size; i++) {
        if (strcmp(cmd_map.router1_table[i].command_name, command) == 0) {
            // Eksekusi fungsi langsung dari pointer fungsi Map
            cmd_map.router1_table[i].function_ptr(db);
            return;
        }
    }
    printf("Command tidak dikenali.\n");
}

void CommandRouter2(char* command, char* extra, WebDatabase *db, LoadConfig *config)  
{
    RemoveNewline(extra); 

    // MAP LOOKUP: Cari fungsi berdasarkan Key
    for (int i = 0; i < cmd_map.router2_size; i++) {
        if (strcmp(cmd_map.router2_table[i].command_name, command) == 0) {
            // Eksekusi fungsi langsung dari pointer fungsi Map
            cmd_map.router2_table[i].function_ptr(extra, db, config);
            return;
        }
    }
    printf("Command tidak dikenali.\n");
}