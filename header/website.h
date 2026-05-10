#ifndef WEBSITE_H
#define WEBSITE_H

#define CACHE_MAX_AMOUNT 10
#define TABS_MAX_AMOUNT 10
#define DOWNLOAD_MAX_AMOUNT 5
#define MAX_WEB_PAGES 100

typedef struct{
    int id; 
    char web_url[100];
    char* content;

}WebSite;

typedef struct{
    WebSite Database[MAX_WEB_PAGES];
    int matrix[MAX_WEB_PAGES][MAX_WEB_PAGES];
    int website_count;
}WebDatabase;

void home(void);

void CommandRouter1(char* command);

void CommandRouter2(char* command, char* extra);

void printGajah(void);

void printHarimau(void);

void printGajahArt(void);

void printAnya(void);

#endif
