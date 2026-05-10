#include <stdio.h>
#include "load.h"

int main(int argc, char *argv[])
{
    WebDatabase db;
    LoadConfig config;
    char *folder = "config/";

    if (argc >= 2)
    {
        folder = argv[1];
    }

    InitWebDatabase(&db);

    if (LoadData(&db, &config, folder))
    {
        printf("\nJumlah halaman: %d\n\n", db.website_count);
        PrintLoadConfig(config);
        printf("\n");
        PrintDatabase(&db);
        printf("\n");
        PrintLinkedPagesFromUrl(&db, "gajahsumatera.com");
    }

    FreeWebDatabase(&db);
    return 0;
}