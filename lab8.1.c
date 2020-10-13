#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 8.
Написать программу определения максимального четного
числа из последовательности положительных чисел, вводимых
с клавиатуры. Ввод данных завершить после того, как пользователь
введет 0 или любое отрицательное число.
*/

void sp() {
	printf("------------------------------------------------\n");
}

int main() {
	setlocale(LC_ALL, "Russian");
	int input, count = 1, max = 0, max_count = 0;
	do
	{
		sp();
		printf_s("Введите число №%d: ", count); scanf_s("%d", &input);
		if (input > max && input % 2 == 0)
		{
			max = input;
			max_count = count;
		}
		count++;
		
	} while (input > 0);

	sp();
	if (max == 0)
	{
		printf_s("В данной последовательности нет чётных чисел.\n");
	}
	else
	{
		printf_s("Максимальное чётное число из последовательности: %d\nЕго номер в последовательности: %d\n", max, max_count);
	}
	sp();
	return 0;
}