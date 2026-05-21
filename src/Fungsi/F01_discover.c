#include "website.h"
#include "load.h"
#include <stdio.h>

#define LCG_A 1103515245
#define LCG_C 12345
#define LCG_M 2147483648

static unsigned long long lcg_seed = 1;


void SeedLCG(WebDatabase *db, LoadConfig *config) {
    // Kombinasi nilai dari database count dan batas maksimum cache/tab
    lcg_seed = (unsigned long long)(db->website_count * 7 + config->cache_max_amount * 31 + 13);
    
    // Lakukan kocokan awal
    lcg_seed = (LCG_A * lcg_seed + LCG_C) % LCG_M;
}

unsigned int LCG_Rand() {
    lcg_seed = (LCG_A * lcg_seed + LCG_C) % LCG_M;
    return (unsigned int)lcg_seed;
}

void Discover(WebDatabase *db) {
    int total_pages = db->website_count; 

    if (total_pages == 0) {
        printf("Database kosong. Tidak ada halaman untuk ditampilkan.\n");
        return;
    }

    printf("\nBerikut adalah beberapa halaman yang mungkin menarik untukmu:\n");

    if (total_pages <= 5) {
        for (int i = 0; i < total_pages; i++) {
            printf("- %s\n", db->Database[i].web_url); 
        }
        return;
    }

    int chosen_indices[5];
    int chosen_count = 0;

    while (chosen_count < 5) {
        int random_index = LCG_Rand() % total_pages;
        int is_duplicate = 0;
        
        for (int i = 0; i < chosen_count; i++) {
            if (chosen_indices[i] == random_index) {
                is_duplicate = 1;
                break;
            }
        }

        if (!is_duplicate) {
            chosen_indices[chosen_count] = random_index;
            chosen_count++;
        }
    }

    for (int i = 0; i < 5; i++) {
        int idx = chosen_indices[i];
        printf("- %s\n", db->Database[idx].web_url);
    }
}