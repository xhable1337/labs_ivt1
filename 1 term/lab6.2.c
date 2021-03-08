#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 6.2.
Подарочные комплекты формируются из трех предметов
различной стоимости. Имеется четыре таких комплекта.
Определить стоимость самого дорогого из них.
*/

void sp() {
	printf("------------------------------------------------\n");
}

struct set_summary {
	int max, price;
};

void set_count(struct set_summary* sets) {
	int price, max_sum = 0, sum = 0, max = 0;

	for (int set = 1; set < 5; set++)
	{
		for (int item = 1; item < 4; item++)
		{
			price = 0;
			sp();
			printf_s("Введите стоимость %d предмета %d комплекта: ", item, set); scanf_s("%d", &price);
			sum += price;
		}

		if (sum > max_sum)
		{
			max_sum = sum;
			max = set;
		}
		sum = 0;
	}

	sets[0].max = max; sets[0].price = max_sum;
}

int main() {
	setlocale(LC_ALL, "Russian");
	struct set_summary sets[1];
	set_count(sets);

	sp();
	printf_s("Самый дорогой комплект: %d\nЕго стоимость: %d\n", sets[0].max, sets[0].price);
	sp();
	return 0;
}