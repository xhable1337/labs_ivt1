#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 7.3.1
Пусть задано число А в десятичной системе счисления и число В
– основание новой системы счисления, B < 9. Перевести А
из десятичной системы счисления в систему счисления
с основанием В.
*/

void sp() {
	printf("------------------------------------------------\n");
}

// Возвращает длину числа А в системе счисления B.
int len(int a, int b) {
	int count = 0;
	while (a) {
		a = floor(a / b);
		count++;
	}
	return count;
}

// Возвращает число A в системе счисления B.
long long int converter(int a, int b) {
	int zero_count = 0;
	long long int c = 0;
	int temp;
	long long int result = 0;
	int count = len(a, b);

	while (count > 0) {
		printf("[!] %d / %d = %d, остаток %d\n", a, b, (int)floor(a / b), a % b);
		if (a % b == 0 && c == 0) zero_count++;
		else c += ((a % b) * pow(10, count));
		a = floor(a / b);
		count--;
	}

	while (c != 0)
	{
		temp = c % 10;
		result = result * 10 + temp;
		c = c / 10;
	}

	result *= (long long int)pow(10, zero_count);

	return result;
}

long long int main() {
	setlocale(LC_ALL, "Russian");
	int a, b, c;
	sp();
	printf_s("Введите A: "); scanf_s("%d", &a);
	sp();
	do
	{
		printf_s("Введите B (1 < B < 9): "); scanf_s("%d", &b);
		if (b < 2 || b > 9) printf_s("[!] Введено неправильное основание системы счисления. Повторите ввод.\n");
	} while (b < 2 || b > 9);
	
	sp();
	long long int result = converter(a, b);
	sp();
	printf("%d_10 = %lli_%d\n", a, result, b);
	sp();

	return 0;
}