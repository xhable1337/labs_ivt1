#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include<Windows.h>

struct raggedArray {

	int** Data = NULL;
	int* Column = NULL;
	int String = 0;
};

void sp() {

	printf("------------------------------------------------\n");
}

//функция заполнения массива случайными значениями
void inputArrayRandom(raggedArray Array) {
	sp();

	int random = 0;
	int a = 0, b = 0;
	printf_s("Введите начало диапазона (a): "); scanf_s("%d", &a);
	printf_s("Введите конец диапазона (b): "); scanf_s("%d", &b);

	for (int i = 0; i < Array.String; i++) {

		for (int j = 0; j < Array.Column[i]; j++) {

			random = rand() % (a - b + 1) + a;
			Array.Data[i][j] = random;
			//printf("%d ", Array.Data[i][j]);
		}

		printf("\n");
	}
}

//Функция заполнения массива пользователем
void arrayInputKeyboard(raggedArray Array) {

	sp(); printf("Введите массив:\n");
	for (int i = 0; i < Array.String; i++) {
		for (int j = 0; j < Array.Column[i]; j++) {

			printf("Array[%d][%d] = ", i, j);
			scanf_s("%d", &Array.Data[i][j]);
		}
	}
}

//Функция считывания масиива из файла .txt
void inputArrayFromFile(raggedArray Array) {
	sp();

	errno_t error;
	FILE* file;
	error = fopen_s(&file, "IntputArrayTXT.txt", "r");
	if (error == 0) {

		fscanf_s(file, "%d", &Array.String);
		printf("Количество строк: %d\n", Array.String);
		Array.Data = (int**)malloc(Array.String * sizeof(int*));
		for (int i = 0; i < Array.String; i++) {
			scanf_s("%d", &Array.Column[i]);
			Array.Data[i] = (int*)malloc(Array.Column[i] * sizeof(int));
		}
		printf("Массив: \n");
		for (int i = 0; i < Array.String; i++) {
			for (int j = 0; j < Array.Column[i]; j++) {
				fscanf_s(file, "%d", &Array.Data[i][j]);
				printf("Array[%d][%d] = %d\n", i, j, Array.Data[i][j]);
			}
		}
		fclose(file); sp();
		printf("Данные из файлы были успешно прочитаны!\n");
	}
	else {
		printf("ERROR!!! Файл не был открыт успешно!\n");
	}
}

//Функция вывода масиива в файл .txt
void OutputArrayInFileTXT(raggedArray Array) {

	sp(); errno_t error;
	FILE* file;
	error = fopen_s(&file, "IntputArrayTXT.txt", "wt");

	fprintf_s(file, "Количество строк: %d\n", Array.String);
	for (int i = 0; i < Array.String; i++) {
		fprintf_s(file, "Количество столбцов: %d\n", Array.Column[i]);
	}
	if (error == 0) {
		fprintf_s(file, "Список элементов массива:\n");
		for (int i = 0; i < Array.String; i++) {
			for (int j = 0; j < Array.Column[i]; j++) {

				fprintf_s(file, "%d ", Array.Data[i][j]);
			}
			fprintf_s(file, "\n");
		}
		fclose(file);
		printf("Данные успешно записаны в файл!\n");
	}
	else {
		printf("ERROR!!! Данные не были успешно записаны в файл!\n");
	}
}


//Функция выбора ввода
int choice() {

	sp(); printf("Выберите способ ввода данных:\n");
	printf("1. Массив заполняется пользователем\n");
	printf("2. Массив заполняется случайными значениями\n");
	printf("3. Массив заполняется данными из файла .txt\n");
	printf("Способ: ");
	int x = 0;
	do
	{
		scanf_s("%d", &x);
		if (x < 1 || x > 3)
		{
			printf("ERROR!!! Неверное значение ввода. Введите значение еще раз:\n");
		}
	} while (x < 1 || x > 3);
	return x;
	sp();
}

void ArrayToScreen(raggedArray Array) {

	int i, j;
	for (i = 0; i < Array.String; i++) {

		printf("[%2d] ", i);
		for (j = 0; j < Array.Column[i]; j++) {
			printf("|%4d ", Array.Data[i][j]);
		}
		printf("|");
		printf("\n");
	}


}

void choice2(raggedArray Array) {


	switch (choice())
	{
	case 1: {
		arrayInputKeyboard(Array); break;
	}
	case 2: {
		inputArrayRandom(Array); break;
	}
	case 3: {
		inputArrayFromFile(Array);
		break;
	}
	}

	ArrayToScreen(Array);
	//OutputArrayInFileTXT(Array);
}


//Функция считывания массива из файла .bin
int InputArrayFromFileBin(int** Array, int& String, int& Columns) {

	FILE* bin;
	errno_t error;
	error = fopen_s(&bin, "InputBIN.bin", "rt");
	if (error == 0) {
		fread(&String, sizeof(int), 1, bin);
		fread(&Columns, sizeof(int), 1, bin);
		for (int i = 0; i < Columns; i++) {
			fread(&Array[i][0], sizeof(Array[0][0]), String, bin);
		}
		fclose(bin);
		printf("Данные успешно прочитаны.\n"); sp();
	}
	else {

		printf("ERROR!!! Произошла ошибка при считывании файла\n");
		system("pause");
		exit(404);
	}
}



void CreateArray(raggedArray* Array) {
	int strings = 0;
	printf("Введите количество строк: ");
	scanf_s("%d", &strings);
	Array->String = strings;

	Array->Data = (int**)malloc(Array->String * sizeof(int*));

	Array->Column = (int*)malloc(Array->String * sizeof(int));

	for (int i = 0; i < Array->String; i++) {

		printf("Количество столбцов в %d строке: ", i);
		scanf_s("%i", &Array->Column[i]);
		Array->Data[i] = (int*)malloc(Array->Column[i] * sizeof(int));

	}
}

void DeleteArray(raggedArray Array) {

	for (int i = 0; i < Array.String; i++) {

		free(Array.Data[i]);

	}
	free(Array.Data);
}

int main() {

	system("chcp 1251");
	system("cls");
	raggedArray Array;

	CreateArray(&Array);

	//printf("%d", Array.String);

	choice2(Array);

	DeleteArray(Array);

	system("pause");
	return 0;
}