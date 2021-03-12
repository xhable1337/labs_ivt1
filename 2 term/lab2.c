#include <SDL.h>
#include <stdio.h>
#include <locale.h>

#define SCREEN_WIDTH   640
#define SCREEN_HEIGHT  480

#define Task 3

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    // Обработка ошибки инициализации
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        printf_s("SDL_Error: \n%s", SDL_GetError());
    else
    {
        // Инициализация окна
        SDL_Window* window = NULL;

        // Инициализация поверхности окна (aka surface)
        SDL_Surface* screenSurface = NULL;

        char title[] = u8"Згурский Евгений | Вариант 13";

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        if (window == NULL)
            printf_s("SDL_Error: \n%s", SDL_GetError());
        else
        {
            //Получаем поверхность
            screenSurface = SDL_GetWindowSurface(window);
            #if Task == 2 || Task == 3
                int R = 0;   // Красный цвет [RGB]
                int G = 32;  // Зеленый цвет [RGB]
                int B = 96;  // Синий цвет [RGB]

                // Заполняем ее RGB цветом из соответствующих переменных 
                SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, R, G, B));

                // Обновляем поверхность
                SDL_UpdateWindowSurface(window);

                // Название файла

                #if Task == 2
                    char filename[] = "lab2.2.bmp";
                #endif

                #if Task == 3
                    char filename[] = "lab2.3.bmp";
                #endif

                SDL_Surface* myImage = SDL_LoadBMP(filename);



                if (myImage == NULL) printf_s("[!] Ошибка при загрузке изображения.");
                else
                {    
                    #if Task == 2
                        SDL_SetColorKey(myImage, SDL_TRUE, SDL_MapRGB(myImage->format, 255, 255, 255));
                        SDL_Rect dest;
                        dest.x = 200;
                        dest.y = 100;
                    #endif

                    #if Task == 3
                        SDL_Rect dest;
                        dest.x = 380;
                        dest.y = 0;
                    #endif

                    SDL_BlitSurface(myImage, NULL, screenSurface, &dest);

                    // Обновляем поверхность
                    SDL_UpdateWindowSurface(window);
                }
            #endif
            SDL_Delay(2000);

            #if Task == 2 || Task == 3
                SDL_FreeSurface(myImage);
            #endif
        }
        // Удаляем из памяти окно
        SDL_DestroyWindow(window);
        SDL_FreeSurface(screenSurface);
        SDL_Quit();
    }
    return 0;
}