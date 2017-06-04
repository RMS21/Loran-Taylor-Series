
typedef struct{
    int power;
    float x;
    float y;
}Term;

typedef struct{
    int max_power;
    int nterm;
    Term *terms;
}Poly;

typedef struct{
    int nroot;
    float *x;
    float *y;
}Denominator_Root;


typedef struct{

    float num_x;
    float num_y;
    float root_x;
    float root_y;

}Part;



float cmp(const float* pa,const float* pb);


void get_numerator_poly(Poly *p, FILE *fp);
void get_denominator_poly(Denominator_Root *dr, FILE *fp);
void convert_root_poly(Denominator_Root *dr, Poly *p);
Part *separate_poly(Poly *pol, Denominator_Root *dr);
void compute_numerator_poly(Poly *pol, float x, float y, float *x_res, float *y_res);
void compute_denominator_poly(Denominator_Root *dr, float x, float y, float *x_res, float *y_res);
void compute_fraction_realpart(Poly *numerator_poly, Poly *denominator_poly, Poly *R);

float my_abs(float x, float y);
float *produce_area(Part *p, int size);


Poly *produce_taylor_series(Part *parts, int nparts, int K);
Poly *produce_loran_series(Part *parts, int nparts, int K);

void save(Poly R, Poly *Taylor_Polys, Poly *Loran_Polys, Part *parts, int nparts, int K, float *area, int flagR);


// Operation Functions Prototype

void my_sum(float x1, float x2, float y1, float y2, float*x_res, float*y_res);
void my_minus(float x1, float x2, float y1, float y2, float*x_res, float*y_res);
void my_mull (float x1, float x2, float y1, float y2, float*x_res, float*y_res);
void my_divide(float x1, float x2, float y1, float y2, float*x_res, float*y_res);
void my_power(float x1, float y1, int power, float*x_res, float*y_res);



