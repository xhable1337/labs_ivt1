#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/*
Задача 4. Создайте проект, содержащий листинг,
представленный на рис. 6. Запустите программу. Программа должна
вывести на экран значение переменной х.
Определите, какие ошибки были допущены в коде, и исправьте
их.
*/

int main() {
    setlocale(LC_ALL, "Russian"); 
    system("chcp 1251"); 
    system("cls");       
    int x, * p;
    x = 10;
    p = &x;
    printf("%d", *p);
    return 0;
}