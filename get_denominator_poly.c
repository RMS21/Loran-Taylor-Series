#include <stdio.h>
#include <stdlib.h>



#ifndef include_head
    #define include_head
    #include "head.h"

#else

#endif // include_head



void get_denominator_poly(Denominator_Root *dr, FILE *fp){

    int p;
    fscanf(fp, "%d", &p);

    dr->nroot = p;

    dr->x = (float *)malloc(sizeof(float) * p);
    dr->y = (float *)malloc(sizeof(float) * p);

    int index = 0;

    while(p--){
        fscanf(fp, "%f %f", &(dr->x[index]), &(dr->y[index]));
        index++;
    }
}


