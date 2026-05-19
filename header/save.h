#ifndef SAVE_H
#define SAVE_H

#include "website.h"

int SaveData(WebDatabase *db, char *folder);
int SaveConfigFile(WebDatabase *db, char *folder);
int SaveWebPages(WebDatabase *db, char *folder);
int SaveLinkedPages(WebDatabase *db, char *folder);

#endif