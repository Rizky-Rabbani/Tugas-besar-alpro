#ifndef SAVE_H
#define SAVE_H

#include "load.h"
#include "website.h"

int SaveData(WebDatabase *db, LoadConfig *config, char *folder);
int SaveWebPages(WebDatabase *db, char *folder);
int SaveLinkedPages(WebDatabase *db, char *folder);
int SaveConfigFile(WebDatabase *db, LoadConfig *config, char *folder);

#endif