#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Лабораторная работа №4. Задача повышенной сложности №2

2.Текущее показание электронных часов m часов (0 ≤ 𝑚 ≤ 23),
n минут (0 ≤ 𝑛 ≤ 59), k секунд (0 ≤ 𝑘 ≤ 59). Какое время будут
показывать часы через p часов q минут r секунд (p>0, q>0, r>0)?
*/

void sp() {
    printf_s("------------------------------------------------\n");
}

int main() {
    setlocale(LC_ALL, "Russian");

    int hours_start = 0, minutes_start = 0, seconds_start = 0;
    int hours_passed = 0, minutes_passed = 0, seconds_passed = 0;
    int minutes_div = 0, hours_div = 0;
    int H = 0, M = 0, S = 0;
    
    // Ввод текущих показаний времени
    do {
        sp();
        printf_s("Введите текущее показание часов (0-23): "); scanf_s("%d", &hours_start);
        if (0 > hours_start || hours_start > 23) printf_s("[!] Введено неверное значение! Повторите попытку.\n");
    } while (0 > hours_start || hours_start > 23);

    do {
        sp();
        printf_s("Введите текущее показание минут (0-59): "); scanf_s("%d", &minutes_start);
        if (0 > minutes_start || minutes_start > 59) printf_s("[!] Введено неверное значение! Повторите попытку.\n");
    } while (0 > minutes_start || minutes_start > 59);   
    
    do {
        sp();
        printf_s("Введите текущее показание секунд (0-59): "); scanf_s("%d", &seconds_start);
        if (0 > seconds_start || seconds_start > 59) printf_s("[!] Введено неверное значение! Повторите попытку.\n");
        
    } while (0 > seconds_start || seconds_start > 59);
    
    // Ввод дельта-показаний времени
    do {
        sp(); 
        printf_s("Введите дельта часов: "); scanf_s("%d", &hours_passed);  // p
        if (hours_passed < 0) printf_s("[!] Введено неверное значение! Повторите попытку.\n");
    } while (hours_passed < 0);

    do {
        sp();
        printf_s("Введите дельта минут: "); scanf_s("%d", &minutes_passed);   // q
        if (minutes_passed < 0) printf_s("[!] Введено неверное значение! Повторите попытку.\n");
    } while (minutes_passed < 0);

    do {
        sp();
        printf_s("Введите дельта секунд: "); scanf_s("%d", &seconds_passed);  // r
        if (seconds_passed < 0) printf_s("[!] Введено неверное значение! Повторите попытку.\n");
    } while (seconds_passed < 0);


    // Вычислительный блок
    hours_div = minutes_passed / 60;
    hours_passed = (hours_passed + hours_div) % 24;

    minutes_div = seconds_passed / 60;
    minutes_passed = (minutes_passed + minutes_div) % 60;

    seconds_passed = seconds_passed % 60;

    hours_div = (minutes_start + minutes_passed + minutes_div) / 60;
    minutes_div = (seconds_start + seconds_passed) / 60;

    H = (hours_start + hours_passed + hours_div) % 24;
    M = (minutes_start + minutes_passed + minutes_div) % 60;
    S = (seconds_start + seconds_passed) % 60;

    sp(); 
    printf_s("Через заданное время на часах будет:\n%d ч., %d мин., %d сек.\n", H, M, S);
    sp();
    return 0;
}
