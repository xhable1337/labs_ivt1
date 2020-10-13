#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 6.1.
13. Определить арккосинус, арккотангенс, десятичный логарифм
или квадратный корень введённого числа (на выбор пользователя).
*/

void sp() {
	printf("------------------------------------------------\n");
}

int main() {
	setlocale(LC_ALL, "Russian");
	int x, operation;
	double result = 0;
	double pi = 3.14159265;
	sp();
	printf_s("Введите число: "); scanf_s("%d", &x);
	sp();
	printf_s("Список операций:"
		"\n1 - арккосинус"
		"\n2 - арккотангенс"
		"\n3 - десятичный логарифм"
		"\n4 - извлечение квадратного корня"
		"\n\nВведите номер операции, которую хотите выполнить с данным числом: "); scanf_s("%d", &operation);
	sp();

	switch (operation)
	{
	case 1: result = acos(x); break;
	case 2: result = pi / 2 - atan(x); break;
	case 3: result = log10(x); break;
	case 4: result = sqrt(x); break;
	default:
		printf("Введён неверный номер операции!"); break;
	}

	if isnan(result) { printf_s("Результат вычислений не определен. Повторите попытку, введя другое число.\n"); }
	else { printf_s("Результат вычислений: %lf\n", result); }

	sp();
	return 0;
}