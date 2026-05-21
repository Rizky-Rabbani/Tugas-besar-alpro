#include "website.h"
#include <string.h>
#include <stdio.h>

// Fungsi untuk mencari website di dalam Cache berdasarkan URL
int GetCacheIndexByUrl(WebDatabase *db, char *url)
{
    int i;
    // Lakukan looping hanya sebanyak jumlah kapasitas maksimum cache kelompok Anda
    for (i = 0; i < CACHE_MAX_AMOUNT; i++)
    {
        // Pastikan slot cache tidak kosong sebelum membandingkan string
        if (db->Cache[i].web_url[0] != '\0' && strcmp(db->Cache[i].web_url, url) == 0)
        {
            return i; 
        }
    }
    return -1; 
}

// Fungsi untuk memasukkan website baru ke dalam Cache
void InsertToCache(WebDatabase *db, WebSite web)
{
    int i;
    int idx_kosong = -1;

    // Cari apakah ada slot cache yang masih kosong
    for (i = 0; i < CACHE_MAX_AMOUNT; i++)
    {
        if (db->Cache[i].web_url[0] == '\0')
        {
            idx_kosong = i;
            break;
        }
    }

    // Jika ada slot kosong, langsung masukkan data ke slot tersebut
    if (idx_kosong != -1)
    {
        db->Cache[idx_kosong] = web;
    }
    else
    {
        // JIKA CACHE PENUH: Geser semua elemen ke kiri 
        for (i = 0; i < CACHE_MAX_AMOUNT - 1; i++)
        {
            db->Cache[i] = db->Cache[i + 1];
        }

        // Masukkan data website terbaru di slot paling akhir 
        db->Cache[CACHE_MAX_AMOUNT - 1] = web;
    }
}