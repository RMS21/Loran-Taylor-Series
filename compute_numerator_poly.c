#include <stdio.h>


#ifndef include_head
    #define include_head
    #include "head.h"

#endif // include_head


void compute_numerator_poly(Poly *pol, float x, float y, float *x_res, float *y_res){

    int temp = pol->nterm;
    int index = 0;

    *x_res = 0;
    *y_res = 0;

    while(temp--){
        float x1,y1;
        float x2,y2;
        float x3,y3;
        if(pol->terms[index].power != 0){
            my_power(x, y, pol->terms[index].power, &x1, &y1);
            my_mull(pol->terms[index].x, x1,pol->terms[index].y, y1, &x2, &y2);
            my_sum(*x_res, x2, *y_res, y2, &x3, &y3);
            *x_res = x3;
            *y_res = y3;
        }
        else{
            *x_res += pol->terms[index].x;
            *y_res += pol->terms[index].y;
        }


        index++;
    }
}

