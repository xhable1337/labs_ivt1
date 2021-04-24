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


void* Malloc(size_t size) {
	void* point = malloc(size);

	if (!point) {
		printf("Недостаточно памяти!\n"); exit(1);
	}

	return point;
}

void* Realloc(void* block, size_t size) {
	void* point = realloc(block, size);

	if (!point) {
		printf("Недостаточно памяти!\n"); exit(1);
	}

	return point;

}

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
void input(double* arr, size_t col, size_t row) {

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

// Выводит массив arr размерностью col x row и максимальную сумму среди строк на экран.
void arrayToScreen(double* arr, size_t col, size_t row, double max_sum) {

	int i, j;
	sl();

	for (i = 0; i < col; i++) {

		for (j = 0; j < row; j++) { printf("%8.1lf ", arr[i * row + j]); }

		printf("\n");

	}

	sp();

	printf("Максимальная сумма элементов строк: %lf", max_sum);

}

// Заполняет массив arr размерностью col x row псевдослучайными числами.
void arrayRandom(double* arr, size_t col, size_t row) {

	int i, j;

	for (i = 0; i < col; i++) {
		for (j = 0; j < row; j++) {
			arr[i * row + j] = rand() % MAX_VALUE + 1;
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

int main() {
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	system("cls");

	srand(time(NULL));

	size_t col, row;

	double* arr;

	Init(&col, &row);

	arr = (double*)Malloc(col * row * sizeof(double));

	//input(Array,col,row);
	arrayRandom(arr, col, row);

	arrayToScreen(arr, col, row, arrayProccessing(arr, col, row));

	system("pause");

	return 0;
}