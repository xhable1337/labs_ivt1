#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 5.2.
13.
𝑓(𝑥) = {1, 𝑥 < 0
	   {2/(𝑥+2), 0 <= 𝑥 < 1
	   {2𝑒𝑥𝑝(𝑥), 𝑥 >= 1
*/

void sp() {
	printf("------------------------------------------------\n");
}

int main() {
	setlocale(LC_ALL, "Russian");
	double x, result = 1;

	sp();
	printf_s("Введите переменную x: "); scanf_s("%lf", &x);
	sp();

	if (x < 0)
	{
		result = 1.0;
	}

	if (0 <= x && x < 1)
	{
		result = 2 / (x + 2);
	}

	if (x >= 1)
	{
		result = 2 * exp(x);
	}



	printf_s("Результат вычислений: %lf\n", result);
	sp();

	return 0;
}

