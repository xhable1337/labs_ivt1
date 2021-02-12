#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 12.1 (использование рекурсии)
Одноклеточная амеба каждые три часа делится на две клетки.
Определить, сколько клеток будет через 3, 6, 9, … 24 часа.
*/

void sp() {
	printf("------------------------------------------------\n");
}

int part_division(int time, int part_count, int end_time, int logging, int recursion_depth) {
	if (logging == 1) { 
		sp(); 
		printf_s("[Глубина рекурсии: %d] Через %d часа (ов) количество клеток амёбы будет: %d \n", 
			recursion_depth, time, part_count); 
	}
	if (time >= end_time || time + 3 > end_time) return part_count;
	return part_division(time + 3, part_count * 2, end_time, logging, recursion_depth + 1);
}

int main() {
	setlocale(LC_ALL, "Russian");
	int part_count = 1, hour_count = 24, recursion_depth = 0;
	int logging = 1; // Вывод глубины рекурсивной функции и её результатов на текущий момент (0/1 - выкл/вкл)

	printf_s("Введите количество часов: "); scanf_s("%d", &hour_count);

	part_count = part_division(0, part_count, hour_count, logging, recursion_depth);

	sp();
	printf_s("Конечное количество клеток амёбы: %d\n", part_count);
	sp();
	return 0;
}