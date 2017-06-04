#include <stdio.h>

#ifndef include_head
    #define include_head
    #include "head.h"

#endif // include_head


void compute_denominator_poly(Denominator_Root *dr, float x, float y, float *x_res, float *y_res){


    int temp = dr->nroot;
    int index = 0;

    *x_res = 0;
    *y_res = 0;
    int flag = 0;

    while(temp--){

        float x1,y1;
        float x2,y2;
        if(x != dr->x[index] || y != dr->y[index]){
            my_minus(x, dr->x[index], y, dr->y[index], &x1, &y1);
            if(flag != 0){
                my_mull(*x_res, x1, *y_res, y1, &x2, &y2);
                *x_res = x2;
                *y_res = y2;
            }else{
                *x_res += x1;
                *y_res += y1;
                flag = 1;
            }
        }


    index++;
    }

}
