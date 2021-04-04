#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <SDL.h>



#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT  800

int surH = SCREEN_HEIGHT / 2;
int surW = SCREEN_WIDTH / 2;
int try_num = 1;

double pixx = 40;
double pixy = 40;
double step = 0.01;

int labyrinth[20][20] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void sp() {
    printf("------------------------------------------------\n");
}

struct Obstacles {
    int x;
    int y;
};

void draw_circle(SDL_Renderer* Render, int x, int y, int radius) {
    int point_x;
    int point_y;

    while (radius > 0)
    {
        for (float t = 0; t < 360; t += 0.1)
        {

            point_x = x + radius * cos(t * M_PI / 180);
            point_y = y + radius * sin(t * M_PI / 180);
            SDL_RenderDrawPoint(Render, point_x, point_y);
        }

        radius--;
    }
}


// Преобразует координату графика graph_coord в координаты пикселя в зависимости от выбранной оси axis (код символа 'x' или 'y').
inline double toScreen(double graph_coord, int axis) {
    if (axis == 'x')
        return 0 + (graph_coord * pixx);
    else if (axis == 'y')
        return 0 + (graph_coord * pixy);
    else
    {
        printf_s("[!] При использовании функции toScreen произошла ошибка.");
        exit(500);
    }
}

int checkObstacle(struct Obstacles* obs, int gx, int gy, int key) {
    
    for (int i = 0; i < 400; i++)
    {
        switch (key)
        {
        case 'w':
            if (gy - 1 == obs[i].y && gx == obs[i].x || gy - 1 < 0) return 1;
            break;
        case 'a':
            if (gx - 1 == obs[i].x && gy == obs[i].y || gx - 1 < 0) return 1;
            break;
        case 's':
            if (gy + 1 == obs[i].y && gx == obs[i].x || gy + 1 > 19) return 1;
            break;
        case 'd':
            if (gx + 1 == obs[i].x && gy == obs[i].y || gx + 1 > 19) return 1;
            break;
        default:
            printf_s("[!] При использовании функции checkObstacle произошла ошибка.");
            exit(500);
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    int alive = 1;
    struct Obstacles obs[400];

    Uint8* KEYS;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf_s("[!] При создании окна SDL произошла ошибка. Текст ошибки:\n%s\n\n", SDL_GetError()); //- проверка на открытие окна;
    }
    else
    {
        SDL_Window* window = NULL; //окно 
        SDL_Event event;
        int x = surW;
        int y = surH;
        int radius = pixx / 2 - 5;
        int start[2] = { 1, 0 };
        int end[2] = { 17, 19 };
        int gx = start[0], gy = start[1];
        window = SDL_CreateWindow(u8"Згурский Евгений | Вариант 13", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == NULL)
        {
            printf_s("[!] При создании окна SDL произошла ошибка. Текст ошибки:\n%s\n\n", SDL_GetError());
        }
        else
        {
            KEYS = (Uint8*)SDL_GetKeyboardState(NULL);
            SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
            while (alive) {
                
                while (SDL_PollEvent(&event)) {
                    SDL_PumpEvents();
                    switch (event.type) {
                    case SDL_QUIT:
                        alive = 0;
                        break;
                    case SDL_KEYDOWN:
                        if (KEYS[SDL_SCANCODE_LSHIFT]) {
                            gx = 5;
                        }

                        if (KEYS[SDL_SCANCODE_TAB]) {
                            gx = 0; gy = 1;
                        }

                        if (KEYS[SDL_SCANCODE_W]) {
                            if (!checkObstacle(obs, gx, gy, 'w'))
                            {
                                gy -= 1;
                                y = toScreen(gy, 'y');
                            }
                            else
                            {
                                gx = start[0];
                                gy = start[1];
                                try_num++;
                            }

                        }

                        else if (KEYS[SDL_SCANCODE_S]) {
                            if (!checkObstacle(obs, gx, gy, 's'))
                            {
                                gy += 1;
                                y = toScreen(gy, 'y');
                            }
                            else
                            {
                                gx = start[0];
                                gy = start[1];
                                try_num++;
                            }
                        }
                        else if (KEYS[SDL_SCANCODE_A]) {
                            if (!checkObstacle(obs, gx, gy, 'a'))
                            {
                                gx -= 1;
                                x = toScreen(gx, 'x');
                            }
                            else
                            {
                                gx = start[0];
                                gy = start[1];
                                try_num++;
                            }
                        }
                        else if (KEYS[SDL_SCANCODE_D]) {
                            if (!checkObstacle(obs, gx, gy, 'd'))
                            {
                                gx += 1;
                                
                                x = toScreen(gx, 'x');
                            }
                            else
                            {
                                gx = start[0];
                                gy = start[1];
                                try_num++;
                            }
                        }
                        if (KEYS[SDL_SCANCODE_F])
                        {
                            gx = end[0];
                            gy = end[1];
                        }
                        system("cls");
                        printf_s(
                            "+--------------------+\n"
                            "| Координаты игрока: |\n"
                            "| X: %2d              |\n"
                            "| Y: %2d              |\n"
                            "| Попытка: %2d        |\n"
                            "+--------------------+\n", gx, gy, try_num);
                        break;


                    }
                    SDL_PumpEvents();
                }

                
                x = toScreen(gx, 'x');
                y = toScreen(gy, 'y');
                
                

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                SDL_RenderClear(renderer);

                // Отрисовка клеток
                SDL_SetRenderDrawColor(renderer, 215, 215, 215, 255); // Светло-серый цвет
                for (int i = -25; i < 25; i++)
                {
                    SDL_RenderDrawLine(renderer, toScreen(i, 'x'), 0, toScreen(i, 'x'), SCREEN_HEIGHT); // Горизонтальные линии клеток
                    SDL_RenderDrawLine(renderer, 0, toScreen(i, 'y'), SCREEN_WIDTH, toScreen(i, 'y')); // Вертикальные линии клеток
                }

                // Отрисовка препятствий
                for (int i = 0; i < 20; i++) 
                {
                    for (int j = 0; j < 20; j++)
                    {
                        if (!labyrinth[i][j])
                        {
                            obs[i * 20 + j].x = i;
                            obs[i * 20 + j].y = j;
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            SDL_Rect rect = { toScreen(obs[i * 20 + j].x, 'x'), toScreen(obs[i * 20 + j].y, 'y'), pixx, pixy };
                            SDL_RenderFillRect(renderer, &rect);
                        }
                    }
                }

                // Старт
                SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255);
                SDL_Rect rect_start = { toScreen(start[0], 'x'), toScreen(start[1], 'y'), pixx, pixy };
                SDL_RenderFillRect(renderer, &rect_start);

                // Финиш
                SDL_SetRenderDrawColor(renderer, 52, 201, 36, 255);
                SDL_Rect rect_finish = { toScreen(end[0], 'x'), toScreen(end[1], 'y'), pixx, pixy };
                SDL_RenderFillRect(renderer, &rect_finish);

                // «Шарик-игрок»
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                draw_circle(
                    renderer, 
                    x + (pixx/2),
                    y + (pixy/2), 
                    radius);


                SDL_RenderPresent(renderer);

            }





            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
    }
    return 1;
}