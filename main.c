#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#ifndef include_head
    #define include_head
    #include "head.h"

#endif // include_head




int main(int argc, char *argv[]){

    FILE *fp;
    fp = fopen("t.txt", "r");

	int N;
	fscanf(fp,"%d", &N);

while(N--){


    int flagR = 0;
    Poly R;
    Poly denum_poly;
    float *area;

    Poly num_poly;
    get_numerator_poly(&num_poly, fp);

    Denominator_Root denum_root;
    get_denominator_poly(&denum_root, fp);


    int K;
    fscanf(fp, "%d", &K);


    if(num_poly.max_power > denum_root.nroot){
        convert_root_poly(&denum_root, &denum_poly);
        compute_fraction_realpart(&num_poly, &denum_poly, &R);
        flagR = 1;
        free(denum_poly.terms);
    }


    Part *parts;
    parts = separate_poly(&num_poly, &denum_root);


    free(num_poly.terms);

    Poly *Taylor_Polys;
    Poly *Loran_Polys;

    Taylor_Polys = produce_taylor_series(parts,denum_root.nroot, K);
    Loran_Polys = produce_loran_series(parts, denum_root.nroot, K);


    area = produce_area(parts, denum_root.nroot);

    save(R, Taylor_Polys, Loran_Polys, parts,denum_root.nroot, K,area, flagR);


    free(denum_root.x);
    free(denum_root.y);
    free(R.terms);
    free(parts);
    free(Taylor_Polys);
    free(Loran_Polys);

    }
 	return 0;
}
