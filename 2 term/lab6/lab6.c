#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <time.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT  800
#define DELAY 12

int surH = SCREEN_HEIGHT / 2;
int surW = SCREEN_WIDTH / 2;

const char balloonImage[] = "greenBalloon.bmp"; // Путь к файлу .bmp с текстурой шарика
const char fontName[] = "Circe-ExtraBold.ttf";  // Путь к шрифту формата .ttf

int spawnDelay = 100;                // Задержка спавна шариков.
int ballsInitCount = 10;             // Общее количество шариков, которые одновременно могут быть в игре.
int speed = 6;                       // Скорость передвижения полосы.
SDL_Color textColor = { 202,58,39 }; // Цвет текста.
int prizeTime = 100;                 // Задержка исчезновения текста очков после сбора шарика.
int mouseDelay = 14;                 // Задержка мыши для защиты от спама зажатием кнопки.
int score = 0;                       // Игровой счёт.
int mouseTimer = 0;                  // Таймер мыши.

// ====================================== Прототипы функций =======================================
int random(int, int);
void balloonsInit(struct balloons*, int);
void colorInit(struct color*, int);
void bodyInit(struct body*, int);
void drawText(SDL_Renderer*, SDL_Color, int, int, int, char*);
void drawStrip(SDL_Renderer*, int, int, int);
void drawBalloons(SDL_Renderer*, SDL_Texture*, struct balloons*, int);
void generateBalloons(struct balloons*, int);
void eventUpdate(SDL_Event*, Uint8*, struct color*, struct body*, struct balloons*, int*, int, int, int);
void splashScreen(SDL_Window*);
// ================================================================================================

// Структура шариков.
struct balloons {
    int x;
    int y;
    int w;
    int h;
    SDL_Rect rect;
    int visible;
    int prizeTime;
    int prize;
};

// Структура цвета.
struct color {
    int r;
    int g;
    int b;
    int a;
};

// Структура «тела» полосы.
struct body {
    int size;
    int x;
    int y;
};

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));

    Uint8* KEYS;

    struct color color[2];
    struct body body[2];
    struct balloons balloons[10];
    int init_count = 2;

    colorInit(color, init_count);
    bodyInit(body, init_count);
    balloonsInit(balloons, ballsInitCount);

    int mainColor = 0;
    int mainType = 0;
    int colorStep = 5;
    int x = surW;
    int y = surH;
    char* text[10];


    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf_s("[!] При создании окна SDL произошла ошибка. Текст ошибки:\n%s\n\n", SDL_GetError()); //- проверка на открытие окна;
    }
    else
    {
        SDL_Window* window = NULL; //окно 
        SDL_Event event;
        char* title[100];
        window = SDL_CreateWindow(u8" ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        splashScreen(window, u8"Згурский Евгений    |    Вариант 13 (7)");
        
        if (window == NULL)
        {
            printf_s("[!] При создании окна SDL произошла ошибка. Текст ошибки:\n%s\n\n", SDL_GetError());
        }
        else
        {
            KEYS = (Uint8*)SDL_GetKeyboardState(NULL);
            SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

            SDL_Surface* balloonSurface = SDL_LoadBMP(balloonImage);
            SDL_Texture* balloonTexture;
            SDL_SetColorKey(balloonSurface, SDL_TRUE, SDL_MapRGB(balloonSurface->format, 255, 255, 255));

            TTF_Init(); // Инициализация SDL_ttf.
            

            int alive = 1;
            while (alive) {
                balloonTexture = SDL_CreateTextureFromSurface(renderer, balloonSurface);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                SDL_RenderClear(renderer);

                eventUpdate(&event, KEYS, color, body, balloons, &alive, speed, colorStep, ballsInitCount);

                SDL_SetRenderDrawColor(renderer, color[0].r, color[0].g, color[0].b, color[0].a);
                drawStrip(renderer, body[0].x, body[0].y, body[0].size);

                generateBalloons(balloons, ballsInitCount);
                drawBalloons(renderer, balloonTexture, balloons, ballsInitCount);

                snprintf(text, 10, "%d", score);
                drawText(renderer, textColor, surW, 0, 100, text);

                SDL_Delay(DELAY);
                snprintf(title, 100, u8"Згурский Евгений    |    Вариант 13 (7)    |    Очки: %d", score);
                SDL_SetWindowTitle(window, title);
                SDL_RenderPresent(renderer);

                SDL_DestroyTexture(balloonTexture);
            }

            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            TTF_Quit();
            SDL_Quit();
        }
    }
    return 1;
}

// Возвращает псевдослучайное число от a до b.
int random(int a, int b)
{
    if (a > 0) return a + rand() % (b - a);
    else return a + rand() % (abs(a) + b);
}

// Инициализирует шарики в количестве count.
void balloonsInit(struct balloons* b, int count) {
    for (int i = 0; i < count; i++) {
        b[i].w = 55;
        b[i].h = 70;
        b[i].rect.x = surH;
        b[i].rect.y = surW;
        b[i].rect.w = b[i].w;
        b[i].rect.h = b[i].h;
        b[i].x = b[i].rect.x;
        b[i].y = b[i].rect.y;
        b[i].visible = 0;
        b[i].prize = random(1, 10);
    }
}

// Инициализирует цвет полосы.
void colorInit(struct color* C, int count) {
    for (int i = 0; i < count; i++) {
        C[i].r = 150;
        C[i].g = 150;
        C[i].b = 150;
        C[i].a = 255;
    }
}

// Инициализирует «тело» полосы.
void bodyInit(struct body* B, int count) {
    for (int i = 0; i < count; i++) {
        B[i].size = 90;
        B[i].x = surH;
        B[i].y = SCREEN_HEIGHT - 15;
    }
}

// Отрисовывает текст text размером size цветом color в координатах [x; y].
void drawText(SDL_Renderer* renderer, SDL_Color color, int x, int y, int size, char* text) {
    TTF_Font* font = TTF_OpenFont(fontName, size);

    SDL_Surface* textSurface = NULL;
    textSurface = TTF_RenderUTF8_Blended(font, text, color);

    SDL_Rect rect = { x - size / 2 * strlen(text) / 2, y, (size / 2) * strlen(text), size };
    SDL_Renderer* Texture_font = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, Texture_font, NULL, &rect);

    SDL_DestroyTexture(Texture_font);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}

// Рисует полосу на координатах [x; y] размером size.
void drawStrip(SDL_Renderer* renderer, int x, int y, int size) {
    SDL_Rect rect = { x - size, y, 2 * size, 10 };
    SDL_RenderFillRect(renderer, &rect);
}

// Функция обработки нажатий.
void eventUpdate(SDL_Event* event, Uint8* KEYS, struct color* color, struct body* body, struct balloons* balloons, int* alive, int speed, int colorStep, int balloons_init_count) {

    int mainColor = 0;
    int mainType = 0;
    int curx, cury;

    while (SDL_PollEvent(event)) {
        SDL_PumpEvents();
        switch (event->type) {
        case SDL_QUIT: {
            *alive = 0;
            break;
        }
        }


        SDL_PumpEvents();
    }

    if (KEYS[SDL_SCANCODE_A]) {
        if (body[mainType].x - speed > 0 + body[mainType].size) {
            body[mainType].x -= speed;
        }

    }
    if (KEYS[SDL_SCANCODE_D]) {
        if (body[mainType].x + speed < SCREEN_WIDTH - body[mainType].size) {
            body[mainType].x += speed;
        }

    }
    if (KEYS[SDL_SCANCODE_R]) {
        color[mainColor].r += colorStep;
        if (color[mainColor].r > 255)color[mainColor].r = 255;
    }
    if (KEYS[SDL_SCANCODE_G]) {
        color[mainColor].g += colorStep;
        if (color[mainColor].g > 255)color[mainColor].g = 255;
    }
    if (KEYS[SDL_SCANCODE_B]) {
        color[mainColor].b += colorStep;
        if (color[mainColor].b > 255)color[mainColor].b = 255;
    }
    if (KEYS[SDL_SCANCODE_Z]) {
        color[mainColor].r = 0;
        color[mainColor].g = 0;
        color[mainColor].b = 0;
    }


    mouseTimer++;
    if (SDL_GetMouseState(&curx, &cury) & SDL_BUTTON(SDL_BUTTON_LEFT)) {

        if (mouseTimer > mouseDelay) {

            SDL_Rect mouse = { curx , cury, 10, 10 };

            for (int i = 0; i < balloons_init_count; i++) {
                if (balloons[i].visible) {
                    if (SDL_HasIntersection(&mouse, &balloons[i].rect)) {
                        balloons[i].visible = 0;
                        balloons[i].prizeTime = prizeTime;
                    }
                }
            }
            mouseTimer = 0;
        }


    }

    SDL_Rect cube = { body[mainType].x - body[mainType].size, body[mainType].y, body[mainType].size * 2, 10 };

    for (int i = 0; i < balloons_init_count; i++) {
        if (balloons[i].visible) {
            if (SDL_HasIntersection(&cube, &balloons[i].rect)) {
                score += balloons[i].prize;
                balloons[i].visible = 0;
                balloons[i].prizeTime = prizeTime;
            }
        }
    }



}

// Отрисовывает шарики и количество очков, которое игрок получил за сбор этого шарика.
void drawBalloons(SDL_Renderer* renderer, SDL_Texture* texture, struct balloons* balloons, int balls_init_count) {
    char* text[10];
    for (int i = 0; i < balls_init_count; i++) {
        
        if (balloons[i].visible) {
            SDL_RenderCopy(renderer, texture, NULL, &balloons[i].rect);
        }

        if (balloons[i].prizeTime > 0) {
            snprintf(text, 10, "%d", balloons[i].prize);
            drawText(renderer, textColor, balloons[i].x, balloons[i].y, 50, text);
            balloons[i].prizeTime--;
        }
    }
}

// Создаёт шарики с задержкой и перемещает их сверху вниз.
void generateBalloons(struct balloons* balloons, int balls_init_count) {
    for (int i = 0; i < balls_init_count; i++) {
        // Падение шариков и проверка на выход за пределы экрана.
        if (balloons[i].visible)
        {
            balloons[i].rect.y++;
            if (balloons[i].rect.y >= SCREEN_HEIGHT)
            {
                balloons[i].rect.y = 0;
                balloons[i].rect.x = rand() % SCREEN_WIDTH;
            }
        }

        // Спавн шариков с задержкой.
        if (spawnDelay == 0)
        {
            if (!balloons[i].visible) {
                balloons[i].rect.x = rand() % SCREEN_WIDTH;
                balloons[i].rect.y = rand() % surH;
                balloons[i].x = balloons[i].rect.x;
                balloons[i].y = SCREEN_HEIGHT - 100;
                balloons[i].visible = 1;
                balloons[i].prizeTime = 0;
                spawnDelay = 100;
            }
        }
        
    }
    spawnDelay--;

}

// Побуквенное появление текста в заголовке окна.
void splashScreen(SDL_Window* window, char* text) {
    int len = strlen(text);
    char* title[100];
    for (int i = 1; i <= len + 10; i+=2)
    {
        snprintf(title, i, text);
        SDL_SetWindowTitle(window, title); SDL_Delay(70);
    }
    SDL_Delay(900);
}