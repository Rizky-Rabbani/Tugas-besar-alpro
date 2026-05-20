#include "website.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE 1000
#define MAX_CONTENT_LENGTH 10000

static void RemoveNewlineF05(char *str)
{
    int len = strlen(str);

    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

static int FindWebIndexByUrl(WebDatabase *db, char *url)
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

static int FindMaxWebId(WebDatabase *db)
{
    int i;
    int max_id = 0;

    for (i = 0; i < db->website_count; i++)
    {
        if (db->Database[i].id > max_id)
        {
            max_id = db->Database[i].id;
        }
    }

    return max_id;
}

static char *DuplicateStringF05(char *src)
{
    char *result;

    result = (char *) malloc((strlen(src) + 1) * sizeof(char));

    if (result != NULL)
    {
        strcpy(result, src);
    }

    return result;
}

static void ClearOutgoingLinks(WebDatabase *db, int idx)
{
    int j;

    for (j = 0; j < db->website_count; j++)
    {
        db->matrix[idx][j] = 0;
    }
}

static void ClearAllLinksRelatedToPage(WebDatabase *db, int idx)
{
    int i;

    for (i = 0; i < db->website_count; i++)
    {
        db->matrix[idx][i] = 0;
        db->matrix[i][idx] = 0;
    }
}

static void UpdatePageInTabs(WebDatabase *db, char *url, WebSite updated_page)
{
    int i, j;

    for (i = 0; i < db->Tab.tab_count; i++)
    {
        for (j = 0; j < db->Tab.daftar_tab[i].web_count; j++)
        {
            if (strcmp(db->Tab.daftar_tab[i].daftar_web[j].web_url, url) == 0)
            {
                db->Tab.daftar_tab[i].daftar_web[j] = updated_page;
            }
        }
    }
}

static void RemovePageFromTabs(WebDatabase *db, char *url)
{
    int i, j, k;

    for (i = 0; i < db->Tab.tab_count; i++)
    {
        j = 0;

        while (j < db->Tab.daftar_tab[i].web_count)
        {
            if (strcmp(db->Tab.daftar_tab[i].daftar_web[j].web_url, url) == 0)
            {
                for (k = j; k < db->Tab.daftar_tab[i].web_count - 1; k++)
                {
                    db->Tab.daftar_tab[i].daftar_web[k] =
                        db->Tab.daftar_tab[i].daftar_web[k + 1];
                }

                db->Tab.daftar_tab[i].web_count--;

                if (db->Tab.daftar_tab[i].web_count == 0)
                {
                    db->Tab.daftar_tab[i].current_web_idx = -1;
                }
                else if (db->Tab.daftar_tab[i].current_web_idx >= db->Tab.daftar_tab[i].web_count)
                {
                    db->Tab.daftar_tab[i].current_web_idx =
                        db->Tab.daftar_tab[i].web_count - 1;
                }
            }
            else
            {
                j++;
            }
        }
    }
}

void add_page(WebDatabase *db, char *url)
{
    int existing_index;
    int new_index;
    int target_index;
    int j;
    char line[MAX_INPUT_LINE];
    char content[MAX_CONTENT_LENGTH];

    existing_index = FindWebIndexByUrl(db, url);

    if (existing_index != -1)
    {
        printf("Sudah terdapat halaman dengan url %s. Gunakan url lain yang belum terdaftar!\n", url);
        return;
    }

    if (db->website_count >= MAX_WEB_PAGES)
    {
        printf("Database halaman web sudah penuh!\n");
        return;
    }

    new_index = db->website_count;

    db->Database[new_index].id = FindMaxWebId(db) + 1;
    strcpy(db->Database[new_index].web_url, url);

    content[0] = '\0';

    printf("Masukkan konten (Akhiri dengan titik '.' di baris baru):\n");

    while (1)
    {
        printf(">>> ");
        fgets(line, MAX_INPUT_LINE, stdin);
        RemoveNewlineF05(line);

        if (strcmp(line, ".") == 0)
        {
            break;
        }

        if (strlen(content) + strlen(line) + 2 < MAX_CONTENT_LENGTH)
        {
            if (strlen(content) > 0)
            {
                strcat(content, "\n");
            }

            strcat(content, line);
        }
        else
        {
            printf("Konten terlalu panjang. Input konten dihentikan.\n");
            break;
        }
    }

    db->Database[new_index].content = DuplicateStringF05(content);

    if (db->Database[new_index].content == NULL)
    {
        printf("Gagal mengalokasikan memori konten!\n");
        return;
    }

    for (j = 0; j < MAX_WEB_PAGES; j++)
    {
        db->matrix[new_index][j] = 0;
        db->matrix[j][new_index] = 0;
    }

    db->website_count++;

    printf("Masukkan linked pages (Ketik 'DONE' jika sudah selesai):\n");

    while (1)
    {
        printf(">>> ");
        fgets(line, MAX_INPUT_LINE, stdin);
        RemoveNewlineF05(line);

        if (strcmp(line, "DONE") == 0)
        {
            break;
        }

        target_index = FindWebIndexByUrl(db, line);

        if (target_index == -1)
        {
            printf("URL tidak ditemukan!\n");
        }
        else if (target_index == new_index)
        {
            printf("Tidak dapat membuat link ke halaman itu sendiri!\n");
        }
        else
        {
            db->matrix[new_index][target_index] = 1;
        }
    }

    printf("Halaman %s berhasil ditambahkan!\n", url);
}

void edit_page(WebDatabase *db, char *url)
{
    int page_index;
    int target_index;
    int j;
    int has_link;
    char line[MAX_INPUT_LINE];
    char content[MAX_CONTENT_LENGTH];

    page_index = FindWebIndexByUrl(db, url);

    if (page_index == -1)
    {
        printf("Tidak ada halaman dengan url %s!\n", url);
        return;
    }

    printf("[Status: Cache-Hit] Mengambil data dari cache...\n\n");

    printf("Konten saat ini:\n");
    printf("%s\n\n", db->Database[page_index].content);

    printf("Linked pages:\n");

    has_link = 0;

    for (j = 0; j < db->website_count; j++)
    {
        if (db->matrix[page_index][j] == 1)
        {
            printf("[%d] %s\n", j + 1, db->Database[j].web_url);
            has_link = 1;
        }
    }

    if (!has_link)
    {
        printf("Tidak ada linked pages.\n");
    }

    printf("\nMasukkan konten baru (akhiri dengan '.' atau ketik '.' saja jika tidak ingin mengubah konten):\n");

    content[0] = '\0';

    while (1)
    {
        printf(">>> ");
        fgets(line, MAX_INPUT_LINE, stdin);
        RemoveNewlineF05(line);

        if (strcmp(line, ".") == 0)
        {
            break;
        }

        if (strlen(content) + strlen(line) + 2 < MAX_CONTENT_LENGTH)
        {
            if (strlen(content) > 0)
            {
                strcat(content, "\n");
            }

            strcat(content, line);
        }
        else
        {
            printf("Konten terlalu panjang. Input konten dihentikan.\n");
            break;
        }
    }

    if (strlen(content) > 0)
    {
        free(db->Database[page_index].content);
        db->Database[page_index].content = DuplicateStringF05(content);

        if (db->Database[page_index].content == NULL)
        {
            printf("Gagal mengalokasikan memori konten baru!\n");
            return;
        }
    }

    printf("Masukkan linked pages baru (Ketik 'DONE' jika sudah selesai, atau ketik 'SKIP' jika tidak ingin mengubah linked pages):\n");

    printf(">>> ");
    fgets(line, MAX_INPUT_LINE, stdin);
    RemoveNewlineF05(line);

    if (strcmp(line, "SKIP") != 0)
    {
        ClearOutgoingLinks(db, page_index);

        while (strcmp(line, "DONE") != 0)
        {
            target_index = FindWebIndexByUrl(db, line);

            if (target_index == -1)
            {
                printf("URL tidak ditemukan!\n");
            }
            else if (target_index == page_index)
            {
                printf("Tidak dapat membuat link ke halaman itu sendiri!\n");
            }
            else
            {
                db->matrix[page_index][target_index] = 1;
            }

            printf(">>> ");
            fgets(line, MAX_INPUT_LINE, stdin);
            RemoveNewlineF05(line);
        }
    }

    UpdatePageInTabs(db, url, db->Database[page_index]);

    printf("Halaman %s berhasil diperbarui!\n", url);
}

void delete_page(WebDatabase *db, char *url)
{
    int page_index;
    int i, j;

    page_index = FindWebIndexByUrl(db, url);

    if (page_index == -1)
    {
        printf("Tidak ada halaman dengan url %s!\n", url);
        return;
    }

    printf("[Status: Cache-Hit] URL ditemukan di cache dan telah dibersihkan.\n");
    printf("Membersihkan relasi linked pages...\n\n");

    ClearAllLinksRelatedToPage(db, page_index);

    RemovePageFromTabs(db, url);

    free(db->Database[page_index].content);

    for (i = page_index; i < db->website_count - 1; i++)
    {
        db->Database[i] = db->Database[i + 1];
    }

    for (i = page_index; i < db->website_count - 1; i++)
    {
        for (j = 0; j < db->website_count; j++)
        {
            db->matrix[i][j] = db->matrix[i + 1][j];
        }
    }

    for (j = page_index; j < db->website_count - 1; j++)
    {
        for (i = 0; i < db->website_count - 1; i++)
        {
            db->matrix[i][j] = db->matrix[i][j + 1];
        }
    }

    db->website_count--;

    for (i = 0; i < MAX_WEB_PAGES; i++)
    {
        db->matrix[db->website_count][i] = 0;
        db->matrix[i][db->website_count] = 0;
    }

    printf("Halaman %s berhasil dihapus!\n", url);
}