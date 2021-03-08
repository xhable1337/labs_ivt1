#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 4.1.
13. Дан размер файла в байтах.
Выразить размер этого файла в формате X мегабайтов Y килобайтов Z байтов.
*/

void sp() {
	printf("------------------------------------------------\n");
}

int main() {
	setlocale(LC_ALL, "Russian");
	int b, Kb, Mb;

	sp();
	printf_s("Введите количество байтов: "); scanf_s("%d", &b);

	Mb = b / (1024 * 1024);
	b -= Mb * (1024 * 1024);
	Kb = b / 1024;
	b -= Kb * 1024;

	sp();
	printf_s("%d Мб, %d Кб, %d б\n", Mb, Kb, b);
	sp();
	return 0;
}

