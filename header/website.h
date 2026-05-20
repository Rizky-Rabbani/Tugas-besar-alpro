#ifndef WEBSITE_H
#define WEBSITE_H

#define CACHE_MAX_AMOUNT 10
#define TABS_MAX_AMOUNT 10
#define DOWNLOAD_MAX_AMOUNT 5
#define MAX_WEB_PAGES 100

// Tipe data Website
typedef struct{
    int id; 
    char web_url[100];
    char* content;

}WebSite;

// Satu tab isinya maksimal 10 website //
typedef struct{

    int id;
    char nama_tab[100];
    WebSite daftar_web[TABS_MAX_AMOUNT];
    int web_count;
    int current_web_idx;

}TabState;

// Total ada 10 Tab maksimal yang bisa dibuka
typedef struct{

    TabState daftar_tab[TABS_MAX_AMOUNT];
    int tab_count;
    int current_tab;
    int tab_terakhir;

}TabDatabase;


typedef struct{
    WebSite Database[MAX_WEB_PAGES];
    int matrix[MAX_WEB_PAGES][MAX_WEB_PAGES];
    int website_count;
    TabDatabase Tab;

}WebDatabase;

typedef struct LoadConfig LoadConfig;

void home(WebDatabase *db, LoadConfig *config);

// Router, Perlu akses database untuk diteruskan ke fungsi fitur // 
void CommandRouter1(char* command, WebDatabase *db);
void CommandRouter2(char* command, char* extra, WebDatabase *db, LoadConfig *config);

// Fungsi display ASCII art, ini gausa diperhatiin // 
void printGajah(void);
void printHarimau(void);
void printGajahArt(void);
void printAnya(void);
void printCenturion(void);

// ----- E01 Validasi URL ----- //
int ValidasiURL(const char* url);

// ----- F01 Discover ----- //
void SeedLCG();
unsigned int LCG_Rand();
void Discover(WebDatabase *db);

// ----- F02 Search ----- //
void Search(char* query);

// ----- F03 Open ----- //
void open(WebDatabase* db, char* link);

// ----- F05 Page Management ---- //
void add_page(WebDatabase *db, char *url);
void edit_page(WebDatabase *db, char *url);
void delete_page(WebDatabase *db, char *url);

// ----- F06 Tab management ----- //
void InitTab(WebDatabase* db);
void createtab(TabState* tab, int n);
void newtab(WebDatabase* db);
void closetab(WebDatabase* db);
void checktab(WebDatabase* db);
void InputTab(WebDatabase* db, WebSite web);
void prevtab(WebDatabase* db, int geser);
void nexttab(WebDatabase* db, int geser);

// ----- F07 Web Management ----- // 
void back(WebDatabase* db, int langkah);
void forward(WebDatabase* db, int langkah);

// ----- F08 Tab History ----- // 
void view_tab_history(WebDatabase* db);

// ----- F09 Open Linked ----- //
void OpenLinked(WebDatabase *db, int current_web_id, int nomor_tautan);

#endif
