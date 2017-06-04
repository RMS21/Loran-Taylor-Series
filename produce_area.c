#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef include_head
    #define include_head
    #include "head.h"

#endif // include_head



float my_abs(float x, float y){

    return (float)sqrt((x * x) + (y * y));

}

float cmp(const float* pa,const float* pb){
	float a=*pa;
	float b=*pb;
	return a-b;
}


float *produce_area(Part *p, int size){

    float *a;

    a = (float *)malloc(sizeof(float) * size);

    int i;
    for(i = 0;i < size; i++)
        a[i] = my_abs(p[i].root_x, p[i].root_y);

    qsort(a, size, sizeof(float), cmp);

    return a;
}
