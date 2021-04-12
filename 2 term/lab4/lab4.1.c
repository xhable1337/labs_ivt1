#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <SDL.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT  800
#define DELAY_TIME 30000
#define PATTERN 1

#define pixx 40
#define pixy 40


int surH = SCREEN_HEIGHT / 2;
int surW = SCREEN_WIDTH / 2;


int surW_Max = SCREEN_WIDTH / pixx;
int surH_Max = SCREEN_HEIGHT / pixy;

double step = 0.01;

struct snake {
    int m;
    int x;
    int y;
};

void Body_init(struct snake* B, int count_max) {
    int i;
    if (PATTERN) {
        for (i = 0; i < count_max; i++) {
            B[i].x = i;
            B[i].y = 0;
            B[i].m = 3;
        }
    }
    else {
        for (i = 0; i < count_max; i++) {
            B[i].x = 0;
            B[i].y = 0;
            B[i].m = 1 - i;
        }

    }
}

void draw_square(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 180, 180, 200, 255);
    SDL_Rect rect = { toScreen(x,'x') - pixx,toScreen(y,'y') - pixy, pixx, pixy };
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
}

void Snake_Movement(SDL_Renderer* renderer, struct snake* B, int body_count) {
    if (PATTERN) {
        for (int i = 0; i < body_count; i++) {
            switch (B[i].m) {
            case 1: {
                draw_square(renderer, B[i].x += 1, B[i].y);
                if (B[i].x < surW_Max) {
                    B[i].m = 1;
                }
                else B[i].m = 3;
                break;
            }
            case 2: {
                draw_square(renderer, B[i].x -= 1, B[i].y);
                if (B[i].x > 1) {
                    B[i].m = 2;
                }
                else B[i].m = 3;
                break;
            }
            case 3: {
                draw_square(renderer, B[i].x, B[i].y -= 1);

                if (B[i].x > 1) {
                    B[i].m = 2;
                }
                if (B[i].x < surW_Max) {
                    B[i].m = 1;
                }

                break;
            }
            }

        }

    }
    else {
        for (int i = 0; i < body_count; i++) {

            if (B[i].m < 1) {
                B[i].m++;
            }
            else {
                switch (B[i].m) {
                case 1: {
                    draw_square(renderer, B[i].x += 1, B[i].y);
                    B[i].m = 3;
                    break;
                }
                case 3: {
                    draw_square(renderer, B[i].x, B[i].y -= 1);
                    B[i].m = 1;

                    break;
                }
                }
            }
        }

    }



}

// Преобразует координату графика graph_coord в координаты пикселя в зависимости от выбранной оси axis (код символа 'x' или 'y').
inline toScreen(int graph_coord, int axis) {
    if (axis == 'x')
        return 0 + (graph_coord * pixx);
    else if (axis == 'y')
        return 0 - (graph_coord * pixy);
    else
    {
        printf_s("[!] При использовании функции toScreen произошла ошибка.");
        exit(500);
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    struct snake* body[10];
    int body_count = 10;
    Body_init(body, body_count);

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
            SDL_SetRenderDrawColor(renderer, 215, 215, 215, 255); // Светло-серый цвет

            int run = 1;
            while (run) {

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                SDL_RenderClear(renderer);

                Snake_Movement(renderer, body, body_count);

                SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
                for (int i = -25; i < 25; i++)
                {
                    SDL_RenderDrawLine(renderer, toScreen(i, 'x'), 0, toScreen(i, 'x'), SCREEN_HEIGHT); // Горизонтальные линии клеток
                    SDL_RenderDrawLine(renderer, 0, toScreen(i, 'y'), SCREEN_WIDTH, toScreen(i, 'y')); // Вертикальные линии клеток
                }
                SDL_RenderPresent(renderer);

                SDL_Delay(100);

            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

            SDL_RenderPresent(renderer);

            SDL_Delay(1000);

            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
    }
    return 1;
}