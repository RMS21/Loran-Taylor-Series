#include <stdio.h>
#include <stdlib.h>

#ifndef include_head
    #define include_head
    #include "head.h"

#else

#endif // include_head





void get_numerator_poly(Poly *p, FILE *fp){

    fscanf(fp ,"%d", &(p->nterm));
    int temp = p->nterm;

    p->terms = (Term *)malloc(sizeof(Term)*temp);

    int index = 0;
    int maxpower = 0;

    while(temp--){
        fscanf(fp, "%f %f %d", &(p->terms[index].x), &(p->terms[index].y), &(p->terms[index].power));
        if(p->terms[index].power > maxpower)
            maxpower = p->terms[index].power;
        index++;
    }
    p->max_power = maxpower;
}
