#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

void sp() {
	printf("------------------------------------------------\n");
}

int main() {
	setlocale(LC_ALL, "Russian");
	int gradeof1, i;
	double sum = 0, x, stx, e, add, factorial;

	sp();
	printf_s("Введите x: "); scanf_s("%lf", &x);
	sp();
	printf_s("Введите точность (е): "); scanf_s("%lf", &e);
	sp();

	gradeof1 = -1;
	factorial = x;
	stx = x;
	i = 1;
	do {
		factorial *= (x + i);
		add = gradeof1 * (fabs(cos(pow(i, i))) / factorial);
		sum += add;
		i++;
		stx *= x;
		gradeof1 *= -1;
		printf_s("Добавлено число %.50lf\nТеперь сумма = %.50lf\n", add, sum);
		sp();
	} while (fabs(add) > e);
	printf_s("Конечная сумма: %.50lf\n", sum);
	sp();

	return 0;
}