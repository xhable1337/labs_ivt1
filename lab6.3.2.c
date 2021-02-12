#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 6. Дополнительное задание 2
Даны два целых числа: D (день) и М (месяц), определяющие правильную дату невисокосного года.
Вывести значения D и M для даты, следующей за указанной. 
*/

void sp() {
	printf("------------------------------------------------\n");
}

struct date {
	int day, month;
};

/* Принимает на вход день и месяц и проверяет ввод даты на правильность.
Если она верна, возвращает количество дней в месяце.
В обратном случае вывод будет равен нулю.
*/
int date_check(int day, int month) {
	int day_count = 0;

	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) day_count = 31;
	else if (month == 4 || month == 6 || month == 9 || month == 11) day_count = 30;
	else if (month == 2) day_count = 28;

	if (day <= day_count && day > 0) return day_count;
	else return 0;
}

// Принимает на входе массив структуры даты и выводит в следующий элемент этого массива день и месяц следующей даты.
void date_next(struct date* arr) {
	int day = arr[0].day; int month = arr[0].month;
	int day_count = date_check(day, month);

	if (day + 1 > day_count) {
		if (month + 1 > 12) {
			day = 1;
			month = 1;
		}
		else {
			day = 1;
			month++;
		}
	}
	else day++;

	arr[1].day = day; arr[1].month = month;
}

int main() {
	setlocale(LC_ALL, "Russian");
	int day = 0, month = 0;
	struct date arr[2];

	do {
		sp(); printf_s("Введите день: "); scanf_s("%d", &day);
		sp(); printf_s("Введите месяц: "); scanf_s("%d", &month); sp();

		if (date_check(day, month) == 0) {
			printf_s("[!] Введена неверная дата, повторите попытку.\n");
		}
	} while (date_check(day, month) == 0);

	arr[0].day = day; arr[0].month = month;
	date_next(arr);
	
	if (arr[0].month < 10 && arr[1].month > 10) printf_s("Дата, следующая после %d.0%d: %d.%d\n", arr[0].day, arr[0].month, arr[1].day, arr[1].month);
	if (arr[0].month > 10 && arr[1].month < 10) printf_s("Дата, следующая после %d.%d: %d.0%d\n", arr[0].day, arr[0].month, arr[1].day, arr[1].month);
	if (arr[0].month < 10 && arr[1].month < 10) printf_s("Дата, следующая после %d.0%d: %d.0%d\n", arr[0].day, arr[0].month, arr[1].day, arr[1].month);
	if (arr[0].month > 10 && arr[1].month > 10) printf_s("Дата, следующая после %d.%d: %d.%d\n", arr[0].day, arr[0].month, arr[1].day, arr[1].month); 

	sp();

	return 0;
}