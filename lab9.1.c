#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 9.
Дано натуральное число n. Вычислить произведение
P = (1 + 1/(1^2)) * (1 + 1/(2^2)) * ... * (1 + 1/(n^2))
*/

void sp() {
	printf("------------------------------------------------\n");
}

int main() {
	setlocale(LC_ALL, "Russian");
	int n; double P = 1;

	sp();
	printf_s("Введите натуральное число n: "); scanf_s("%d", &n);

	for (int i = 1; i < n + 1; i++)
	{
		P *= (1 + (1 / pow(i, 2)));
	}

	sp();
	printf_s("Произведение P = %lf\n", P);
	sp();
	return 0;
}