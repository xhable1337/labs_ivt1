#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>
#include <limits.h>
#include <math.h>
#include <time.h>

#define MAX_VALUE 1000 

void sp() {
	printf("------------------------------------------------\n");
}
void sl() {
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

// ============== Прототипы функций ==============
void* Malloc(size_t size);
void* Realloc(void* block, size_t size);
void Init(size_t* col, size_t* row);
void arrayInput(double* arr, size_t col, size_t row);
void arrayRandom(double* arr, size_t col, size_t row);
double arrayProccessing(double* array, size_t col, size_t row);
void arrayToScreen(double* arr, size_t col, size_t row, double max_sum);
void input(double* arr, size_t col, size_t row);
// ===============================================

int main() {
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	system("cls");

	srand(time(NULL));

	size_t col, row;

	double* arr;

	Init(&col, &row);

	arr = (double*)Malloc(col * row * sizeof(double));

	input(arr, col, row);

	arrayToScreen(arr, col, row, arrayProccessing(arr, col, row));

	system("pause");

	return 0;
}

// Выделяет память размером size.
void* Malloc(size_t size) {
	void* point = malloc(size);

	if (!point) {
		printf("Недостаточно памяти!\n"); exit(1);
	}

	return point;
}

// Перевыделяет память на block размером size.
void* Realloc(void* block, size_t size) {
	void* point = realloc(block, size);

	if (!point) {
		printf("Недостаточно памяти!\n"); exit(1);
	}

	return point;
}

// Получает размерность массива col и row.
void Init(size_t* col, size_t* row) {
	int string, column;
	sp();
	do {
		printf("Введите количество строк: "); scanf_s("%d", &string);
		printf("Введите количество столбцов: "); scanf_s("%d", &column);
		if (string <= 0 || column <= 0)
		{
			printf_s("[!] Неправильный ввод размерности массива. Повторите ввод.\n");
			sp();
		}
	} while (string <= 0 || column <= 0);

	*row = string; *col = column;
}

// Заполняет массив arr размерностью col x raw с клавиатуры.
void arrayInput(double* arr, size_t col, size_t row) {
	int i, j;

	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
		{
			printf("Введите arr[%d][%d]: ", i, j);
			scanf_s("%lf", &arr[i * row + j]);
		}
		sp();
	}

}

// Осуществляет пользовательский выбор способа заполнения массива arr размерностью col x row.
void input(double* arr, size_t col, size_t row) {
	int choice = 0;

	do
	{
		printf_s("Способы ввода массива:\n"
			"1) Ввод с клавиатуры\n"
			"2) Заполнение с помощью псевдо-рандома\n\n"
			"Каким способом вы желаете заполнить массив? ");
		scanf_s("%d", &choice);
		if (choice < 1 || choice > 2) printf_s("[!] Неправильный выбор! Число должно быть равно 1 или 2.\n\n");
	} while (choice < 1 || choice > 2);
	
	switch (choice)
	{
	case 1:
		arrayInput(arr, col, row);
		break;
	case 2:
		arrayRandom(arr, col, row);
		break;
	default:
		printf_s("[!] Произошла ошибка в switch.\n\n");
		exit(500);
	}
}

// Выводит массив arr размерностью col x row и максимальную сумму среди строк на экран.
void arrayToScreen(double* arr, size_t col, size_t row, double max_sum) {
	int i, j;
	sl();

	for (i = 0; i < col; i++) {

		for (j = 0; j < row; j++) { printf("%8.1lf ", arr[i * row + j]); }

		printf("\n");

	}

	sp();

	printf("\nМаксимальная сумма элементов строк: %.3lf.\n", max_sum);
}

// Заполняет массив arr размерностью col x row псевдослучайными числами.
void arrayRandom(double* arr, size_t col, size_t row) {
	int i, j;

	for (i = 0; i < col; i++) {
		for (j = 0; j < row; j++) {
			arr[i * row + j] = rand() % MAX_VALUE + 1.0;
		}
	}
}

// Среди сумм строк массива arr размерностью col x row находит максимальное значение.
double arrayProccessing(double* array, size_t col, size_t row) {
	int i, j;
	double sum = 0, max_sum = -99999999;

	for (i = 0; i < col; i++) {
		for (j = 0; j < row; j++) {
			sum += array[i * row + j];
		}

		if (sum > max_sum) max_sum = sum;
		sum = 0;
	}

	return max_sum;
}