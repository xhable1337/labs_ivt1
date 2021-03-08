#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 3.2
13. Определить площадь равнобедренной трапеции с основаниями а и b и углом X при большем основании а.
*/

void sp() {
	printf("------------------------------------------------\n");
}

int main() {
	setlocale(LC_ALL, "Russian");
	int a, b, X;
	double S, pi = 3.14159265;

	sp();
	printf_s("Введите большее основание a: "); scanf_s("%d", &a);
	sp();
	printf_s("Введите меньшее основание b: "); scanf_s("%d", &b);
	sp();
	printf_s("Введите угол X при большем основании: "); scanf_s("%d", &X);
	sp();

	S = 0.25 * ((pow(a, 2) - pow(b, 2)) * tan(X * (pi / 180)));

	printf_s("Площадь трапеции равна %.2f \n", S);
	sp();

	system("pause");
	return 0;
}