#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <SDL.h>



#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT  800
#define DELAY_TIME 30000

int x1 = 1, x2 = 15;

double A = 0, B = 0, C = 0;

int scale = 0;
int surH = SCREEN_HEIGHT / 2;
int surW = SCREEN_WIDTH / 2;

double pixx = 80;
double pixy = 80;
double step = 0.01;

void sp() {
    printf("------------------------------------------------\n");
}


void draw_circle(SDL_Renderer* Render, int surfacew, int surfaceh, int circle_radius) {
    int point_x;
    int point_y;

    while (circle_radius > 0)
    {
        for (float t = 0; t < 360; t += 0.1)
        {

            point_x = surfacew + circle_radius * cos(t * M_PI / 180);
            point_y = surfaceh + circle_radius * sin(t * M_PI / 180);
            SDL_RenderDrawPoint(Render, point_x, point_y);
        }

        circle_radius--;
    }
}

// Преобразует координату графика graph_coord в координаты пикселя в зависимости от выбранной оси axis (код символа 'x' или 'y').
inline double toScreen(double graph_coord, int axis) {
    if (axis == 'x')
        return surW + (graph_coord * pixx);
    else if (axis == 'y')
        return surH - (graph_coord * pixy);
    else
    {
        printf_s("[!] При использовании функции toScreen произошла ошибка.");
        exit(500);
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    /*do {
        printf_s("Введите диапазон графика функции (x1<x2)\n");
        scanf_s("%d %d", &x1, &x2);
    } while (x1 > x2);*/
    printf_s("Введите коэффициент A: ");
    scanf_s("%lf", &A);
    sp();
    printf_s("Введите коэффициент B: ");
    scanf_s("%lf", &B);
    sp();
    printf_s("Введите коэффициент C: ");
    scanf_s("%lf", &C);
    sp();
    
    do {
        printf_s("Выберите масштаб графика (1 — мелкий, 2 — средний, 3 — крупный): ");
        scanf_s("%d", &scale);
        if (scale < 1 || scale > 3) printf_s("[!] Введено неправильно значение масштаба! Повторите ввод.\n");
        sp();
    } while (scale < 1 || scale > 3);

    // Мелкий 20
    // Средний 40
    // Крупный 80
    switch (scale)
    {
    case 1: pixx = pixy = 20; break;
    case 2: pixx = pixy = 40; break;
    case 3: pixx = pixy = 80; break;
    default:
        break;
    }






    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf_s("[!] При создании окна SDL произошла ошибка. Текст ошибки:\n%s\n\n", SDL_GetError()); //- проверка на открытие окна;
    }
    else
    {
        SDL_Window* window = NULL; //окно 

        window = SDL_CreateWindow(u8"Згурский Евгений | Вариант 13", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf_s("[!] При создании окна SDL произошла ошибка. Текст ошибки:\n%s\n\n", SDL_GetError());
        }
        else
        {

            SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
          
            //Рисуем оси х у
            SDL_RenderDrawLine(renderer, 0, surH, SCREEN_WIDTH, surW);  // Ox
            SDL_RenderDrawLine(renderer, surW, 0, surW, SCREEN_HEIGHT); // Oy


            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

            for (int i = -SCREEN_WIDTH; i < SCREEN_WIDTH; i += pixx)
            {
                draw_circle(renderer, surW + i , surH, 2);
            }
            for (int i = -SCREEN_HEIGHT; i < SCREEN_HEIGHT; i += pixy)
            {
                draw_circle(renderer, surH, surW + i, 2);
            }
	
			SDL_RenderDrawLine(renderer, toScreen(x1, 'x'), 0, toScreen(x1, 'x'), SCREEN_HEIGHT); // Ограничение по x1
            SDL_RenderDrawLine(renderer, toScreen(x2, 'x'), 0, toScreen(x2, 'x'), SCREEN_HEIGHT); // Ограничение по x2

            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

            for (double i = x1; i < x2; i+=step)
            {
                double y = sqrt(A * i + B) + C;                  // Получаем координаты на коорд.плоскости
                double y2 = sqrt(A * (i+step) + B) + C;

                if (isnan(y) || isnan(y2)) continue;

                printf_s("i = %lf | y = %lf | y2 = %lf\n", i, y, y2);

                SDL_RenderDrawLine(renderer,
                    toScreen(i, 'x'),
                    toScreen(y, 'y'),
                    toScreen(i + step, 'x'),
                    toScreen(y2, 'y')
                );
            }

            SDL_RenderPresent(renderer);

            SDL_Delay(DELAY_TIME);

            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        } 
    }
    return 1;
}
