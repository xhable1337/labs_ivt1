#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

/* Лабораторная работа 3.3.
13.
1 / sqrt(ax^2 + bx + c)
*/

void sp() {
	printf("------------------------------------------------\n");
}

int main() {
	setlocale(LC_ALL, "Russian");
	double a = 0, b = 0, c = 0, x = 0, result = 0;

	sp();
	printf("Введите a: "); scanf_s("%lf", &a);
	sp();
	printf("Введите b: "); scanf_s("%lf", &b);
	sp();
	printf("Введите c: "); scanf_s("%lf", &c);
	sp();
	printf("Введите x: "); scanf_s("%lf", &x);
	sp();

	while ((sqrt(a * pow(x, 2) + b * x + c)) == 0) {
		printf("Введены некорректные данные, повторите попытку!");
		sp();
	}

	result = 1 / (sqrt(a * pow(x, 2) + b * x + c));
	printf("Ответ: %lf\n", result);
	sp();

	system("pause");
	return 0;
}