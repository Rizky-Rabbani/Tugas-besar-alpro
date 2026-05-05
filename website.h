#ifndef WEBSITE_H
#define WEBSITE_H

//Tipe data WebSite
typedef struct 
{
    
    char *URL;
    char *CONTENT;
    
}WebSite;

//Deklarasi variabel untuk database.c
extern const WebSite database[];
extern const int jumlah_website;

#endif