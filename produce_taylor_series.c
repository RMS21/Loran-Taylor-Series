#include <stdio.h>

#ifndef include_head
    #define include_head
    #include "head.h"

#endif // include_head






Poly *produce_taylor_series(Part *p, int n, int K){

    Poly *T;
    T = (Poly *)malloc(sizeof(Poly )* n);

    int i;
    int j;
    float x,y;



    for(i = 0; i < n; i++){

        if((p[i].root_x == 0) && (p[i].root_y == 0)){
            T[i].terms = malloc(sizeof(Term ));
            T[i].max_power = -1;
            T[i].nterm = 1;
            T[i].terms[0].power = -1;
            T[i].terms[0].x = -p[i].num_x;
            T[i].terms[0].y = -p[i].num_y;
        }
        else{
            T[i].terms = (Term *)malloc(sizeof(Term ) * K);
            T[i].nterm = K;
            T[i].max_power = K-1;
            for(j = 0; j < K; j++){
                T[i].terms[j].power = j;
                my_power(p[i].root_x, p[i].root_y, j+1,&x, &y);
                my_divide(p[i].num_x, x, p[i].num_y, y, &T[i].terms[j].x, &T[i].terms[j].y);
                T[i].terms[j].x = -T[i].terms[j].x;
                T[i].terms[j].y = -T[i].terms[j].y;
            }
        }
    }
    return T;

}

