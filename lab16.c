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
<фамилия_2>
<день_2>
<месяц_2>
<год_2>
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

struct employees                      // Инициализация структуры работников
{
	char last_name[30];
	int day, month, year;
};

// Конфигурация программы

int employees_max = 30;               // Максимальное количество элементов в массиве структуры employees
const char txt_filename_in[30] = "input.txt";      // Путь к файлу .txt, из которого нужно считать массив
const char bin_filename_in[30] = "input.bin";      // Путь к файлу .bin, из которого нужно считать массив
const char bin_filename_out[30] = "output.bin";    // Путь к файлу .bin, в который нужно записать массив

//===========================================================================================//
//                                                   -=[ Функции ввода массива ]=-

/* Функция заполнения массива с клавиатуры.
На входе получает:
* arr - указатель на массив
* array_size - размерность массива
*/
int array_input(struct employees* arr) {
	int element, array_size;
	printf_s("Введите размерность массива: "); scanf_s("%d", &array_size);
	sp();
	for (int i = 0; i < array_size; i++)
	{

		printf("Введите фамилию %d человека: ", i + 1); scanf_s("%s", &arr[i].last_name, 30);

		do {
			printf("Введите день поступления %d человека на работу: ", i + 1); scanf_s("%d", &element);

			if (element < 1 || element > 31) { sp(); printf_s("[!] Введён некорректный день!\n"); sp(); }
			else arr[i].day = element;
		} while (element < 1 || element > 31);

		do {
			printf("Введите месяц поступления %d человека на работу: ", i + 1); scanf_s("%d", &element);

			if (element < 1 || element > 12) { sp(); printf_s("[!] Введён некорректный месяц!\n"); sp(); }
			else arr[i].month = element;
		} while (element < 1 || element > 12);

		printf("Введите год поступления %d человека на работу: ", i + 1); scanf_s("%d", &arr[i].year);
		sp();

	}

	return array_size;
}

// Функция получения массива из текстового файла input.txt (должен быть в одном каталоге с исполняемым!)
int array_fromfile(struct employees* arr, const char filename[]) {
	errno_t err;
	FILE* file;
	int array_size = 0;
	int line = 1;
	err = fopen_s(&file, filename, "rt");
	do {
		if (err == 0)
		{
			fscanf_s(file, "%d", &array_size);
			for (int i = 0; i < array_size; i++) {

				fscanf_s(file, "%s", &arr[i].last_name, 30);
				printf_s("Фамилия %d человека: %s\n", i + 1, arr[i].last_name);

				fscanf_s(file, "%d", &arr[i].day);
				printf_s("День поступления %d человека на работу: %d\n", i + 1, arr[i].day);

				fscanf_s(file, "%d", &arr[i].month);
				printf_s("Месяц поступления %d человека на работу: %d\n", i + 1, arr[i].month);

				fscanf_s(file, "%d", &arr[i].year);
				printf_s("Месяц поступления %d человека на работу: %d\n", i + 1, arr[i].year);

				sp();
			}
		}
		else { printf("Произошла ошибка при считывании файла."); exit(500); }
	} while (err != 0);
	fclose(file);
	printf_s("Массив успешно прочитан из файла!\n");
	sp();
	return array_size;
}

// Функция получения массива из бинарного файла input.bin (должен быть в одном каталоге с исполняемым!)
int array_frombinary(struct employees* arr, const char filename[]) {
	FILE* binary;
	errno_t err;
	err = fopen_s(&binary, filename, "rb");
	int array_size;

	fread(&array_size, 1, sizeof(array_size), binary);
	fread(arr, sizeof(arr[array_size]), array_size, binary);

	printf_s("Массив прочитан из бинарного файла!\n");
	sp();
	return array_size;
}

// Функция получения способа заполнения массива.
int get_input_way() {
	int input_way;
	do
	{
		sp();
		printf_s("Способы заполнения массива:\n"
			"1) С клавиатуры\n"
			"2) Из файла '%s'\n"
			"3) Из бинарного файла '%s'\n\n"
			"Каким способом вы хотите заполнить массив? ", txt_filename_in, bin_filename_in); scanf_s("%d", &input_way);
		sp();
		if (input_way > 3 || input_way < 1) {
			printf_s("Неверное значение способа заполнения массива!\n"
				"Значение должно быть от 1 до 3.\n");
		}
	} while (input_way > 3 || input_way < 1);
	return input_way;
}

//===========================================================================================//
//                                                   -=[ Функции ввода массива ]=-

/*                 Функция вывода массива на экран.
                         На входе получает:
* «arr» - указатель на массив
* «array_size» - размерность массива
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

	if (count == 0) printf_s("отсутствуют.\n");
	sp();
}

void array_tobinary(struct employees* arr, int array_size, const char filename[]) {
	FILE* binary;
	errno_t err;
	int line = 1;
	err = fopen_s(&binary, filename, "wb");

	fwrite(&array_size, 1, sizeof(array_size), binary);
	fwrite(arr, sizeof(arr[array_size]), array_size, binary);

	fclose(binary);
	printf_s("Записан в бинарный файл!\n");
	sp();
}

void output(struct employees* arr, int array_size) {
	int output_way;
	do
	{
		printf_s("Способы вывода массива:\n"
			"1) На экран\n"
			"2) В бинарный файл '%s'\n\n"
			"Каким способом вы хотите вывести массив? ", bin_filename_out); scanf_s("%d", &output_way);
		sp();
		if (output_way > 2 || output_way < 1) {
			printf_s("Неверное значение способа заполнения массива!\n"
				"Значение должно быть от 1 до 2.\n");
		}
	} while (output_way > 2 || output_way < 1);

	switch (output_way) // Обработка введённого способа вывода массива
	{
	case 1: array_print(arr, array_size); break;                                     // Вывод массива на экран
	case 2: {array_tobinary(arr, array_size, bin_filename_out); array_print(arr, array_size); } break;  // Вывод массива в бинарный файл и на экран
	}
}

// ============================================================================ \\
\\ ============================================================================ //

// Главная функция, запускаемая при инициализации.
int main() {
	setlocale(LC_ALL, "Russian"); // Установка русской локализации
	system("chcp 1251"); // Установка русской локализации для даннх ввода/вывода
	system("cls");       // Очистка окна консоли от служебных сообщений
	struct employees arr[100]; // Инициализация структуры в виде массива
	int input_way = get_input_way();

	switch (input_way) // Обработка введённого способа заполнения массива
	{
	case 1: { // Выбран ввод с клавиатуры
		int array_size = array_input(arr);        // Функция ввода чисел с клавиатуры

		output(arr, array_size); // Функция вывода массива
	} break;

	case 2: { // Выбран ввод из файла
		int array_size = array_fromfile(arr, txt_filename_in);     // Выбрано заполнение массива из файла .txt

		output(arr, array_size); // Функция вывода массива
	} break;

	case 3: { // Выбран ввод из бинарного файла
		int array_size = array_frombinary(arr, bin_filename_in);   // Выбрано заполнение массива из бинарного файла

		output(arr, array_size); // Функция вывода массива
	} break;
	}


	return 0; // Завершение программы
}