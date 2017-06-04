#include <stdio.h>


void my_sum(float x1, float x2, float y1, float y2, float*x_res, float*y_res) {
	*x_res = x1 + x2;
	*y_res = y1 + y2;
}

void my_minus(float x1, float x2, float y1, float y2, float*x_res, float*y_res) {
	*x_res = x1 - x2;
	*y_res = y1 - y2;
}


void my_mull (float x1, float x2, float y1, float y2, float*x_res, float*y_res) {
	*x_res = x1 * x2 - y1 * y2;
	*y_res = x1 * y2 + x2 * y1;
}

void my_divide(float x1, float x2, float y1, float y2, float*x_res, float*y_res) {
	if (x2 == 0 && y2 == 0) {
		printf("Erorr Division by Zero");
	}
	else {
		*x_res = (x1 * x2 + y1 * y2) / (x2 * x2 + y2 * y2);
		*y_res = (x2 * y1 - x1 * y2) / (x2 * x2 + y2 * y2);
	}
}

void my_power(float x1, float y1, int power, float*x_res, float*y_res){

	if (power == 0) {
		*x_res = 1;
		*y_res = 1;
	}
	else if (power == 1) {
		*x_res = x1;
		*y_res = y1;
	}
	else {
		my_mull(x1, x1, y1, y1, x_res, y_res);
		power -= 2;
		while (power--)
			my_mull(x1, *x_res, y1, *y_res, x_res, y_res);
	}
}
