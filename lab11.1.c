#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

void sp() {
	printf("------------------------------------------------\n");
}

int main() {
	setlocale(LC_ALL, "Russian");
	int n; double x, sum = 0, add = 0;

	//const double e = 2.71828;

	sp();
	printf_s("Введите x: "); scanf_s("%lf", &x);
	sp();
	printf_s("Введите n: "); scanf_s("%d", &n);
	sp();

	for (double i = 1; i <= n; i++)
	{
		add = pow(-1, 1 - i) * 2 * log(x);
		//add = i * 2 * log(x);
		sum += add;
		printf_s("К сумме добавлено число: %lf\nТеперь сумма равна %lf\n", add, sum);
		sp();
	}
	printf_s("Сумма = %lf", sum);
	return 0;
}
