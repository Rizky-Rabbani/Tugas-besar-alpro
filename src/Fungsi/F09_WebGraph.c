#include "website.h"
#include <stdio.h>
#include <string.h>

void OpenLinked(WebDatabase *db, int current_web_id, int nomor_tautan)
{
    // KONDISI 1: Validasi ketat jika user berada di home atau belum membuka halaman apa pun
    if (current_web_id == -1)
    {
        printf("ERROR: COMMAND HANYA DAPAT DIGUNAKAN SAAT HALAMAN WEB TERBUKA!\n");
        return;
    }

    // Cari indeks array untuk website asal berdasarkan ID-nya
    int idx_sekarang = -1;
    int i;
    for (i = 0; i < db->website_count; i++)
    {
        if (db->Database[i].id == current_web_id)
        {
            idx_sekarang = i;
            break;
        }
    }

    if (idx_sekarang == -1)
    {
        printf("ERROR: COMMAND HANYA DAPAT DIGUNAKAN SAAT HALAMAN WEB TERBUKA!\n");
        return;
    }

    // Hitung total tautan yang dimiliki halaman saat ini untuk validasi batas input
    int total_tautan_tersedia = 0;
    for (i = 0; i < db->website_count; i++)
    {
        if (db->matrix[idx_sekarang][i] == 1)
        {
            total_tautan_tersedia++;
        }
    }

    // Jika halaman memang tidak memiliki outbound link sama sekali
    if (total_tautan_tersedia == 0)
    {
        printf("ERROR: HALAMAN TIDAK MEMILIKI TAUTAN YANG BISA DIBUKA!\n");
        return;
    }

    // Validasi jika input nomor tautan di luar jangkauan (terlalu besar atau <= 0)
    if (nomor_tautan <= 0 || nomor_tautan > total_tautan_tersedia)
    {
        printf("ERROR: HALAMAN TIDAK MEMILIKI TAUTAN YANG BISA DIBUKA!\n");
        return;
    }

    // Telusuri matriks relasi untuk mengekstrak alamat URL target ke-N
    int counter_tautan = 0;
    int idx_target = -1;

    for (i = 0; i < db->website_count; i++)
    {
        if (db->matrix[idx_sekarang][i] == 1)
        {
            counter_tautan++; 
            if (counter_tautan == nomor_tautan)
            {
                idx_target = i; 
                break;
            }
        }
    }

    // Eksekusi pemanggilan halaman target jika lolos seluruh validasi
    if (idx_target != -1)
    {
        char *target_url = db->Database[idx_target].web_url;
        printf("Membuka tautan [%d]: %s...\n", nomor_tautan, target_url);
        open(db, target_url); 
    }
}