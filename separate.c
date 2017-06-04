#include <stdio.h>
#include <stdlib.h>

#ifndef include_head
    #define include_head
    #include "head.h"

#endif // include_head




Part *separate_poly(Poly *pol, Denominator_Root *dr){

    Part *par;
    par = (Part *)malloc(sizeof(Part) * dr->nroot);

    int temp = dr->nroot;
    int index = 0;
    while(temp--){


        (par+index)->root_x = dr->x[index];
        (par+index)->root_y = dr->y[index];

        float x1,y1;
        float x2,y2;
        float x3,y3;

        compute_numerator_poly(pol, dr->x[index], dr->y[index], &x1, &y1);
        compute_denominator_poly(dr, dr->x[index], dr->y[index], &x2, &y2);

        my_divide(x1, x2, y1, y2, &x3, &y3);

        (par+index)->num_x = x3;
        (par+index)->num_y = y3;

        index++;

    }
    return par;
}
