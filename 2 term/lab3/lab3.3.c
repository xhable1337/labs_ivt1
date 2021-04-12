#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <SDL.h>

#define SCREEN_WIDTH  900
#define SCREEN_HEIGHT  900
#define DELAY_TIME 30000
//#define DEBUG

int x1 = 1, x2 = 15;

double A = 0, B = 0, C = 0;
int scale = 0;

int surH = SCREEN_HEIGHT / 2;
int surW = SCREEN_WIDTH / 2;

double pixx = 0, pixy = 0;
double step = 0.01;

void draw_circle(SDL_Renderer* renderer, int x, int y, int radius);
void draw_graph_base(SDL_Renderer* renderer, int left_limit, int right_limit);
void draw_graph(SDL_Renderer* renderer, double A, double B, double C);
inline double toScreen(double graph_coord, int axis);
void input();


void sp() {
    printf("------------------------------------------------\n");
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    input(); // Ввод данных с клавиатуры

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

            // Фон
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);   // Белый цвет
            SDL_RenderClear(renderer);

            draw_graph_base(renderer, x1, x2); // Отрисовка координатной плоскости

            draw_graph(renderer, A, B, C);     // Отрисовка графика функции Y=(Ax+B)^0.5+C, [0;15].

            SDL_RenderPresent(renderer);

            SDL_Delay(DELAY_TIME);

            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
    }
    return 1;
}

// Функция ввода коэффициентов A, B, C и масштаба scale с клавиатуры
void input() {
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

    // switch по масштабу графика
    // Мелкий  — 20 пикс/ед
    // Средний — 40 пикс/ед
    // Крупный — 80 пикс/ед
    switch (scale)
    {
    case 1: pixx = pixy = 20; break;
    case 2: pixx = pixy = 40; break;
    case 3: pixx = pixy = 80; break;
    default:
        break;
    }
}

// Отрисовывает круг c центром в точке с координатами [x; y] радиусом radius.
void draw_circle(SDL_Renderer* renderer, int x, int y, int radius) {
    int point_x;
    int point_y;

    while (radius > 0)
    {
        for (float t = 0; t < 360; t += 0.1)
        {

            point_x = x + radius * cos(t * M_PI / 180);
            point_y = y + radius * sin(t * M_PI / 180);
            SDL_RenderDrawPoint(renderer, point_x, point_y);
        }
        radius--;
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

// Отрисовывает координатную плоскость и ограничение [left_limit; right_limit]
void draw_graph_base(SDL_Renderer* renderer, int left_limit, int right_limit) {
    // Отрисовка клеток
    SDL_SetRenderDrawColor(renderer, 215, 215, 215, 255); // Светло-серый цвет
    for (int i = -25; i < 25; i++)
    {
        SDL_RenderDrawLine(renderer, toScreen(i, 'x'), 0, toScreen(i, 'x'), SCREEN_HEIGHT); // Горизонтальные линии клеток
        SDL_RenderDrawLine(renderer, 0, toScreen(i, 'y'), SCREEN_WIDTH, toScreen(i, 'y')); // Вертикальные линии клеток
    }

    // Отрисовка ограничения графика функции
    SDL_SetRenderDrawColor(renderer, 255, 153, 0, 255); // Красный цвет
    SDL_RenderDrawLine(renderer, toScreen(left_limit, 'x'), 0, toScreen(left_limit, 'x'), SCREEN_HEIGHT); // Ограничение по x1
    SDL_RenderDrawLine(renderer, toScreen(right_limit, 'x'), 0, toScreen(right_limit, 'x'), SCREEN_HEIGHT); // Ограничение по x2

    // Отрисовка осей
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);  // Чёрный цвет
    SDL_RenderDrawLine(renderer, 0, surH, SCREEN_WIDTH, surW);  // Ox
    SDL_RenderDrawLine(renderer, surW, 0, surW, SCREEN_HEIGHT); // Oy

    // Отрисовка единичных точек на осях [v2]
    SDL_SetRenderDrawColor(renderer, 255, 3, 62, 255); // Красный цвет
    for (int i = -25; i < 25; i += 1)
    {
        draw_circle(renderer, toScreen(0, 'x'), toScreen(i, 'y'), 2);
        draw_circle(renderer, toScreen(i, 'x'), toScreen(0, 'y'), 2);
    }

}

// Отрисовывает график функции Y=(Ax+B)^0.5+C, [0;15].
void draw_graph(SDL_Renderer* renderer, double A, double B, double C) {
    // Отрисовка графика функции
    SDL_SetRenderDrawColor(renderer, 0, 127, 171, 255); // Голубой цвет
    for (double i = x1; i < x2; i += step)
    {
        double y = sqrt(A * i + B) + C;                  // Значение функции
        double y2 = sqrt(A * (i + step) + B) + C;        // Значение функции на следующем шаге
        if (isnan(y) || isnan(y2)) continue;             // Проверка на NaN (NaN — функция не определена в данной точке)

#ifdef DEBUG
        printf_s("i = %lf | y = %lf | y2 = %lf\n", i, y, y2);
#endif
        // Отрисовка линии значения функции от нынешнего шага до следующего
        SDL_RenderDrawLine(renderer,
            toScreen(i, 'x'),
            toScreen(y, 'y'),
            toScreen(i + step, 'x'),
            toScreen(y2, 'y')
        );
    }

}


