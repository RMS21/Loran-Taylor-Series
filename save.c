#include <stdio.h>

#ifndef include_head
    #define include_head
    #include "head.h"

#endif // include_head


void save(Poly R, Poly *Taylor_Polys, Poly *Loran_Polys, Part *parts, int nparts, int K,float *area, int flagR){


    FILE *fp;

    fp = fopen("/home/rasoul/Desktop/o.txt", "w");

    float *x_pos;
    float *y_pos;



    float *x_neg;
    float *y_neg;



    float x,y;

    int narea = 0;

    int i,j;

    if(area[0] != 0){
        nparts++;
        area = (float *)realloc(area, sizeof(float)*nparts);
        area[nparts-1] = 0;
        qsort(area, nparts, sizeof(float), cmp);

    }


    while(narea != nparts){



        if(narea+1 != nparts)
            fprintf(fp, "%.2f %.2f\n\n", area[narea], area[narea+1]);
        else
            fprintf(fp, "%.2f -\n\n", area[narea]);

        int csize = (nparts*K+R.nterm);

        x_pos = (float *)calloc((nparts*K+R.nterm), sizeof(float));
        y_pos = (float *)calloc((nparts*K+R.nterm), sizeof(float));
        x_neg = (float *)calloc((nparts*K+R.nterm), sizeof(float));
        y_neg = (float *)calloc((nparts*K+R.nterm), sizeof(float));


        if(flagR){
            for(i = 0; i != R.nterm; i++){
                if(R.terms[i].power >= 0){
                    x_pos[R.terms[i].power] = R.terms[i].x;
                    y_pos[R.terms[i].power] = R.terms[i].y;
                }
                else if(R.terms[i].power < 0){
                    x_neg[abs(R.terms[i].power+1)] = R.terms[i].x;
                    y_neg[abs(R.terms[i].power+1)] = R.terms[i].y;
                }
            }
        }


        for(i = 0; i != nparts; i++){

            float dif = my_abs(parts[i].root_x, parts[i].root_y);

            char c = 'f';

            if(dif == 0)
                c = 'L';
            else if(narea+1 == nparts)
                c = 'L';
            else if ( (dif >= area[narea]) && (dif >= area[narea+1]))
                c = 'T';
            else
                c = 'L';

            if(c == 'T'){

                for(j = 0; j != Taylor_Polys[i].nterm; j++){
                    my_sum(x_pos[Taylor_Polys[i].terms[j].power], Taylor_Polys[i].terms[j].x, y_pos[Taylor_Polys[i].terms[j].power], Taylor_Polys[i].terms[j].y, &x, &y);
                    x_pos[Taylor_Polys[i].terms[j].power] = x;
                    y_pos[Taylor_Polys[i].terms[j].power] = y;
                }
            }
            else{
                for(j = 0; j != Loran_Polys[i].nterm; j++){
                    my_sum(x_neg[abs(Loran_Polys[i].terms[j].power+1)] , Loran_Polys[i].terms[j].x, y_neg[abs(Loran_Polys[i].terms[j].power+1)], Loran_Polys[i].terms[j].y, &x, &y);
                    x_neg[abs(Loran_Polys[i].terms[j].power+1)] = x;
                    y_neg[abs(Loran_Polys[i].terms[j].power+1)] = y;

                    }
                }
            }




        int pcount=0;
        int ncount=0;

        for(i = 0; i != csize; i++){
            if((x_pos[i] != 0) || (y_pos[i] != 0))
                pcount++;
            if((x_neg[i] != 0) || (y_neg[i] != 0))
                ncount++;

        }


        fprintf(fp, "%d ", pcount+ncount);


        float xtemp = 0.0f;
        float ytemp = 0.0f;

        for(i = csize-1; i != -1; i--){
            if((x_neg[i] != 0) || (y_neg[i] != 0)){
                if(x_neg[i] == 0)
                    x_neg[i] = 0;
                if(y_neg[i] == 0)
                    y_neg[i] = 0;
                fprintf(fp, "%.2f %.2f %d  ", x_neg[i], y_neg[i], -(i+1));
            }
        }

        for(i = 0; i != csize; i++){
            if((x_pos[i] != 0) || (y_pos[i] != 0)){
                if(x_pos[i] == 0)
                    x_pos[i] = 0;
                if(y_pos[i] == 0)
                    y_pos[i] = 0;
                fprintf(fp, "%.2f %.2f %d  ", x_pos[i], y_pos[i], i);
            }
        }

        fprintf(fp, "\n\n");




        free(x_pos);
        free(y_pos);
        free(x_neg);
        free(y_neg);
        narea++;
    }
    fclose(fp);

}

