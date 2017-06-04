#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef include_head
    #define include_head
    #include "head.h"

#endif // include_head

int max_power_diffrence(float *x1 ,float *y1, int size ,int *mpn){

    int i = 0;

    for(i = size; i >= 0; i--)
        if((x1[i] != 0) || (y1[i] != 0)){
            *mpn = i;
            break;
        }

    return *mpn;

}

void compute_fraction_realpart(Poly *n, Poly *d, Poly *r){

    int i;
    int shift = 0;
    float *x_n, *y_n;
    float *x_d, *y_d;
    float *x_r, *y_r;
    float *x_temp, *y_temp;
    float dx, dy;
    int mpn, mpd = d->max_power;
    float x, y;

    x_n = (float *)calloc(n->max_power, sizeof(float ));
    y_n = (float *)calloc(n->max_power, sizeof(float ));
    x_d = (float *)calloc(n->max_power, sizeof(float ));
    y_d = (float *)calloc(n->max_power, sizeof(float ));
    x_r = (float *)calloc(n->max_power, sizeof(float ));
    y_r = (float *)calloc(n->max_power, sizeof(float ));
    x_temp = (float *)calloc(n->max_power, sizeof(float ));
    y_temp = (float *)calloc(n->max_power, sizeof(float ));



    for(i = 0; i < d->nterm; i++){
        x_d[d->terms[i].power] = d->terms[i].x;
        y_d[d->terms[i].power] = d->terms[i].y;
    }

    for(i = 0; i < n->nterm; i++){
        x_n[n->terms[i].power] = n->terms[i].x;
        y_n[n->terms[i].power] = n->terms[i].y;
    }

    while((shift = (max_power_diffrence(x_n, y_n, n->max_power, &mpn) - mpd)) >= 0){

        my_divide(x_n[mpn], x_d[mpd], y_n[mpn], y_d[mpd], &dx, &dy);

        x_r[shift] = dx;         //Reminder
        y_r[shift] = dy;

        for(i = 0; i + shift <= n->max_power; i++)
            my_mull(x_d[i], dx, y_d[i], dy, &x_temp[i+shift], &y_temp[i+shift]);

        for(i = 0; i < shift; i++){
            x_temp[i] = 0;
            y_temp[i] = 0;
        }

        for(i = 0; i <= n->max_power; i++){
            my_minus(x_n[i], x_temp[i], y_n[i], y_temp[i], &x, &y);
            x_n[i] = x;
            y_n[i] = y;
        }

    }
    free(x_temp);
    free(y_temp);
    free(x_d);
    free(y_d);



//Updating num poly
    int nterms = 0;
    int flag = 0;

    for(i = n->max_power; i >= 0; i--)
        if((x_n[i] != 0) || (y_n[i] != 0)){
            if(!flag){
                mpn = i;
                flag = 1;
            }
            nterms++;
        }

    n->max_power = mpn;
    n->nterm = nterms;
    free(n->terms);
    n->terms = (Term *)malloc(sizeof(Term )* nterms);

    int j;

    for(i = 0, j = 0; i <= n->max_power; i++)
       if((x_n[i] != 0) || (y_n[i] != 0)){
        n->terms[j].power = i;
        n->terms[j].x = x_n[i];
        n->terms[j].y = y_n[i];
        j++;
    }


//End of Updating num poly

    free(x_n);
    free(y_n);

//Producing R poly

    nterms = 0;
    int mpr = 0;
    flag = 0;
    for(i = n->max_power; i  >= 0; i--)
        if((x_r[i] != 0) || (y_r[i] != 0)){
            if(!flag){
                mpr = i;
                flag = 1;
            }
            nterms++;
        }


    r->max_power = mpr;
    r->nterm = nterms;
    r->terms = (Term *)malloc(sizeof(Term )* nterms);

    for(i = 0, j = 0; i <= n->max_power; i++)
       if((x_r[i] != 0) || (y_r[i] != 0)){
            r->terms[j].power = i;
            r->terms[j].x = x_r[i];
            r->terms[j].y = y_r[i];
            j++;
        }

    free(x_r);
    free(y_r);

}

