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

<a[0][0]>
<a[0][1]>
...
<a[0][j]>
<a[1][0]>
<a[1][1]>
...
<a[1][j]>
..........
<a[i][j]>
*/

// Декоративная функция для вывода.
void sp() {
	printf("------------------------------------------------\n");
}

const char txt_filename_in[] = "input.txt";      // Путь к файлу .txt, из которого нужно считать массив
const char bin_filename_in[] = "input.bin";      // Путь к файлу .bin, из которого нужно считать массив
const char txt_filename_out[] = "output.txt";    // Путь к файлу .txt, в который нужно записать массив
const char bin_filename_out[] = "output.bin";    // Путь к файлу .bin, в который нужно записать массив

//                                                   -=[ Функции ввода массива ]=-

// Заполняет массив arr с клавиатуры и возвращает массив размерностей массива arr.
int* array_input(double arr[100][100], int* array_size) {
	int string, column;
	do
	{
		printf_s("Введите количество строк: "); scanf_s("%d", &string);
		printf_s("Введите количество столбцов: "); scanf_s("%d", &column);
		
		if (string <= 0 || column <= 0)
		{
			printf_s("[!] Неправильный ввод размерности массива. Повторите ввод.\n");
			sp();
		}
	} while (string <= 0 || column <= 0);

	sp();
	array_size[0] = string; array_size[1] = column;
	int element;
	for (int i = 0; i < string; i++)
	{
		for (int j = 0; j < column; j++)
		{
			printf_s("Введите arr[%d][%d]: ", i, j); scanf_s("%lf", &arr[i][j]);
		}
		sp();
	}

	return array_size;
}

// Заполняет массив arr из текстового файла filename и возвращает массив размерностей массива arr.
int* array_fromfile(double arr[100][100], int* array_size, const char filename[]) {
	errno_t err;
	FILE* file;
	int element = 0;
	int string, column;
	err = fopen_s(&file, filename, "rt");

	if (err == 0)
	{
		fscanf_s(file, "%d", &string);
		fscanf_s(file, "%d", &column);
		array_size[0] = string; array_size[1] = column;

		for (int i = 0; i < string; i++)
		{
			for (int j = 0; j < column; j++)
			{
				fscanf_s(file, "%lf", &arr[i][j]);
				printf_s("arr[%d][%d] = %lf\n", i, j, arr[i][j]);
			}
			sp();
		}

		fclose(file);
	}
	else { printf("[!] Произошла ошибка при открытии файла."); exit(500); }
	
	return array_size;
}

// Заполняет массив arr псевдослучайными числами в заданном диапазоне и возвращает массив размерностей массива arr.
int* array_random(double arr[100][100], int* array_size) {
	double random;
	int string, column, A, B, temp;
	srand(time(NULL));

	do
	{
		printf_s("Введите количество строк: "); scanf_s("%d", &string);
		printf_s("Введите количество столбцов: "); scanf_s("%d", &column);

		if (string <= 0 || column <= 0)
		{
			printf_s("[!] Неправильный ввод размерности массива. Повторите ввод.\n");
			sp();
		}
	} while (string <= 0 || column <= 0);

	sp();
	printf_s("Введите начало диапазона: "); scanf_s("%d", &A);
	printf_s("Введите конец диапазона: "); scanf_s("%d", &B);
	array_size[0] = string; array_size[1] = column;
	sp();
	
	// Меняем местами начало и конец диапазона, если начало больше конца (A больше B)
	if (A > B) 
	{
		temp = B;
		B = A;
		A = temp;
	}

	for (int i = 0; i < string; i++)
	{
		for (int j = 0; j < column; j++)
		{
			random = rand() % (B - A + 1) + (double)A; // Генерация псевдослучайного числа в диапазоне [A; B]
			arr[i][j] = random;
			printf_s("Заполнен элемент arr[%d][%d] = %lf\n", i, j, random);
		}
		sp();
	}
	return array_size;
}

// Заполняет массив arr из бинарного файла filename и возвращает массив размерностей массива arr.
int* array_frombinary(double arr[100][100], int* array_size, const char filename[]) {
	FILE* binary;
	errno_t err;
	int string, column;

	err = fopen_s(&binary, filename, "rb");

	if (err == 0)
	{
		fread(&string, sizeof(string), 1, binary);
		fread(&column, sizeof(column), 1, binary);
		array_size[0] = string; array_size[1] = column;

		for (int i = 0; i < column; i++)
		{
			fread(&arr[i][0], sizeof(arr[0][0]), string, binary);
		}

		fclose(binary);
	}
	else { printf("[!] Произошла ошибка при открытии файла."); exit(500); }

	
	

	return array_size;
}

// Возвращает способ заполнения массива.
int get_input_way() {
	int input_way = 0;
	errno_t err;
	
	sp();
	printf_s("Способы заполнения массива:\n"
		"1) С клавиатуры\n"
		"2) Из файла '%s'\n"
		"3) Из бинарного файла '%s'\n"
		"4) Заполнение псевдослучайными числами в заданном диапазоне\n"
		"5) Заполнение по формуле\n\n"
		"Каким способом вы хотите заполнить массив? ", txt_filename_in, bin_filename_in); 
	err = scanf_s("%d", &input_way);
	sp();

	if (err != 0)
	{
		switch (input_way)
		{
		case 1: return input_way; break;
		case 2: return input_way; break;
		case 3: return input_way; break;
		case 4: return input_way; break;
		case 5: return input_way; break;
		default:
			printf_s("Неверное значение способа заполнения массива!\n"
				"Значение должно быть от 1 до 5.\n"); input_way = 0; get_input_way(); break;
		}
	}
	else 
	{
		printf_s("[!] Ошибка при вводе с клавиатуры! Завершение программы.");
		exit(500);
	}
		
}

// Заполняет массив arr по формуле и возвращает массив размерностей массива arr.
int* array_formula(double arr[100][100], int* array_size) {
	int string, column;
	do
	{
		printf_s("Введите количество строк: "); scanf_s("%d", &string);
		printf_s("Введите количество столбцов: "); scanf_s("%d", &column);

		if (string <= 0 || column <= 0)
		{
			printf_s("[!] Неправильный ввод размерности массива. Повторите ввод.\n");
			sp();
		}
	} while (string <= 0 || column <= 0);

	array_size[0] = string; array_size[1] = column;

	for (int i = 0; i < string; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (i < j)  arr[i][j] = 4.0 / (((double)i + (double)j) - 1.0);
			if (i == j) arr[i][j] = 0;
			if (i > j)  arr[i][j] = 1.0 / ((2.0 * i) + (7.0 * j) - 1.0);
			printf_s("Заполнен элемент arr[%d][%d] = %lf\n", i, j, arr[i][j]);
		}
		sp();
	}

	return array_size;
}

// ======================================================================================================

// Возвращает среднее арифметическое элементов, стоящих выше главной диагонали.
double array_processing(double arr[100][100], int string, int column) {
	double sum = 0, count = 0, result = 0;

	for (int i = 0; i < string; i++) {
		for (int j = 0; j < column; j++) {
			if (j > i)
			{
				sum += arr[i][j];
				count++;
			}
		}
	}

	result = (sum / count);
	return result;
}

// ======================================================================================================

//                                                   -=[ Функции вывода массива ]=-

// Выводит массив arr размерностью string×column в окно консоли.
void array_print(double arr[100][100], int string, int column) {
	for (int i = 0; i < string; i++)
	{
		for (int j = 0; j < column; j++)
		{
			printf_s("arr[%d][%d] = %lf\n", i, j, arr[i][j]);
		}
		sp();
	}
	double result = array_processing(arr, string, column);
	printf_s("Среднее арифметическое элементов: %lf\n", result);
}

// Записывает массив arr размерностью string×column в бинарный файл filename.
void array_tobinary(double arr[100][100], int string, int column, const char filename[]) {
	FILE* binary;
	errno_t err;
	err = fopen_s(&binary, filename, "wb");

	if (err == 0)
	{
		fwrite(&string, sizeof(string), 1, binary);
		fwrite(&column, sizeof(column), 1, binary);


		for (int i = 0; i < column; i++)
		{
			fwrite(&arr[i][0], sizeof(arr[0][0]), string, binary);
		}

		fclose(binary);
	}
	else { printf("[!] Произошла ошибка при открытии файла."); exit(500); }
	

	printf_s("Записан в бинарный файл!\n");
	sp();
	double result = array_processing(arr, string, column);
	printf_s("Среднее арифметическое элементов: %lf\n", result);
	sp();
}

// Записывает массив arr размерностью string×column в текстовый файл filename.
void array_tofile(double arr[100][100], int string, int column, const char filename[]) {
	FILE* file;
	errno_t err;
	err = fopen_s(&file, filename, "wt");
	if (err == 0)
	{
		fprintf_s(file, "Массив размерностью %dx%d: \n\n", string, column);

		for (int i = 0; i < string; i++)
		{
			for (int j = 0; j < column; j++)
			{
				fprintf_s(file, "%lf   ", arr[i][j]);
			}
			fprintf_s(file, "\n");
		}

		double result = array_processing(arr, string, column);
		fprintf_s(file, "\nСреднее арифметическое элементов: %lf\n", result);
		fclose(file);
	}
	else { printf("[!] Произошла ошибка при открытии файла."); exit(500); }
	
}

// Выбирает способ вывода массива.
void output(double arr[100][100], int string, int column) {
	int output_way;
	do
	{
		printf_s("Способы вывода массива:\n"
			"1) На экран\n"
			"2) В бинарный файл '%s'\n"
			"3) В текстовый файл '%s'\n\n"
			"Каким способом вы хотите вывести массив? ", bin_filename_out, txt_filename_out); scanf_s("%d", &output_way);
		sp();
		if (output_way > 3 || output_way < 1) {
			printf_s("Неверное значение способа заполнения массива!\n"
				"Значение должно быть от 1 до 3.\n");
		}
	} while (output_way > 3 || output_way < 1);

	switch (output_way) // Обработка введённого способа вывода массива
	{
	case 1: array_print(arr, string, column); break;     // Вывод массива на экран
	case 2: array_tobinary(arr, string, column, bin_filename_out); break;  // Вывод массива в бинарный файл
	case 3: array_tofile(arr, string, column, txt_filename_out); break;  // Вывод массива в текстовый файл
	}
}

// ======================================================================================================

// Главная функция, запускаемая при инициализации.
int main() {
	setlocale(LC_ALL, "Russian"); // Установка русской локализации
	system("chcp 1251"); // Установка русской локализации для даннх ввода/вывода
	system("cls");       // Очистка окна консоли от служебных сообщений
	double arr[100][100]; // Инициализация структуры в виде массива
	int string = 0, column = 0, arr_size[2]; // Инициализация остальных переменных
	int input_way = get_input_way(); // Получение способа заполнения массива
	int* array_size;

	switch (input_way) // Обработка введённого способа заполнения массива
	{
	case 1:  // Выбран ввод с клавиатуры
		array_size = array_input(arr, arr_size);   // Ввод массива с клавиатуры и получение массива с размерностью основного массива
		string = array_size[0]; column = array_size[1]; // "Распаковка" массива с размерностью основного массива
		break;

	case 2:  // Выбран ввод из файла
		array_size = array_fromfile(arr, arr_size, txt_filename_in);
		string = array_size[0]; column = array_size[1]; // "Распаковка" массива с размерностью основного массива
		printf_s("Массив успешно прочитан из файла!\n"); // Уведомление об успешном считывании массива
		sp();
		break;

	case 3:  // Выбран ввод из бинарного файла
		array_size = array_frombinary(arr, arr_size, bin_filename_in);
		string = array_size[0]; column = array_size[1]; // "Распаковка" массива с размерностью основного массива
		printf_s("Массив успешно прочитан из бинарного файла!\n"); // Уведомление об успешном считывании массива
		sp();
		break;

	case 4: // Выбрано заполнения псевдослучайными числами
		array_size = array_random(arr, arr_size);
		string = array_size[0]; column = array_size[1]; // "Распаковка" массива с размерностью основного массива
		break;

	case 5: // Выбрано заполнение по формуле
		array_size = array_formula(arr, arr_size);
		string = array_size[0]; column = array_size[1]; // "Распаковка" массива с размерностью основного массива
		break;
	}

	output(arr, string, column); // Вывод основного массива

	return 0; // Завершение программы
}