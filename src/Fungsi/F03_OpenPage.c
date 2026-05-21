#include "website.h"
#include "load.h"
#include <stdio.h>
#include <string.h>

void open(WebDatabase *db, char* link) {
    int i, j;
    int idx_web = -1; // Menampung indeks website utama yang akan diproses

    // perika cache
    int idx_cache = GetCacheIndexByUrl(db, link);

    if (idx_cache != -1)
    {
        // CACHE HIT: Teks penanda opsional untuk debugging asisten/dosen praktikum
        printf("[CACHE HIT] Mengambil data langsung dari memori cache...\n");
        
        // Catat riwayat kunjungan ke tab aktif menggunakan data dari cache
        InputTab(db, db->Cache[idx_cache]);
        
        // Cari indeks website asli di database global untuk kebutuhan cetak Linked Pages (Matrix)
        idx_web = GetWebsiteIndexByUrl(db, link);
    }

    // kalo gaada di cache, cek di database
    else
    {
        idx_web = GetWebsiteIndexByUrl(db, link);

        if (idx_web == -1)
        {
            printf("URL %s tidak ditemukan.\n", link);
            return;
        }

        printf("[CACHE MISS] Membaca database global...\n");

        // Catat riwayat kunjungan ke tab aktif
        InputTab(db, db->Database[idx_web]);

        // PENTING: Masukkan website yang baru dibaca dari database ini ke dalam Cache
        InsertToCache(db, db->Database[idx_web]);
    }

    // Cetak konten utama website
    printf("\n%s\n", db->Database[idx_web].content);

    // Menampilkan linked pages berdasarkan ADT matrix
    printf("\nLinked pages :\n");
    int nomor_tautan = 1;

    for(j = 0; j < db->website_count; j++) {
        if(db->matrix[idx_web][j] == 1) {
            printf("[%d] %s\n", nomor_tautan, db->Database[j].web_url);
            nomor_tautan++;
        }
    }

    if(nomor_tautan == 1) 
    {
        printf("(Tidak ada website yang tertaut)\n");
    }
}