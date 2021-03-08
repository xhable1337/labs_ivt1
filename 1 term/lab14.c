#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>

/* Лабораторная работа 14.
13. Определить, содержатся ли в массиве хотя бы два
отрицательных числа. Если да, прибавить сумму этих чисел ко всем
элементам массива. В противном случае оставить массив
неизменным.
________________________________________________________________
За основу берется выполненное задание предыдущей
лабораторной работы. К реализованному функционалу добавить
следующие возможности: считывание массива из файла; сохранение
массива в другой файл после выполненных с ним преобразований
(если такой файл есть, его предыдущее содержимое
перезаписывается).
*/

// Декоративная функция для вывода.
void sp() {
	printf("------------------------------------------------\n");
}

//                                                   -=[ Функции ввода массива ]=-

/* Функция заполнения массива с клавиатуры.
На входе получает:
* arr - указатель на массив
* array_size - размерность массива
*/
void array_input(int* arr, int array_size) {
	sp();
	for (int i = 0; i < array_size; i++)
	{
		printf_s("Введите arr[%d]: ", i); scanf_s("%d", &arr[i]);
	}
}

/* Функция заполнения массива случайными числами.
На входе получает:
* arr - указатель на массив
* array_size - размерность массива
* A - начальное число диапазона случайных чисел
* B - конечное число диапазона случайных чисел
*/
void array_random(int* arr, int array_size, int A, int B) {
	int random;
	sp();
	for (int i = 0; i < array_size; i++)
	{
		random = rand() % (B - A + 1) + A; // Генерация псевдослучайного числа
		arr[i] = random; // Присваивание элементу массива псевдослучайного числа
		printf_s("Заполнен элемент arr[%d] = %d\n", i, random);
	}
}

// Функция получения размерности массива из текстового файла input.txt (должен быть в одном каталоге с исполняемым!)
int array_fromfile_arraysize() {
	int array_size;
	errno_t err;
	FILE* file;
	err = fopen_s(&file, "input.txt", "rt");
	do
	{
		if (err == 0) {
			fscanf_s(file, "%d", &array_size);
			printf_s("Размерность массива: %d\n", array_size);
			fclose(file);
		}
		else printf("Произошла ошибка при считывании файла.\n");
	} while (err != 0);

	return array_size;
}

// Функция получения массива из текстового файла input.txt (должен быть в одном каталоге с исполняемым!)
void array_fromfile(int* arr, int array_size) {
	errno_t err;
	FILE* file;
	int element = 0;
	err = fopen_s(&file, "input.txt", "rt");
	do { 
		if (err == 0)
		{
			fscanf_s(file, "%d", &array_size);
			for (int i = 0; i < array_size; i++) { 
				fscanf_s(file, "%d", &element); 
				arr[i] = element;
				printf_s("arr[%d] = %d\n", i, arr[i]);
			}	
		}
		else { printf("Произошла ошибка при считывании файла."); exit(500); }
	} while (err != 0);
	fclose(file);
	sp();
	printf_s("Массив успешно прочитан из файла!\n");
}

// ============================================================================ \\
\\ ============================================================================ //

/* Функция выполнения действий с массивом, исходя из условий задачи.
На входе получает:
* arr - указатель на массив
* array_size - размерность массива
*/
void array_processing(int* arr, int array_size) {
	int negative_count = 0, negative_sum = 0;
	for (int i = 0; i < array_size; i++)
	{
		if (arr[i] < 0) // Подсчёт количества и суммы отрицательных элементов массива
		{
			negative_count++;
			negative_sum += arr[i];
		}
	}

	if (negative_count >= 2) // Обработка условия по количеству отрицательных эл-в массива
	{
		for (int i = 0; i < array_size; i++)
		{
			arr[i] += negative_sum;
		}
	}
}

//                                                  -=[ Функции вывода массива ]=-

// Функция определения способа вывода массива
int array_output_way() {
	int output_way = 0;
	do
	{
		sp();
		printf_s("Способы вывода массива:\n"
			"1) На экран\n"
			"2) В файл 'output.txt'\n\n"
			"Каким способом вы хотите вывести массив? "); scanf_s("%d", &output_way);
		sp();
		if (output_way > 2 || output_way < 1) {
			printf_s("Неверное значение способа заполнения массива!\n"
				"Значение должно быть равно 1 или 2.\n");
		}
	} while (output_way > 2 || output_way < 1);
	return output_way;
}

/* Функция вывода массива на экран.
На входе получает:
* arr - указатель на массив
* array_size - размерность массива
*/
void array_print(int* arr, int array_size) {
	int element;
	sp();
	printf_s("Список элементов массива:\n");
	for (int i = 0; i < array_size; i++)
	{
		element = arr[i];
		printf_s("arr[%d] = %d\n", i, element);
	}
	sp();
}

/* Функция вывода массива в текстовый файл output.txt (должен быть в одном каталоге с исполняемым!)
На входе получает:
* arr - указатель на массив
* array_size - размерность массива
*/
void array_tofile(int* arr, int array_size) {
	FILE* file = NULL;
	errno_t err;
	err = fopen_s(&file, "output.txt", "w+");
	fprintf_s(file, "Массив состоит из %d элементов.\n"
		"Список элементов массива:\n\n", array_size);

	for (int i = 0; i < array_size; i++) fprintf_s(file, "arr[%d] = %d\n", i, arr[i]);
	fclose(file);
	sp();
	printf_s("Массив успешно записан в файл!\n");
	sp();
}

// ============================================================================ \\
\\ ============================================================================ //

// Главная функция, запускаемая при инициализации.
int main() {
	setlocale(LC_ALL, "Russian"); // Установка русской локализации
	int* arr; // Инициализация указателя на массив
	int input_way, output_way, A, B, array_size; // Инициализация остальных переменных
	srand(time(NULL)); // Генерация новой псевдослучайной последовательности
	do
	{
		sp();
		printf_s("Способы заполнения массива:\n"
			"1) С клавиатуры\n"
			"2) Случайными числами в заданном диапазоне\n"
			"3) Из файла 'input.txt'\n\n"
			"Каким способом вы хотите заполнить массив? "); scanf_s("%d", &input_way);
		sp();
		if (input_way > 3 || input_way < 1) {
			printf_s("Неверное значение способа заполнения массива!\n"
				"Значение должно быть от 1 до 3.\n");
		}
	} while (input_way > 3 || input_way < 1);

	switch (input_way) // Обработка введённого способа заполнения массива
	{
	case 1: { // Выбран ввод с клавиатуры
		printf_s("Введите размерность массива: "); scanf_s("%d", &array_size);
		arr = (int*)malloc(array_size * sizeof(int)); // Выделение памяти под массив
		array_input(arr, array_size);       // Функция ввода чисел с клавиатуры
		array_processing(arr, array_size);  // Функция обработки массива в соответствии с условием задачи
		output_way = array_output_way();    // Функция вывода массива в зависимости от выбора пользователя
		switch (output_way) {
		case 1: array_print(arr, array_size); break;
		case 2: array_tofile(arr, array_size); break;
		}
	} break;

	case 2: { // Выбрано заполнение псевдослучайными числами
		printf_s("Введите размерность массива: "); scanf_s("%d", &array_size);
		arr = (int*)malloc(array_size * sizeof(int)); // Выделение памяти под массив
		printf_s("Введите начало диапазона случайных чисел для заполнения массива: "); scanf_s("%d", &A);
		printf_s("Введите конец диапазона случайных чисел для заполнения массива: "); scanf_s("%d", &B);
		array_random(arr, array_size, A, B); // Функция заполнения массива псевдослучайными числами
		array_processing(arr, array_size);   // Функция обработки массива в соответствии с условием задачи
		output_way = array_output_way();     // Функция вывода массива в зависимости от выбора пользователя
		switch (output_way) {
		case 1: array_print(arr, array_size); break;
		case 2: array_tofile(arr, array_size); break;
		}
	} break;

	case 3: { // Выбран ввод из файла
		array_size = array_fromfile_arraysize();
		arr = (int*)malloc(array_size * sizeof(int)); // Выделение памяти под массив
		array_fromfile(arr, array_size);   // Выбрано заполнение массива из файла
		array_processing(arr, array_size); // Функция обработки массива в соответствии с условием задачи
		output_way = array_output_way();   // Функция вывода массива в зависимости от выбора пользователя
		switch (output_way) { // Обработка введённого способа вывода массива
		case 1: array_print(arr, array_size); break;  // Выбран вывод на экран
		case 2: array_tofile(arr, array_size); break; // Выбран вывод в файл
		}
	}
	}
	return 0; // Завершение программы
}