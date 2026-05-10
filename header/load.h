#ifndef LOAD_H
#define LOAD_H

#include "website.h"

#define DEFAULT_CACHE_MAX_AMOUNT 10
#define DEFAULT_TABS_MAX_AMOUNT 10
#define DEFAULT_DOWNLOAD_MAX_AMOUNT 5
#define DEFAULT_MAX_WEB_PAGES 100
#define MAX_PATH_LENGTH 300
#define MAX_CONTENT_LENGTH 5000
#define MAX_LINE_LENGTH 6000

typedef struct {
    int cache_max_amount;
    int tabs_max_amount;
    int download_max_amount;
    int max_web_pages;
} LoadConfig;

void InitWebDatabase(WebDatabase *db);
void FreeWebDatabase(WebDatabase *db);
int LoadData(WebDatabase *db, LoadConfig *config, char *folder);
int LoadWebPages(WebDatabase *db, char *folder);
int LoadLinkedPages(WebDatabase *db, char *folder);
int LoadConfigFile(LoadConfig *config, char *folder);

int GetWebsiteIndexById(WebDatabase *db, int id);
int GetWebsiteIndexByUrl(WebDatabase *db, char *url);
void PrintDatabase(WebDatabase *db);
void PrintLinkedPagesFromUrl(WebDatabase *db, char *url);
void PrintLoadConfig(LoadConfig config);

#endif
