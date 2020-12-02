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

int part_division(int time, int part_count, int end_time, int logging) {
	if (logging == 1) {sp(); printf_s("[Log] Через %d часа(ов) амёба будет иметь %d клеток\n", time, part_count);}
	if (time == end_time) return part_count;
	return part_division(time + 3, part_count * 2, end_time, logging);
}

int main() {
	setlocale(LC_ALL, "Russian");
	int part_count = 1, logging = 1;
	//printf_s("Введите начальное количество клеток: "); scanf_s("%d", &part_count);
	part_count = part_division(0, part_count, 24, logging);

	sp();
	printf_s("Конечное количество клеток амёбы: %d\n", part_count);
	sp();
	return 0;
}
