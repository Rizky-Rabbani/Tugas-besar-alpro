#include "load.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RemoveNewline(char *s)
{
    int len = strlen(s);

    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'))
    {
        s[len - 1] = '\0';
        len--;
    }
}

static char *CopyString(char *s)
{
    char *result = (char*) malloc((strlen(s) + 1) * sizeof(char));

    if (result != NULL)
    {
        strcpy(result, s);
    }

    return result;
}

static void ConvertSlashNToNewline(char *s)
{
    int i = 0;
    int j = 0;
    char temp[MAX_CONTENT_LENGTH];

    while (s[i] != '\0' && j < MAX_CONTENT_LENGTH - 1)
    {
        if (s[i] == '\\' && s[i + 1] == 'n')
        {
            temp[j] = '\n';
            i += 2;
            j++;
        }
        else
        {
            temp[j] = s[i];
            i++;
            j++;
        }
    }

    temp[j] = '\0';
    strcpy(s, temp);
}

static void InitLoadConfig(LoadConfig *config)
{
    config->cache_max_amount = DEFAULT_CACHE_MAX_AMOUNT;
    config->tabs_max_amount = DEFAULT_TABS_MAX_AMOUNT;
    config->download_max_amount = DEFAULT_DOWNLOAD_MAX_AMOUNT;
    config->max_web_pages = DEFAULT_MAX_WEB_PAGES;
}

static int ParseQuotedField(char *line, int *idx, char *output, int max_output)
{
    int j = 0;

    if (line[*idx] != '"')
    {
        return 0;
    }

    (*idx)++;

    while (line[*idx] != '\0' && j < max_output - 1)
    {
        if (line[*idx] == '"' && line[*idx + 1] == '"')
        {
            output[j] = '"';
            j++;
            (*idx) += 2;
        }
        else if (line[*idx] == '"')
        {
            (*idx)++;
            output[j] = '\0';
            return 1;
        }
        else
        {
            output[j] = line[*idx];
            j++;
            (*idx)++;
        }
    }

    output[j] = '\0';
    return 1;
}

static int ParseWebPageLine(char *line, int *id, char *url, char *content)
{
    int idx = 0;
    char id_string[30];
    int j = 0;

    while (line[idx] != ',' && line[idx] != '\0' && j < 29)
    {
        id_string[j] = line[idx];
        idx++;
        j++;
    }
    id_string[j] = '\0';

    if (line[idx] != ',')
    {
        return 0;
    }

    *id = atoi(id_string);
    idx++;

    if (!ParseQuotedField(line, &idx, url, 100))
    {
        return 0;
    }

    if (line[idx] != ',')
    {
        return 0;
    }

    idx++;

    if (!ParseQuotedField(line, &idx, content, MAX_CONTENT_LENGTH))
    {
        return 0;
    }

    ConvertSlashNToNewline(content);
    return 1;
}

void InitWebDatabase(WebDatabase *db)
{
    int i, j;

    db->website_count = 0;

    for (i = 0; i < MAX_WEB_PAGES; i++)
    {
        db->Database[i].id = 0;
        db->Database[i].web_url[0] = '\0';
        db->Database[i].content = NULL;

        for (j = 0; j < MAX_WEB_PAGES; j++)
        {
            db->matrix[i][j] = 0;
        }
    }
}

void FreeWebDatabase(WebDatabase *db)
{
    int i;

    for (i = 0; i < db->website_count; i++)
    {
        if (db->Database[i].content != NULL)
        {
            free(db->Database[i].content);
            db->Database[i].content = NULL;
        }
    }

    InitWebDatabase(db);
}

int GetWebsiteIndexById(WebDatabase *db, int id)
{
    int i;

    for (i = 0; i < db->website_count; i++)
    {
        if (db->Database[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

int GetWebsiteIndexByUrl(WebDatabase *db, char *url)
{
    int i;

    for (i = 0; i < db->website_count; i++)
    {
        if (strcmp(db->Database[i].web_url, url) == 0)
        {
            return i;
        }
    }

    return -1;
}

int LoadWebPages(WebDatabase *db, char *folder)
{
    FILE *file;
    char path[MAX_PATH_LENGTH];
    char line[MAX_LINE_LENGTH];
    int id;
    char url[100];
    char content[MAX_CONTENT_LENGTH];

    sprintf(path, "%s/web_pages.csv", folder);
    file = fopen(path, "r");

    if (file == NULL)
    {
        return 0;
    }

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) != NULL)
    {
        RemoveNewline(line);

        if (db->website_count >= MAX_WEB_PAGES)
        {
            printf("Peringatan: jumlah halaman melebihi MAX_WEB_PAGES. Data setelah batas tidak di-load.\n");
            break;
        }

        if (ParseWebPageLine(line, &id, url, content))
        {
            db->Database[db->website_count].id = id;
            strcpy(db->Database[db->website_count].web_url, url);
            db->Database[db->website_count].content = CopyString(content);
            db->website_count++;
        }
        else
        {
            printf("Peringatan: baris web_pages.csv tidak valid dan dilewati.\n");
        }
    }

    fclose(file);
    return 1;
}

int LoadLinkedPages(WebDatabase *db, char *folder)
{
    FILE *file;
    char path[MAX_PATH_LENGTH];
    char line[300];
    int id_relasi;
    int id_sumber;
    int id_tujuan;
    int idx_sumber;
    int idx_tujuan;
    int i, j;

    sprintf(path, "%s/linked_pages.csv", folder);
    file = fopen(path, "r");

    if (file == NULL)
    {
        return 0;
    }

    for (i = 0; i < MAX_WEB_PAGES; i++)
    {
        for (j = 0; j < MAX_WEB_PAGES; j++)
        {
            db->matrix[i][j] = 0;
        }
    }

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) != NULL)
    {
        RemoveNewline(line);

        if (sscanf(line, "%d,%d,%d", &id_relasi, &id_sumber, &id_tujuan) == 3)
        {
            idx_sumber = GetWebsiteIndexById(db, id_sumber);
            idx_tujuan = GetWebsiteIndexById(db, id_tujuan);

            if (idx_sumber != -1 && idx_tujuan != -1)
            {
                db->matrix[idx_sumber][idx_tujuan] = 1;
            }
        }
    }

    fclose(file);
    return 1;
}

int LoadConfigFile(LoadConfig *config, char *folder)
{
    FILE *file;
    char path[MAX_PATH_LENGTH];

    InitLoadConfig(config);

    sprintf(path, "%s/config.txt", folder);
    file = fopen(path, "r");

    if (file == NULL)
    {
        return 0;
    }

    fscanf(file, "%d %d %d %d",
           &config->cache_max_amount,
           &config->tabs_max_amount,
           &config->download_max_amount,
           &config->max_web_pages);

    fclose(file);
    return 1;
}

int LoadData(WebDatabase *db, LoadConfig *config, char *folder)
{
    WebDatabase temp_db;
    LoadConfig temp_config;

    printf("Loading new data from %s folder...\n", folder);

    InitWebDatabase(&temp_db);
    InitLoadConfig(&temp_config);

    if (!LoadWebPages(&temp_db, folder))
    {
        printf("Error: %s folder not found atau web_pages.csv tidak ditemukan!\n", folder);
        return 0;
    }

    if (!LoadLinkedPages(&temp_db, folder))
    {
        FreeWebDatabase(&temp_db);
        printf("Error: linked_pages.csv tidak ditemukan di folder %s!\n", folder);
        return 0;
    }

    LoadConfigFile(&temp_config, folder);

    FreeWebDatabase(db);
    *db = temp_db;
    *config = temp_config;

    printf("New data loaded\n");
    return 1;
}

void PrintDatabase(WebDatabase *db)
{
    int i;

    printf("=== DAFTAR WEB YANG TER-LOAD ===\n");

    if (db->website_count == 0)
    {
        printf("Belum ada data website.\n");
        return;
    }

    for (i = 0; i < db->website_count; i++)
    {
        printf("[%d] %s\n", db->Database[i].id, db->Database[i].web_url);
    }
}

void PrintLinkedPagesFromUrl(WebDatabase *db, char *url)
{
    int idx_sumber;
    int i;
    int nomor = 1;

    idx_sumber = GetWebsiteIndexByUrl(db, url);

    if (idx_sumber == -1)
    {
        printf("URL %s tidak ditemukan.\n", url);
        return;
    }

    printf("Linked pages dari %s:\n", url);

    for (i = 0; i < db->website_count; i++)
    {
        if (db->matrix[idx_sumber][i] == 1)
        {
            printf("[%d] %s\n", nomor, db->Database[i].web_url);
            nomor++;
        }
    }

    if (nomor == 1)
    {
        printf("Tidak ada linked page.\n");
    }
}

void PrintLoadConfig(LoadConfig config)
{
    printf("=== KONFIGURASI ===\n");
    printf("CACHE_MAX_AMOUNT    : %d\n", config.cache_max_amount);
    printf("TABS_MAX_AMOUNT     : %d\n", config.tabs_max_amount);
    printf("DOWNLOAD_MAX_AMOUNT : %d\n", config.download_max_amount);
    printf("MAX_WEB_PAGES       : %d\n", config.max_web_pages);
}
