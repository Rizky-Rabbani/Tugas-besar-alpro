#include "website.h"
#include <stdio.h>

int app(void)
{
    koordinat rumah;
    float distance;
    int posisiX, posisiY;

    printf("Masukkan koordinat x rumah kalian : ");
    scanf("%d", &posisiX);
    printf("Masukkan koordinat y rumah kalian : ");
    scanf("%d", &posisiY);

    buattitik(&rumah, posisiX, posisiY);

    distance = hitungjarak(rumah);
    
    printf("jarak dari (0,0) = %.2f", distance);

    return 0;

}