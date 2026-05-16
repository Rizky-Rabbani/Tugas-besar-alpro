#include "website.h"
#include <stdio.h>
#include <string.h>

void Search(char* query)
{
    FILE *file = fopen("config/web_pages.csv", "r");

    if(file == NULL)
    {
        printf("File web_pages.csv tidak ditemukan\n");
        return;
    }

    char line[1000];
    int id;
    char url[100];
    char content[1000];

    int found = 0;

    // Skip header
    fgets(line, sizeof(line), file);

    printf("Search result(s) for \"%s\":\n", query);

    while(fgets(line, sizeof(line), file))
    {
        sscanf(line,
               "%d,\"%[^\"]\",\"%[^\"]\"",
               &id,
               url,
               content);

        if(strncmp(url, query, strlen(query)) == 0)
        {
            printf("- %s\n", url);
            found = 1;
        }
    }

    if(found == 0)
    {
        printf("Tidak ditemukan\n");
    }

    fclose(file);
}
