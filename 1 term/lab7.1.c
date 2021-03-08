#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 7.1.
Дано целое число N (N>1). Составить алгоритм вывода
наименьшего целого K, при котором выполняется неравенство
3K> N и самого значения 3K.
*/

void sp() {
	printf("------------------------------------------------\n");
}

int main() {
	setlocale(LC_ALL, "Russian");
	int N, K = 0;
	sp();
	printf_s("Введите N: "); scanf_s("%d", &N);
	sp();

	while (3 * K < N)
	{
		K++;
	}

	printf_s("Наименьшее значение K, при котором 3K > N: %d\nПри этом 3K = %d\n", K, 3 * K);

	return 0;
}