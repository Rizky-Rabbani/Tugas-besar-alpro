#include "website.h"
#include "load.h"
#include <stdio.h>
#include <string.h>

static int HitungTicks(char *url)
{
    return (int)(strlen(url) / 5) + 2;
}

static void BuatNamaFile(char *url, char *filename)
{
    int i = 0;

    while (url[i] != '\0' && url[i] != '.' && i < 90)
    {
        filename[i] = url[i];
        i++;
    }

    filename[i] = '\0';
    strcat(filename, ".txt");
}

static int TulisFileDownload(DownloadItem item, char *filename)
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        return 0;
    }

    fprintf(file, "%s\n", item.web.content);
    fclose(file);

    return 1;
}

void InitDownloadQueue(WebDatabase *db)
{
    db->Download.front = 0;
    db->Download.rear = -1;
    db->Download.count = 0;
}

void download(WebDatabase *db, LoadConfig *config, char *url)
{
    int idx_web;
    int ticks;
    int max_download;

    if (!ValidasiURL(url))
    {
        printf("ERROR: Format URL tidak valid sesuai aturan E01!\n");
        return;
    }

    idx_web = GetWebsiteIndexByUrl(db, url);

    if (idx_web == -1)
    {
        printf("URL %s tidak ditemukan.\n", url);
        return;
    }

    max_download = config->download_max_amount;

    if (max_download > DOWNLOAD_MAX_AMOUNT)
    {
        max_download = DOWNLOAD_MAX_AMOUNT;
    }

    if (db->Download.count >= max_download)
    {
        printf("Download tidak diterima, antrian sudah penuh.\n");
        return;
    }

    ticks = HitungTicks(url);

    db->Download.rear = (db->Download.rear + 1) % DOWNLOAD_MAX_AMOUNT;
    db->Download.items[db->Download.rear].web = db->Database[idx_web];
    db->Download.items[db->Download.rear].total_ticks = ticks;
    db->Download.items[db->Download.rear].remaining_ticks = ticks;
    db->Download.count++;

    if (db->Download.count == 1)
    {
        printf("Download %s (%d ticks)\n", url, ticks);
    }
    else
    {
        printf("Download %s (%d ticks) -> antrian no %d, %d ticks masih tertunda dari antrian sebelumnya\n",
               url,
               ticks,
               db->Download.count,
               db->Download.items[db->Download.front].remaining_ticks);
    }
}

void tick_download(WebDatabase *db)
{
    DownloadItem *aktif;
    char filename[100];

    if (db->Download.count == 0)
    {
        printf("Antrian download saat ini kosong.\n");
        return;
    }

    aktif = &db->Download.items[db->Download.front];

    aktif->remaining_ticks--;

    if (aktif->remaining_ticks > 0)
    {
        printf("Downloading %s... (%d ticks tersisa)\n",
               aktif->web.web_url,
               aktif->remaining_ticks);
        return;
    }

    BuatNamaFile(aktif->web.web_url, filename);

    if (TulisFileDownload(*aktif, filename))
    {
        printf("%s selesai didownload, ke file %s.\n",
               aktif->web.web_url,
               filename);
    }
    else
    {
        printf("%s selesai didownload, tetapi gagal membuat file %s.\n",
               aktif->web.web_url,
               filename);
    }

    db->Download.front = (db->Download.front + 1) % DOWNLOAD_MAX_AMOUNT;
    db->Download.count--;

    if (db->Download.count == 0)
    {
        db->Download.front = 0;
        db->Download.rear = -1;
    }
    else
    {
        aktif = &db->Download.items[db->Download.front];

        printf("Lanjut downloading %s... (%d ticks tersisa)\n",
               aktif->web.web_url,
               aktif->remaining_ticks);
    }
}