#include <stdio.h>

#ifndef include_head
    #define include_head
    #include "head.h"

#endif // include_head




Poly *produce_loran_series(Part *p, int n, int K){

    Poly *L;
    L = (Poly *)malloc(sizeof(Poly )* n);

    int i;
    int j;
    float x, y;


    for(i = 0; i < n; i++){

        if((p[i].root_x == 0) && (p[i].root_y == 0)){
            L[i].terms = malloc(sizeof(Term ));
            L[i].max_power = 1;
            L[i].nterm = 1;
            L[i].terms[0].power = -1;
            L[i].terms[0].x = p[i].num_x;
            L[i].terms[0].y = p[i].num_y;
        }
        else{
            L[i].terms = (Term *)malloc(sizeof(Term ) * K);
            L[i].nterm = K;
            L[i].max_power = -1;
            for(j = 0; j < K; j++){
                L[i].terms[j].power = -(j+1);
                if(j == 0){
                    L[i].terms[j].x = p[i].num_x;
                    L[i].terms[j].y = p[i].num_y;
                }
                else{
                    my_power(p[i].root_x, p[i].root_y, j,&x, &y);
                    my_mull(p[i].num_x, x, p[i].num_y, y, &L[i].terms[j].x, &L[i].terms[j].y);
                }
            }
        }
    }
    return L;
}
