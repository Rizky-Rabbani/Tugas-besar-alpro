#include "website.h"
#include "load.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void open(WebDatabase *db, char* link) {
    int i, j;
    int found = 0;

    for(i = 0; i < db->website_count; i++) {
        if(strcmp(link, db->Database[i].web_url) == 0) 
        {
            // 1. Catat riwayat kunjungan ke tab aktif terlebih dahulu agar state sinkron
            InputTab(db, db->Database[i]);
            found = 1;

            // 2. Tampilkan konten utama website
            printf("\n%s\n", db->Database[i].content);

            // 3. FITUR WEB GRAPH: Menampilkan linked pages berdasarkan adjacency matrix
            printf("\nLinked pages :\n");
            int nomor_tautan = 1;

            // Iterasi kolom pada baris indeks 'i' (website yang sedang dibuka)
            for(j = 0; j < db->website_count; j++) {
                
                // Jika bernilai 1, artinya ada tautan dari website 'i' ke website 'j'
                if(db->matrix[i][j] == 1) {
                    printf("[%d] %s\n", nomor_tautan, db->Database[j].web_url);
                    nomor_tautan++;
                }
            }

            // Jika setelah dicek satu baris tidak ada angka 1 sama sekali
            if(nomor_tautan == 1) 
            {
                printf("(Tidak ada website yang tertaut)\n");
            }

            return;
        }
    }
    
    if(!found) {
        printf("URL %s tidak ditemukan.\n", link);
    }
}