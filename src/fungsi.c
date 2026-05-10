#include <stdio.h>
#include <math.h>
#include "website.h"

void buattitik(koordinat *a, int x, int y)
{
    a->x = x;
    a->y = y;
}

float hitungjarak(koordinat a)
{
    float jarak;

    jarak = sqrt(pow(a.x,2)+pow(a.y,2));

    return jarak;

}
