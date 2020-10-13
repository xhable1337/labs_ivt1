#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 12.2 (без использования рекурсии)
Одноклеточная амеба каждые три часа делится на две клетки.
Определить, сколько клеток будет через 3, 6, 9, … 24 часа.
*/

void sp() {
	printf("------------------------------------------------\n");
}


int main() {
	setlocale(LC_ALL, "Russian");
	int part_count = 1, logging = 1;
	//printf_s("Введите начальное количество клеток: "); scanf_s("%d", &part_count);

	for (int i = 3; i <= 24; i += 3) {part_count *= 2;}

	sp();
	printf_s("Конечное количество клеток амёбы: %d\n", part_count);
	sp();
	return 0;
}