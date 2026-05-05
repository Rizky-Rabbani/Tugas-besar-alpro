#ifndef WEBSITE_H
#define WEBSITE_H

//Tipe data WebSite
typedef struct 
{
    
    char *URL;
    char *CONTENT;
    
}WebSite;

//Deklarasi variabel untuk database.c
extern const WebSite database[]; /*Variabel array untuk nyimpen semua website*/
extern const int jumlah_website; /*Variabel integer buat ngitung jumlah website di database.c*/

#endif
