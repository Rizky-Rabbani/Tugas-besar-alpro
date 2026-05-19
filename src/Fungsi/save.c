#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef _WIN32
#include <direct.h>
#endif

#define SAVE_MAX_PATH_LENGTH 300

static int MakeDirectoryIfNotExist(char *folder)
{
    struct stat st = {0};

    if (stat(folder, &st) == -1)
    {
#ifdef _WIN32
        return mkdir(folder);
#else
        return mkdir(folder, 0700);
#endif
    }

    return 0;
}

static void WriteEscapedContent(FILE *file, char *content)
{
    int i = 0;

    if (content == NULL)
    {
        return;
    }

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

int SaveData(WebDatabase *db, char *folder)
{
    printf("Saving data into %s folder...\n", folder);

    if (MakeDirectoryIfNotExist(folder) != 0)
    {
        printf("Error: gagal membuat folder %s\n", folder);
        return 0;
    }

    if (!SaveConfigFile(db, folder))
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

int SaveConfigFile(WebDatabase *db, char *folder)
{
    FILE *file;
    char path[SAVE_MAX_PATH_LENGTH];
    int i, j;
    int current_web;

    sprintf(path, "%s/config.txt", folder);

    file = fopen(path, "w");
    if (file == NULL)
    {
        return 0;
    }

    /*
        Baris 1:
        cache_max tabs_max download_max max_web_pages
    */
    fprintf(file, "%d %d %d %d\n",
            CACHE_MAX_AMOUNT,
            TABS_MAX_AMOUNT,
            DOWNLOAD_MAX_AMOUNT,
            MAX_WEB_PAGES);

    /*
        Baris 2:
        jumlah_tab current_tab
    */
    fprintf(file, "%d %d\n",
            db->Tab.tab_count,
            db->Tab.current_tab);

    /*
        Baris berikutnya:
        TABx jumlah_web current_web
        daftar_url_di_tab
    */
    for (i = 0; i < db->Tab.tab_count; i++)
    {
        if (db->Tab.daftar_tab[i].current_web_idx >= 0)
        {
            current_web = db->Tab.daftar_tab[i].current_web_idx + 1;
        }
        else
        {
            current_web = 0;
        }

        fprintf(file, "%s %d %d\n",
                db->Tab.daftar_tab[i].nama_tab,
                db->Tab.daftar_tab[i].web_count,
                current_web);

        for (j = 0; j < db->Tab.daftar_tab[i].web_count; j++)
        {
            fprintf(file, "%s",
                    db->Tab.daftar_tab[i].daftar_web[j].web_url);

            if (j < db->Tab.daftar_tab[i].web_count - 1)
            {
                fprintf(file, " ");
            }
        }

        fprintf(file, "\n");
    }

    fclose(file);
    return 1;
}

int SaveWebPages(WebDatabase *db, char *folder)
{
    FILE *file;
    char path[SAVE_MAX_PATH_LENGTH];
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
    char path[SAVE_MAX_PATH_LENGTH];
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