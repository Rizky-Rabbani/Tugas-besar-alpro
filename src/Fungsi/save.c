#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


static void WriteEscapedContent(FILE *file, char *content)
{
    int i = 0;

    while (content[i] != '\0')
    {
        if (content[i] == '\n')
        {
            fprintf(file, "\\n");
        }
        else if (content[i] == '"')
        {
            fprintf(file, "\"\"");
        }
        else
        {
            fputc(content[i], file);
        }

        i++;
    }
}

int SaveData(WebDatabase *db, LoadConfig *config, char *folder)
{
    struct stat st = {0};

    printf("Saving data into %s folder...\n", folder);

    if (stat(folder, &st) == -1)
    {
        if (mkdir(folder, 0700) != 0)
        {
            printf("Error: gagal membuat folder %s\n", folder);
            return 0;
        }
    }

    if (!SaveConfigFile(db, config, folder))
    {
        printf("Error: gagal menyimpan config.txt\n");
        return 0;
    }

    if (!SaveWebPages(db, folder))
    {
        printf("Error: gagal menyimpan web_pages.csv\n");
        return 0;
    }

    if (!SaveLinkedPages(db, folder))
    {
        printf("Error: gagal menyimpan linked_pages.csv\n");
        return 0;
    }

    printf("Data saved!\n");
    return 1;
}

int SaveConfigFile(WebDatabase *db, LoadConfig *config, char *folder)
{
    FILE *file;
    char path[MAX_PATH_LENGTH];

    sprintf(path, "%s/config.txt", folder);
    file = fopen(path, "w");

    if (file == NULL)
    {
        return 0;
    }

    // BARIS 1: Konstanta Konfigurasi Global (Sudah benar dari teman Anda)
    fprintf(file, "%d %d %d %d\n",
            config->cache_max_amount,
            config->tabs_max_amount,
            config->download_max_amount,
            config->max_web_pages);

    // BARIS 2: Status Tab Global (Jumlah tab terbuka dan indeks tab aktif)
    // Catatan: sesuaikan nama variabel struct .tab_count dan .current_tab dengan struct Anda
    fprintf(file, "%d %d\n", db->Tab.tab_count, db->Tab.current_tab);

    // BARIS 3 & 4: Metadata TAB dan Data Riwayat URL (Melakukan looping untuk setiap tab yang terbuka)
    int i, j;
    for (i = 0; i < db->Tab.tab_count; i++)
    {
        TabState *tab = &db->Tab.daftar_tab[i];

        // BARIS 3: Nama TAB, Total Riwayat (web_count), dan Pointer Posisi Riwayat (current_web_idx + 1 agar tidak bernilai 0)
        // Ditambah 1 pada indeks aktif karena spesifikasi contoh menggunakan basis 1 (1-indexed)
        int posisi_aktif = tab->current_web_idx + 1; 
        fprintf(file, "%s %d %d\n", tab->nama_tab, tab->web_count, posisi_aktif);

        // BARIS 4: Data Riwayat URL dipisahkan oleh spasi
        for (j = 0; j < tab->web_count; j++)
        {
            fprintf(file, "%s", tab->daftar_web[j].web_url);
            if (j < tab->web_count - 1)
            {
                fprintf(file, " "); // Beri spasi antar-URL, kecuali URL terakhir
            }
        }
        fprintf(file, "\n"); // Newline setelah mendaftar riwayat satu tab
    }

    fclose(file);
    return 1;
}

int SaveWebPages(WebDatabase *db, char *folder)
{
    FILE *file;
    char path[MAX_PATH_LENGTH];
    int i;

    sprintf(path, "%s/web_pages.csv", folder);
    file = fopen(path, "w");

    if (file == NULL)
    {
        return 0;
    }

    fprintf(file, "id,web_url,content\n");

    for (i = 0; i < db->website_count; i++)
    {
        fprintf(file, "%d,\"%s\",\"",
                db->Database[i].id,
                db->Database[i].web_url);

        WriteEscapedContent(file, db->Database[i].content);

        fprintf(file, "\"\n");
    }

    fclose(file);
    return 1;
}

int SaveLinkedPages(WebDatabase *db, char *folder)
{
    FILE *file;
    char path[MAX_PATH_LENGTH];
    int i, j;
    int id_relasi = 1;

    sprintf(path, "%s/linked_pages.csv", folder);
    file = fopen(path, "w");

    if (file == NULL)
    {
        return 0;
    }

    fprintf(file, "id,id_sumber,id_tujuan\n");

    for (i = 0; i < db->website_count; i++)
    {
        for (j = 0; j < db->website_count; j++)
        {
            if (db->matrix[i][j] == 1)
            {
                fprintf(file, "%d,%d,%d\n",
                        id_relasi,
                        db->Database[i].id,
                        db->Database[j].id);

                id_relasi++;
            }
        }
    }

    fclose(file);
    return 1;
}