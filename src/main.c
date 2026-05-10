#include <stdio.h>
#include "website.h"

int main(){

    koordinat rumah;
    float distance;

    buattitik(&rumah, 3, 4);

    distance = hitungjarak(rumah);
    
    printf("jarak dari (0,0) = %.2f", distance);

    return 0;
}