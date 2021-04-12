#include <stdio.h>
#include <conio.h>
#include <locale.h>

/*
Задача 3. Разработать функцию обмена значений двух
переменных.
*/

void sp() {
    printf("------------------------------------------------\n");
}

// Меняет местами значения переменных.
void swap(double *a, double *b);

int main(void) {
    setlocale(LC_ALL, "Russian");
    int x, y;
    printf_s("Введите x: "); scanf_s("%d", &x);
    printf_s("Введите y: "); scanf_s("%d", &y);

    sp();

    printf_s(
        "До вызова swap:\n"
        "x = %d\n"
        "y = %d\n", x, y
	);

    sp();
    
    swap(&x, &y);

    printf_s(
        "После вызова swap:\n"
        "x = %d\n"
        "y = %d\n", x, y
	);

    sp();
}

void swap(double* a, double* b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}