#ifndef COMMAND_ROUTER_H
#define COMMAND_ROUTER_H

#include "website.h"

// Definisi tipe data pointer fungsi untuk CommandRouter1 (hanya menerima WebDatabase*)
typedef void (*CmdFunc1)(WebDatabase*);

// Definisi tipe data pointer fungsi untuk CommandRouter2 (menerima extra, db, config)
typedef void (*CmdFunc2)(char*, WebDatabase*, LoadConfig*);

// Map untuk Command Router 1
typedef struct {
    char command_name[30];
    CmdFunc1 function_ptr;
} RouterEntry1;

// Map untuk Command Router 2
typedef struct {
    char command_name[30];
    CmdFunc2 function_ptr;
} RouterEntry2;

// Struktur Utama ADT Map Router
typedef struct {
    RouterEntry1 router1_table[20];
    int router1_size;

    RouterEntry2 router2_table[20];
    int router2_size;
} CommandMap;

void SetupCommandRouterMap();

void CommandRouter1(char* command, WebDatabase *db);
void CommandRouter2(char* command, char* extra, WebDatabase *db, LoadConfig *config);

#endif