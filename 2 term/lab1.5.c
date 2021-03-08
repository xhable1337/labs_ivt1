#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
/*
Задача 5. Создайте проект, содержащий листинг,
представленный на рис. 7. Запустите программу. Программа должна
вывести на экран числа от одного до десяти.
Определите, какие ошибки были допущены в коде, и исправьте
их.
*/
int main() {
    setlocale(LC_ALL, "Russian"); 
    system("chcp 1251"); 
    system("cls");       
    int x, * p;
    x = 10;
    for (int i = 1; i <= x; i++) {
        p = &i;
        printf("%d\n", *p);
    }
    return 0;
}