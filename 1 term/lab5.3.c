#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа 5. Дополнительное задание г)
Даны координаты точки. Определить принадлежность точки
заштрихованной области, представленной на рисунке.
*/

void sp() {
	printf("------------------------------------------------\n");
}

// Функция проверки на принадлежность точки (x; y) треугольнику (x1; y1), (x2; y2;), (x3; y3)
int is_inTriangle(double x, double y, double x1, double y1, double x2, double y2, double x3, double y3) {
	
	double side1 = (x1 - x) * (y2 - y1) - (x2 - x1) * (y1 - y); // Скалярное произведение 1 стороны
	double side2 = (x2 - x) * (y3 - y2) - (x3 - x2) * (y2 - y); // Скалярное произведение 2 стороны
	double side3 = (x3 - x) * (y1 - y3) - (x1 - x3) * (y3 - y); // Скалярное произведение 3 стороны

	//printf_s("\n\nside1 = %lf\nside2 = %lf\nside3 = %lf\n\n", side1, side2, side3);

	if ((side1 >= 0 && side2 >= 0 && side3 >= 0) || (side1 <= 0 && side2 <= 0 && side3 <= 0)) return 1; // Точка лежит в треугольнике
	else return 0; // Точка не лежит в треугольнике

}

// Функция проверки на принадлежность точки (x; y) прямоугольнику (x1; y1), (x2; y2;), (x3; y3), (x4; y4)
int is_inRectangle(double x, double y, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
	int left_triangle = is_inTriangle(x, y, x1, y1, x2, y2, x3, y3); // Принадлежность точки левому треугольнику прямоугольника (1/0)
	int right_triangle = is_inTriangle(x, y, x1, y1, x3, y3, x4, y4); // Принадлежность точки правому треугольнику прямоугольника (1/0)
	
	//printf_s("\n\nleft_triangle = %d\nright_triangle = %d\n\n", left_triangle, right_triangle);

	if (left_triangle == 1 || right_triangle == 1) return 1;
	else return 0;
}

int main() {
	setlocale(LC_ALL, "Russian");
	double x, y;
	sp(); printf_s("Введите x точки: "); scanf_s("%lf", &x);
	sp(); printf_s("Введите y точки: "); scanf_s("%lf", &y);
	sp();

	int inTriangle1 = is_inTriangle(x, y, -1, 0, -1, 1, 0, 0);
	int inTriangle2 = is_inTriangle(x, y, 1, 1, 0, 0, 1, 0);
	int inRectangle = is_inRectangle(x, y, -1, -2, -1, 0, 1, 0, 1, -2);

	//printf_s("\n\ninTri1 = %d\ninTri2 = %d\ninRect = %d\n\n", inTriangle1, inTriangle2, inRectangle);

	if (inRectangle == 1 || inTriangle1 == 1 || inTriangle2 == 1) printf_s("Точка (%.3lf; %.3lf) лежит в заданной фигуре.\n", x, y);
	else printf_s("Точка (%.3lf; %.3lf) не лежит в заданной фигуре.\n", x, y);

	sp();
	return 0;
}