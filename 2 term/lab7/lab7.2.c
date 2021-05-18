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
void Init(size_t* row);
void arrayToScreen(int** arr, size_t row);
double arrayProccessing(int** arr, size_t row, double* arith_mean, int* mark_count, int* bad_mark, int* good_st);
double inputMarks(int** arr, size_t row);
// ===============================================

int main() {
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	system("cls");

	srand(time(NULL));

	size_t col = 1, row = 1;

	Init(&row);
	// Массив с колличеством студентов
	int** array = (int**)Malloc(row * sizeof(int*));

	inputMarks(array, row);
	arrayToScreen(array, row);

	double arith_mean;
	int mark_count;
	int bad_mark;
	int good_st;

	arrayProccessing(array, row, &arith_mean, &mark_count, &bad_mark, &good_st);

	printf_s("Количество оценок: %d\nКоличество неуд. оценок: %d\nКолличество отличников: %d\nСредний балл: %lf\n", mark_count, bad_mark, good_st, arith_mean);
	
	free(array);

	//system("pause");

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

// Получает размерность массива структуры студентов (row).
void Init(size_t* row) {
	int string;
	int column;
	sp();
	do {
		printf("Введите количество студентов: "); scanf_s("%d", &string);
		if (string <= 0)
		{
			printf_s("[!] Неправильный ввод размерности массива. Повторите ввод.\n");
			sp();
		}
	} while (string <= 0);

	*row = string;

}

// Выводит массив студентов arr размерностью row на экран.
void arrayToScreen(int** arr, size_t row) {
	int i, j;
	size_t col = 0;
	int init = 0;

	sl();

	for (i = 0; i < row; i++) {
		printf("Студент № %d:\n", i);

		if (init == 0) {
			col = arr[i][0];
			init = 1;
		}

		for (j = 1; j < col; j++) { printf("|%2d ", arr[i][j]); }

		printf("|\n");

		init = 0;
	}

	sl();
}

// Находит в массиве arr размерностью arr средний балл по предмету, количество неуд. оценок и количество отличников.
double arrayProccessing(int** arr, size_t row, double* arithMean, int* markCount, int* badMarks, int* goodStudents) {
	int i, j;
	size_t col = 0;
	int init = 0;

	*arithMean = 0;
	*markCount = 0;
	*badMarks = 0;
	*goodStudents = 0;

	for (i = 0; i < row; i++) {
		int good = 1;
		if (init == 0) {
			col = arr[i][0];
			init = 1;
		}

		for (j = 1; j < col; j++) {
			*markCount += 1;

			if (arr[i][j] < 3)
				*badMarks += 1;

			if (arr[i][j] != 5) 
				good = 0;

			*arithMean += arr[i][j];
		}

		if (good) *goodStudents += 1;

		init = 0;
	}

	*arithMean /= *markCount;
}

// Получает оценки студентов с клавиатуры и записывает их в массив arr размерностью row.
double inputMarks(int** arr, size_t row) {
	int i, j, mark;

	int counter = 0, input;

	int* values = NULL;
	int* many_numbers;

	for (i = 0; i < row; i++) {
		values = NULL;
		counter = 1;

		do
		{
			counter++;
			int check = 0;
			do {

				printf("Оценка [%d] студента № %d: ", counter - 1, i); scanf_s("%d", &input);
				if (input < 0 || input > 5) {
					printf("Неверное значение оценки\n");
					check = 0;
				}
				else check = 1;
			} while (!check);

			// при добавлении нового числа, увеличиваем массив на 1
			many_numbers = (int*)Realloc(values, counter * sizeof(int));
			// записываем колличество оценок студента в нулевой элмент массива
			many_numbers[0] = counter - 1;

			if (many_numbers != NULL)
			{
				values = many_numbers;
				values[counter - 1] = input;                      // добавить к массиву только что введённое число
			}
			else
			{
				free(values);                                   // удалить массив
				printf("Ошибка перевыделения памяти!");
				exit(1);                                        // завершить работу программы
			}
		} while (input != 0);

		arr[i] = values;

		sl();
	}
}