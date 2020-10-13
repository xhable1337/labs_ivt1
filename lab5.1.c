#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 5.1
13. Дано целое число. Если оно отрицательно, возвести его в квадрат, в противном случае извлечь из него корень.
*/


void sp() {
	printf("------------------------------------------------\n");
}

int main() {
	setlocale(LC_ALL, "Russian");
	int src;
	double dest;

	sp();
	printf_s("Введите целое число: "); scanf_s("%d", &src);

	if (src > 0) {
		dest = sqrt(src);
		
	}
	else {
		dest = pow(src, 2);
	}

	sp();
	printf_s("Полученное число: %.3lf\n", dest);
	sp();

	return 0;
}