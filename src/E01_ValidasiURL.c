#include "website.h"
#include "load.h"
#include <string.h>
#include <stdio.h>

int ValidasiURL(const char* url) {
    int len = strlen(url);
    
    // 1. Validasi Panjang Total & Karakter Pertama/Terakhir
    if (len < 4 || len > 255) return 0; 
    if (url[0] == '-' || url[len - 1] == '-') return 0; 

    // Cari posisi titik ('.') pertama dan terakhir
    const char* first_dot = strchr(url, '.');
    const char* last_dot = strrchr(url, '.');
    
    if (first_dot == NULL || first_dot == url || last_dot == (url + len - 1)) {
        return 0;
    }

    // 2. Validasi Nama Domain (Sebelum titik pertama)
    int domain_len = first_dot - url;
    if (domain_len < 1 || domain_len > 63) return 0;
    if (*(first_dot - 1) == '-') return 0; 

    for (int i = 0; i < domain_len; i++) {
        char c = url[i];
        // Validasi Manual isalnum: Huruf besar (A-Z), huruf kecil (a-z), atau angka (0-9)
        int is_alphanumeric = ((c >= 'A' && c <= 'Z') || 
                               (c >= 'a' && c <= 'z') || 
                               (c >= '0' && c <= '9'));
        
        if (!is_alphanumeric && c != '-') {
            return 0; 
        }
    }

    // 3. Validasi Ekstensi (Setelah titik pertama sampai akhir)
    const char* current = first_dot;
    while (*current != '\0') {
        if (*current == '.') {
            current++; 
            int ext_len = 0;
            
            // Validasi Manual isalpha: Hanya huruf (A-Z atau a-z)
            while ((*current >= 'A' && *current <= 'Z') || (*current >= 'a' && *current <= 'z')) {
                ext_len++;
                current++;
            }
            
            // Ekstensi minimal 2 huruf
            if (ext_len < 2) return 0;
            
            if (*current != '.' && *current != '\0') return 0;
        } else {
            return 0;
        }
    }

    return 1; 
}