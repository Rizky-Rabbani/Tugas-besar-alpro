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

void home(WebDatabase *db);

// Router, Perlu akses database untuk diteruskan ke fungsi fitur // 
void CommandRouter1(char* command, WebDatabase *db);
void CommandRouter2(char* command, char* extra, WebDatabase *db);

// Fungsi display ASCII art, ini gausa diperhatiin // 
void printGajah(void);
void printHarimau(void);
void printGajahArt(void);
void printAnya(void);

// ----- E01 Validasi URL ----- //
int ValidasiURL(const char* url);

// ----- F02 Open ----- //
void Search(char* query);

// ----- F03 Open ----- //
void open(WebDatabase* db, char* link);

// ----- F06 Tab management ----- //
void InitTab(WebDatabase* db);
void createtab(TabState* tab, int n);
void newtab(WebDatabase* db);
void closetab(WebDatabase* db);
void checktab(WebDatabase* db);
void InputTab(WebDatabase* db, WebSite web);
void prevtab(WebDatabase* db, int geser);
void nexttab(WebDatabase* db, int geser);
void nexttab(WebDatabase* db, int langkah);
void prevtab(WebDatabase* db, int langkah);


// ----- F07 Web Management ----- // 
void back(WebDatabase* db);
void forward(WebDatabase* db);

#endif
