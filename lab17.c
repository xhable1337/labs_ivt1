#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>

/* Лабораторная работа 17.
13. Вычислить среднее арифметическое элементов, лежащих
выше главной диагонали матрицы.
__________________________________________________________________
          { 4 / (i + j - 1); i < j
b[i][j] = { 0; i = j
          { 1 / 2i + 7j - 1: i > j
*/


/*
Синтаксис файла input.txt


<количество_строк = i>
<количество_столбцов = j>
<a[1][1]>
<a[1][2]>
...
<a[1][j]>
<a[2][1]>
<a[2][2]>
...
<a[2][j]>
..........
<a[i][j]>
*/



// Декоративная функция для вывода.
void sp() {
	printf("------------------------------------------------\n");
}

//                                                   -=[ Функции ввода массива ]=-

// Функция заполнения массива с клавиатуры.
int* array_input(double arr[100][100], int* array_size) {
	int string, column;
	sp();
	printf_s("Введите количество строк: "); scanf_s("%d", &string);
	printf_s("Введите количество столбцов: "); scanf_s("%d", &column);
	array_size[0] = string; array_size[1] = column;
	int line = 1; int element;
	for (int i = 1; i <= string; i++)
	{
		for (int j = 1; j <= column; j++)
		{
			printf_s("Введите arr[%d][%d]: ", i, j); scanf_s("%lf", &arr[i][j]);
		}
		sp();
	}

	return array_size;
}

// Функция получения массива из текстового файла input.txt (должен быть в одном каталоге с исполняемым!)
int* array_fromfile(double arr[100][100], int* array_size) {
	errno_t err;
	FILE* file;
	int element = 0;
	int string, column;
	int line = 1;
	err = fopen_s(&file, "input.txt", "rt");
	fscanf_s(file, "%d", &string);
	fscanf_s(file, "%d", &column);
	array_size[0] = string; array_size[1] = column;

	for (int i = 1; i <= string; i++)
	{
		for (int j = 1; j <= column; j++)
		{
			fscanf_s(file, "%lf", &arr[i][j]);
			printf_s("arr[%d][%d] = %lf\n", i, j, arr[i][j]);
		}
		sp();
	}

	fclose(file);
	printf_s("Массив успешно прочитан из файла!\n");
	sp();
	return array_size;
}

// Функция заполнения массива псевдослучайными числами из заданного диапазона.
int* array_random(double arr[100][100], int* array_size) {
	double random;
	int string, column, A, B;
	srand(time(NULL));

	printf_s("Введите количество строк: "); scanf_s("%d", &string);
	printf_s("Введите количество столбцов: "); scanf_s("%d", &column);
	printf_s("Введите начало диапазона: "); scanf_s("%d", &A);
	printf_s("Введите конец диапазона: "); scanf_s("%d", &B);
	array_size[0] = string; array_size[1] = column;
	sp();

	for (int i = 1; i <= string; i++)
	{
		for (int j = 1; j <= column; j++)
		{
			random = rand() % (B - A + 1) + A; // Генерация псевдослучайного числа
			arr[i][j] = random;
			printf_s("Заполнен элемент arr[%d][%d] = %lf\n", i, j, random);
		}
		sp();
	}
	return array_size;
}

// Функция заполнения массива из бинарного файла.
int* array_frombinary(double arr[100][100], int* array_size) {
	FILE* binary;
	errno_t err;
	int string, column;

	err = fopen_s(&binary, "input.bin", "rb");
	fread(&string, 1, sizeof(string), binary);
	fread(&column, 1, sizeof(column), binary);
	array_size[0] = string; array_size[1] = column;
	

	for (int i = 1; i <= string; i++)
	{
		for (int j = 1; j <= column; j++)
		{
			fread(&arr[i][j], 1, sizeof(arr[i][j]), binary);
		}
	}

	//fread(&arr, 1, sizeof(arr), binary);
	fclose(binary);

	//fread(&arr, 100, sizeof(arr), binary);
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
			"2) Из файла 'input.txt'\n"
			"3) Из бинарного файла 'input.bin'\n"
			"4) Заполнение псевдослучайными числами в заданном диапазоне\n"
			"5) Заполнение по формуле\n\n"
			"Каким способом вы хотите заполнить массив? "); scanf_s("%d", &input_way);
		sp();
		if (input_way > 5 || input_way < 1) {
			printf_s("Неверное значение способа заполнения массива!\n"
				"Значение должно быть от 1 до 5.\n");
		}
	} while (input_way > 5 || input_way < 1);
	return input_way;
}

// Функция заполнения массива по формуле.
int* array_formula(double arr[100][100], int* array_size) {
	int string, column;
	double element;
	printf_s("Введите количество строк: "); scanf_s("%d", &string);
	printf_s("Введите количество столбцов: "); scanf_s("%d", &column);
	array_size[0] = string; array_size[1] = column;

	for (int i = 1; i <= string; i++)
	{
		for (int j = 1; j <= column; j++)
		{
			if (i < j) element = 4.0 / ((i + j) - 1.0);
			if (i == j) element = 0;
			if (i > j) element = 1.0 / ((2.0 * i) + (7.0 * j) - 1.0);
			arr[i][j] = element;
			printf_s("Заполнен элемент arr[%d][%d] = %lf\n", i, j, element);
		}
		sp();
	}

	return array_size;
}


// ============================================================================ \\
\\ ============================================================================ //

// Функция нахождения среднего арифметического элементов, стоящих выше главной диагонали
double array_processing(double arr[100][100], int string, int column) {
	int i = 1, j = 1, s1 = 0;
	double sum = 0, count = 0, result = 0;

	while (i < string) { //строка
		s1 = j;
		while (s1 < column) { //столбец
			s1++;
			sum += arr[i][s1];
			count++;
		}
		s1 = 0;
		i++;
		j++;
	}
	result = (sum / count);
	return result;
}

// ============================================================================ \\
\\ ============================================================================ //

//                                                   -=[ Функции вывода массива ]=-

// Функция вывода массива на экран.
void array_print(double arr[100][100], int string, int column) {
	for (int i = 1; i <= string; i++)
	{
		for (int j = 1; j <= column; j++)
		{
			printf_s("arr[%d][%d] = %lf\n", i, j, arr[i][j]);
		}
		sp();
	}
	double result = array_processing(arr, string, column);
	printf_s("Среднее арифметическое элементов: %lf\n", result);
}

// Функция вывода массива в бинарный файл.
void array_tobinary(double arr[100][100], int string, int column) {
	FILE* binary;
	errno_t err;
	int line = 1;
	err = fopen_s(&binary, "output.bin", "wb");

	fwrite(&string, 1, sizeof(string), binary);
	fwrite(&column, 1, sizeof(column), binary);

	for (int i = 1; i <= string; i++)
	{
		for (int j = 1; j <= column; j++)
		{
			fwrite(&arr[i][j], 1, sizeof(arr[i][j]), binary);
		}
	}

	//fwrite(&arr, 1, sizeof(arr), binary);
	fclose(binary);

	printf_s("Записан в бинарный файл!\n");
	sp();
	double result = array_processing(arr, string, column);
	printf_s("Среднее арифметическое элементов: %lf\n", result);
	sp();
}

// Функция вывода массива в текстовый файл.
void array_tofile(double arr[100][100], int string, int column) {
	FILE* file;
	errno_t err;
	err = fopen_s(&file, "output.txt", "wt");

	fprintf_s(file, "Массив размерностью %dx%d: \n\n", string, column);

	for (int i = 1; i <= string; i++)
	{
		for (int j = 1; j <= column; j++)
		{
			fprintf_s(file, "%lf   ", arr[i][j]);
		}
		fprintf_s(file, "\n");
	}

	double result = array_processing(arr, string, column);
	fprintf_s(file, "\nСреднее арифметическое элементов: %lf\n", result);
	fclose(file);
}

// Функция выбора способа вывода массива.
void output(double arr[100][100], int string, int column) {
	int output_way;
	do
	{
		printf_s("Способы вывода массива:\n"
			"1) На экран\n"
			"2) В бинарный файл 'output.bin'\n"
			"3) В текстовый файл 'output.txt'\n\n"
			"Каким способом вы хотите вывести массив? "); scanf_s("%d", &output_way);
		sp();
		if (output_way > 3 || output_way < 1) {
			printf_s("Неверное значение способа заполнения массива!\n"
				"Значение должно быть от 1 до 3.\n");
		}
	} while (output_way > 3 || output_way < 1);

	switch (output_way) // Обработка введённого способа вывода массива
	{
	case 1: array_print(arr, string, column); break;     // Вывод массива на экран
	case 2: array_tobinary(arr, string, column); break;  // Вывод массива в бинарный файл
	case 3: array_tofile(arr, string, column); break;  // Вывод массива в текстовый файл
	}
}

// ============================================================================ \\
\\ ============================================================================ //

// Главная функция, запускаемая при инициализации.
int main() {
	setlocale(LC_ALL, "Russian"); // Установка русской локализации
	system("chcp 1251"); // Установка русской локализации для даннх ввода/вывода
	system("cls");       // Очистка окна консоли от служебных сообщений
	double arr[100][100]; // Инициализация структуры в виде массива
	int string, column, arr_size[2]; // Инициализация остальных переменных
	int input_way = get_input_way(); // Получение способа заполнения массива

	switch (input_way) // Обработка введённого способа заполнения массива
	{
	case 1: { // Выбран ввод с клавиатуры
		int* array_size = array_input(arr, arr_size);   // Ввод массива с клавиатуры и получение массива с размерностью основного массива
		string = array_size[0]; column = array_size[1]; // "Распаковка" массива с размерностью основного массива

		output(arr, string, column);
	} break;

	case 2: { // Выбран ввод из файла
		int* array_size = array_fromfile(arr, arr_size);
		string = array_size[0]; column = array_size[1];

		output(arr, string, column);
	} break;

	case 3: { // Выбран ввод из бинарного файла
		int* array_size = array_frombinary(arr, arr_size);
		string = array_size[0]; column = array_size[1];

		output(arr, string, column);
	} break;

	case 4: { // Выбрано заполнения псевдослучайными числами
		int* array_size = array_random(arr, arr_size);
		string = array_size[0]; column = array_size[1];

		output(arr, string, column);
	} break;

	case 5: { // Выбрано заполнение по формуле
		int* array_size = array_formula(arr, arr_size);
		string = array_size[0]; column = array_size[1];

		output(arr, string, column);
	} break;
	}


	return 0; // Завершение программы
}