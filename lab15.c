#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>

/* Лабораторная работа 15.
13. Имеется массив данных о К работающих в фирме: фамилия
и дата поступления на работу (день, месяц, год). Вывести на экран
фамилии тех, кто поступил на работу в определенную дату. Дата
(день, месяц и год) вводится с клавиатуры.
*/

// Синтаксис файла input.txt
/*
<размерность_массива = n>
<фамилия_1>
<день_1>
<месяц_1>
<год_1>
...
<фамилия_n>
<день_n>
<месяц_n>
<год_n>
*/

// Декоративная функция для вывода.
void sp() {
	printf("------------------------------------------------\n");
}

struct employees         // Инициализация структуры работников
{
	char last_name[30];
	int day, month, year;
};

//                                                   -=[ Функции ввода массива ]=-

/* Функция заполнения массива с клавиатуры.
На входе получает:
* arr - указатель на массив
* array_size - размерность массива
*/
void array_input(struct employees* arr, int array_size) {
	sp();
	int line = 1; int element;
	for (int i = 0; i < array_size; i++)
	{
		switch (line)
		{
		case 1: printf("Введите фамилию %d человека: ", i + 1); scanf_s("%s", &arr[i].last_name, 30);
		case 2: {
			do {
				printf("Введите день поступления %d человека на работу: ", i + 1); scanf_s("%d", &element);
				
				if (element < 1 || element > 31) { sp(); printf_s("[!] Введён некорректный день!\n"); sp(); }
				else arr[i].day = element;
			} while (element < 1 || element > 31);
		}
		case 3: {
			do {
				printf("Введите месяц поступления %d человека на работу: ", i + 1); scanf_s("%d", &element);

				if (element < 1 || element > 12) { sp(); printf_s("[!] Введён некорректный месяц!\n"); sp(); }
				else arr[i].month = element;
			} while (element < 1 || element > 12);
		}
		case 4: {
			printf("Введите год поступления %d человека на работу: ", i + 1); scanf_s("%d", &arr[i].year);
			sp();
			line = 0;
		}
		}

		line++;
	}
}

// Функция получения массива из текстового файла input.txt (должен быть в одном каталоге с исполняемым!)
int array_fromfile(struct employees* arr) {
	errno_t err;
	FILE* file;
	int element = 0;
	int array_size = 0;
	int line = 1;
	err = fopen_s(&file, "input.txt", "rt");
	do {
		if (err == 0)
		{
			fscanf_s(file, "%d", &array_size);
			for (int i = 0; i < array_size; i++) {
				fscanf_s(file, "%d", &element);
				switch (line)
				{
				case 1: {
					fscanf_s(file, "%s", &arr[i].last_name, 30);
					printf_s("Фамилия %d человека: %s\n", i + 1, arr[i].last_name);
				}
				case 2: {
					fscanf_s(file, "%d", &arr[i].day);
					printf_s("День поступления %d человека на работу: %d\n", i + 1, arr[i].day);
				}
				case 3: {
					fscanf_s(file, "%d", &arr[i].month);
					printf_s("Месяц поступления %d человека на работу: %d\n", i + 1, arr[i].month);
				}
				case 4: {
					fscanf_s(file, "%d", &arr[i].year);
					printf_s("Месяц поступления %d человека на работу: %d\n", i + 1, arr[i].year);
					line = 0;
					sp();
				}
				}

				line++;
			}
		}
		else { printf("Произошла ошибка при считывании файла."); exit(500); }
	} while (err != 0);
	fclose(file);
	printf_s("Массив успешно прочитан из файла!\n");
	sp();
	return array_size;
}

// ============================================================================ \\
\\ ============================================================================ //

/* Функция вывода массива на экран.
На входе получает:
* arr - указатель на массив
* array_size - размерность массива
*/
void array_print(struct employees* arr, int array_size) {
	int element;
	int count = 0;
	int day, month, year;

	do {
		printf_s("Введите день: "); scanf_s("%d", &day);
		printf_s("Введите месяц: "); scanf_s("%d", &month);
		printf_s("Введите год: "); scanf_s("%d", &year);

		if (day > 31 || day < 1 || month > 12 || month < 1)
		{
			sp();
			printf_s("[!] Введена некорректная дата. Повторите попытку.\n");
			sp();
		}
	} while (day > 31 || day < 1 || month > 12 || month < 1);

	sp();
	printf_s("Люди, поступившие на работу %d.%d.%d:\n", day, month, year);
	for (int i = 0; i < array_size; i++)
	{
		if (arr[i].day == day && arr[i].month == month && arr[i].year == year)
		{
			count++;
			printf_s("%d) %s\n", count, arr[i].last_name);
		}

	}

	if (count == 0)
	{
		printf_s("отсутствуют.\n");
	}
	sp();
}

// ============================================================================ \\
\\ ============================================================================ //

// Главная функция, запускаемая при инициализации.
int main() {
	setlocale(LC_ALL, "Russian"); // Установка русской локализации
	system("chcp 1251"); // Установка русской локализации для данных ввода/вывода
	system("cls");       // Очистка окна консоли от служебных сообщений
	struct employees arr[100]; // Инициализация структуры в виде массива
	int input_way, array_size, day, month, year; // Инициализация остальных переменных
	do
	{
		sp();
		printf_s("Способы заполнения массива:\n"
			"1) С клавиатуры\n"
			"2) Из файла 'input.txt'\n\n"
			"Каким способом вы хотите заполнить массив? "); scanf_s("%d", &input_way);
		sp();
		if (input_way > 2 || input_way < 1) {
			printf_s("Неверное значение способа заполнения массива!\n"
				"Значение должно быть от 1 до 2.\n");
		}
	} while (input_way > 2 || input_way < 1);

	switch (input_way) // Обработка введённого способа заполнения массива
	{
	case 1: { // Выбран ввод с клавиатуры
		printf_s("Введите размерность массива: "); scanf_s("%d", &array_size);
		array_input(arr, array_size);       // Функция ввода чисел с клавиатуры
		array_print(arr, array_size);       // Вывод массива на экран
	} break;

	case 2: { // Выбран ввод из файла
		array_size = array_fromfile(arr);   // Выбрано заполнение массива из файла
		array_print(arr, array_size);      // Вывод массива на экран
	}
	}
	return 0; // Завершение программы
}