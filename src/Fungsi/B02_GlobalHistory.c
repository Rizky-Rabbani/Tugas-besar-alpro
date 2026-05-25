#include "website.h"
#include <stdio.h>
#include <string.h>

// menggunakan "simulasi waktu" karena penggunaan library time.h dilarang
static void GetSimulatedTime(char *output) {
    static int dummy_hour = 14;
    static int dummy_min = 0;
    
    // Setiap kali halaman dibuka, waktu disimulasikan maju sedikit
    dummy_min += 1;
    if (dummy_min >= 60) {
        dummy_min = 0;
        dummy_hour = (dummy_hour + 1) % 24;
    }
    sprintf(output, "%02d:%02d", dummy_hour, dummy_min);
}

// Inisialisasi awal Global History
void InitGlobalHistory(WebDatabase *db) {
    db->HistoryGlobal.history_count = 0;
    for (int i = 0; i < HISTORY_MAX_AMOUNT; i++) {
        db->HistoryGlobal.entries[i].web_url[0] = '\0';
        db->HistoryGlobal.entries[i].access_time[0] = '\0';
    }
}

// Prosedur untuk mencatat atau memperbarui history
void RecordGlobalHistory(WebDatabase *db, char *url) {
    char current_time[6];
    GetSimulatedTime(current_time);

    int existing_idx = -1;

    // LANGKAH A: Cari apakah URL sudah ada di dalam history (Unique URL Check)
    for (int i = 0; i < db->HistoryGlobal.history_count; i++) {
        if (strcmp(db->HistoryGlobal.entries[i].web_url, url) == 0) {
            existing_idx = i;
            break;
        }
    }

    if (existing_idx != -1) {
        // KASUS: URL sudah ada -> Geser elemen di atasnya ke bawah, pindahkan URL ke indeks 0
        HistoryEntry target = db->HistoryGlobal.entries[existing_idx];
        strcpy(target.access_time, current_time); // Update waktu akses terbaru

        for (int i = existing_idx; i > 0; i--) {
            db->HistoryGlobal.entries[i] = db->HistoryGlobal.entries[i - 1];
        }
        db->HistoryGlobal.entries[0] = target;
    } 
    else {
        // KASUS: URL Baru
        if (db->HistoryGlobal.history_count < HISTORY_MAX_AMOUNT) {
            // Jika kapasitas belum penuh, geser semua ke bawah untuk memberi ruang di indeks 0
            for (int i = db->HistoryGlobal.history_count; i > 0; i--) {
                db->HistoryGlobal.entries[i] = db->HistoryGlobal.entries[i - 1];
            }
            strcpy(db->HistoryGlobal.entries[0].web_url, url);
            strcpy(db->HistoryGlobal.entries[0].access_time, current_time);
            db->HistoryGlobal.history_count++;
        } 
        else {
            // Jika kapasitas sudah penuh, elemen terakhir (terlama) otomatis terbuang/tertimpa
            for (int i = HISTORY_MAX_AMOUNT - 1; i > 0; i--) {
                db->HistoryGlobal.entries[i] = db->HistoryGlobal.entries[i - 1];
            }
            strcpy(db->HistoryGlobal.entries[0].web_url, url);
            strcpy(db->HistoryGlobal.entries[0].access_time, current_time);
        }
    }
}

// 3. Perintah untuk menampilkan isi Global History ke layar (Command: history)
void PrintGlobalHistory(WebDatabase *db) {
    if (db->HistoryGlobal.history_count == 0) {
        printf("Riwayat kosong, belum ada halaman yang pernah dibuka.\n");
        return;
    }

    printf("Riwayat halaman yang pernah dikunjungi:\n");
    for (int i = 0; i < db->HistoryGlobal.history_count; i++) {
        printf("[%d] %s (%s)\n", i + 1, 
               db->HistoryGlobal.entries[i].web_url, 
               db->HistoryGlobal.entries[i].access_time);
    }
}