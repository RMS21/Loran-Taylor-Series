#include <stdio.h>
#include <string.h>


#ifndef include_head
    #define include_head
    #include "head.h"

#endif // include_head



void convert_root_poly(Denominator_Root *dr, Poly *p){

    float *x_res;
    float *y_res;

    float *x1, *y1;
    float *x2, *y2;

    x_res = (float *)calloc(dr->nroot, sizeof(float));
    y_res = (float *)calloc(dr->nroot, sizeof(float));
    x1 = (float *)calloc(dr->nroot, sizeof(float));
    y1 = (float *)calloc(dr->nroot, sizeof(float));
    x2 = (float *)calloc(dr->nroot, sizeof(float));
    y2 = (float *)calloc(dr->nroot, sizeof(float));

    int temp = dr->nroot- 1;

    x_res[0] = -dr->x[0];
    y_res[0] = -dr->y[0];
    x_res[1] = 1;
    y_res[1] = 0;



    int i,j = 1;

    while(temp--){
                                            //Shifting to right : multipling by z

        for(i = 0; i <= (dr->nroot)-1 ; i++){
            x1[i+1] = x_res[i];
            y1[i+1] = y_res[i];
        }

        x1[0] = 0;
        y1[0] = 0;
                                                    //Multiping by root
        for(i = 0; i <= dr->nroot; i++)
            my_mull(x_res[i], -dr->x[j], y_res[i], -dr->y[j], &x2[i], &y2[i]);


        for(i = 0; i <= dr->nroot; i++)      //Adding each two term multipltion
            my_sum(x1[i], x2[i], y1[i], y2[i], &x_res[i], &y_res[i]);

        j++;
    }
    free(x1);
    free(x2);
    free(y1);
    free(y2);

    int count = 0;

   for(i = 0; i <= dr->nroot; i++)
        if((x_res[i] != 0) || (y_res[i] != 0) )
            count++;

    p->nterm = count;
    p->max_power = dr->nroot;
    p->terms = (Term *)malloc(sizeof(Term) * count);

    for(i = 0, j = 0; i <= dr->nroot; i++){
        if((x_res[i] != 0) || (y_res[i] != 0)){
            p->terms[j].power = i;
            p->terms[j].x = x_res[i];
            p->terms[j].y = y_res[i];
            j++;
        }
    }

    free(x_res);
    free(y_res);

    return &p;


}
