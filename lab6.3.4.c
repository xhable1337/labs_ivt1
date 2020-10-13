#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 6. Дополнительное задание 4
Мастям игральных карт присвоены порядковые номера: 1 – пики, 2 – трефы, 3 – бубны, 4 – червы. 
Достоинству карт, старших десятки, присвоены номера: 11 – валет, 12 - дама, 13 – король, 14 – туз. 
Даны два целых числа: N – достоинство (6 <= N <= 14) и М – масть карты (1 <= M <= 4). 
Вывести название соответствующей карты вида «шестерка бубен», «дама червей», «туз треф» и т.п. 
*/

void sp() {
	printf("------------------------------------------------\n");
}

void card_to_text(int value, int suit) {
	printf_s("Введённая карта: ");
	switch (value)	{
		case 6: printf_s("шестёрка "); break;
		case 7: printf_s("семёрка "); break;
		case 8: printf_s("восьмёрка "); break;
		case 9: printf_s("девятка "); break;
		case 10: printf_s("десятка "); break;
		case 11: printf_s("валет "); break;
		case 12: printf_s("дама "); break;
		case 13: printf_s("король "); break;
		case 14: printf_s("туз "); break;
	}

	switch (suit) {
		case 1: printf_s("пик.\n"); break;
		case 2: printf_s("треф.\n"); break;
		case 3: printf_s("бубен.\n"); break;
		case 4: printf_s("червей.\n"); break;
	}

	sp();
}

int main() {
	setlocale(LC_ALL, "Russian");
	int value, suit;

	do {
		sp(); printf_s("Введите достоинство карты (6-14): "); scanf_s("%d", &value);
		sp(); printf_s("Введите масть карты (1-4): "); scanf_s("%d", &suit); sp();
		if (value < 6 || value > 14 || suit < 1 || suit > 4) printf_s("[!] Введены неправильные данные. Повторите попытку.\n");
	} while (value < 6 || value > 14 || suit < 1 || suit > 4);

	card_to_text(value, suit);

	return 0;
}
