#ifndef HISTORY_H
#define HISTORY_H

#define HISTORY_MAX_AMOUNT 50 // Sesuaikan dengan kebutuhan/kebebasan spesifikasi
#define MAX_URL_LEN 100

typedef struct {
    char web_url[MAX_URL_LEN];
    char access_time[6]; // Menyimpan format waktu "HH:MM" seperti di spek (contoh: "14:05")
} HistoryEntry;

typedef struct {
    HistoryEntry entries[HISTORY_MAX_AMOUNT];
    int history_count;
} GlobalHistory;

#endif