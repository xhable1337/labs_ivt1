#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 10.
Найти все целочисленные решения уравнения 3𝑥 − 4𝑧 = 2𝑦
на интервале от А до В.
*/

void sp() {
	printf("------------------------------------------------\n");
}

int main() {
	setlocale(LC_ALL, "Russian");
	int A = 0, B = 0, x, y, z, count = 0;
	
	sp();
	printf_s("Введите левую границу интервала: "); scanf_s("%d", &A);
	sp();
	printf_s("Введите правую границу интервала: "); scanf_s("%d", &B);
	sp();

	
	for (x = A; x <= B; x++)
	{
		for (y = A; y <= B; y++)
		{
			for (z = A; z <= B; z++)
			{
				if (3 * x - 4 * z == 2 * y)
				{
					count++;
					printf_s("Решение №%d:\n\n[x = %d | y = %d | z = %d]\n3 * (%d) - 4 * (%d) = 2 * (%d)\n", count, x, y, z, x, z, y);
					sp();
				}
			}
		}
	}

	if (count == 0)
	{
		printf_s("Решений уравнения на заданном диапазоне не существует.\n");
		sp();
	}
	else
	{
		printf_s("Всего решений уравнения на заданном диапазоне: %d\n", count);
		sp();
	}

	return 0;
}