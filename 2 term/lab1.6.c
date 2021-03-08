#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 1 (2 семестр)
13 % 10 + 1 = 4

4. Даны координаты трех вершин треугольника. Вычислить
длины всех его сторон и площадь, если треугольник существует.
*/

void sp() {
	printf("------------------------------------------------\n");
}

/* 
Принимает указатели на координаты вершин треугольника ABC (ax, ay, bx, by, cx, cy), выполняет вычисление площади и длин сторон 
и записывает в соответствующие указатели S, ab_length, bc_length, ac_length.
*/
void calculations(double* ax, double* ay, double* bx, double* by, double* cx, double* cy, double* S, double* ab_length, double* bc_length, double* ac_length);

int main(void) {
	setlocale(LC_ALL, "Russian");
	double ax, ay, bx, by, cx, cy;

	double* p_ax = &ax;
	double* p_ay = &ay;
	double* p_bx = &bx;
	double* p_by = &by;
	double* p_cx = &cx;
	double* p_cy = &cy;

	double S, ab_length, bc_length, ac_length;
	char* explanation[300];

	printf_s("Введите координату x вершины треугольника A: "); scanf_s("%lf", &ax);
	printf_s("Введите координату y вершины треугольника A: "); scanf_s("%lf", &ay);
	sp();
	printf_s("Введите координату x вершины треугольника B: "); scanf_s("%lf", &bx);
	printf_s("Введите координату y вершины треугольника B: "); scanf_s("%lf", &by);
	sp();
	printf_s("Введите координату x вершины треугольника C: "); scanf_s("%lf", &cx);
	printf_s("Введите координату y вершины треугольника C: "); scanf_s("%lf", &cy);
	sp();

	calculations(p_ax, p_ay, p_bx, p_by, p_cx, p_cy, &S, &ab_length, &bc_length, &ac_length);

	if (ab_length + bc_length > ac_length && ab_length + ac_length > bc_length && ac_length + bc_length > ab_length) 
	{
		printf_s(
			"Площадь треугольника: %lf\n"
			"Длина стороны AB: %lf\n"
			"Длина стороны BC: %lf\n"
			"Длина стороны AC: %lf\n", S, ab_length, bc_length, ac_length);
	}
	else
	{
		if (ab_length + bc_length < ac_length)
			*explanation = "Так как AB + BC < AC, треугольник не существует.";

		else if (ab_length + ac_length < bc_length)
			*explanation = "Так как AB + AC < BC, треугольник не существует.";

		else if (ac_length + bc_length < ab_length)
			*explanation = "Так как AC + BC < AB, треугольник не существует.";

		else
			*explanation = "Так как вершины совпадают, треугольник не существует.";

		printf_s(
			"Длина стороны AB: %lf\n"
			"Длина стороны BC: %lf\n"
			"Длина стороны AC: %lf\n"
			"%s\n", ab_length, bc_length, ac_length, *explanation);
	}
}	

void calculations(double* ax, double* ay, double* bx, double* by, double* cx, double* cy, double* S, double* ab_length, double* bc_length, double* ac_length) {

	*S =      fabs((*bx - *ax) * (*cy - *ay) - (*cx - *ax) * (*by - *ay))
		/ //--------------------------------------------------------------
		                                2.0;

	*ab_length = sqrt((*bx - *ax) * (*bx - *ax) + (*by - *ay) * (*by - *ay));
	*bc_length = sqrt((*cx - *bx) * (*cx - *bx) + (*cy - *by) * (*cy - *by));
	*ac_length = sqrt((*cx - *ax) * (*cx - *ax) + (*cy - *ay) * (*cy - *ay));
}

