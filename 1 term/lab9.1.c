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

// Возвращает результат расчёта формулы относительно натурального n.
double calc(int n) {
	double P = 1;
	for (int i = 1; i <= n; i++)
	{
		P *= (1.0 + (1.0 / ((double)i * (double)i)));
	}
	return P;
}

int main() {
	setlocale(LC_ALL, "Russian");
	int n; double P = 1;

	do {
		sp();
		printf_s("Введите натуральное число n: "); scanf_s("%d", &n);
		if (n <= 0) printf("[!] Введённое число не является натуральным. Повторите ввод.\n");
	} while (n <= 0);

	P = calc(n);

	sp();
	printf_s("Произведение P = %lf\n", P);
	sp();
	return 0;
}