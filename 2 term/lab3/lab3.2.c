#include <SDL.h>
#include <stdio.h>
#define SCREEN_WIDTH  700
#define SCREEN_HEIGHT  700
#define DELAY_TIME 9000

/* Лабораторная работа 3.2.
13. Нарисовать ноутбук.
*/

int SurfaceW = SCREEN_WIDTH / 2;
int SurfaceH = SCREEN_HEIGHT / 2;

void draw_laptop_part(SDL_Renderer* renderer, char part[]);

int main(int argc, char* argv[])
{
	

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf_s("[!] При создании окна SDL произошла ошибка. Текст ошибки:\n%s\n\n", SDL_GetError());
	}
	else
	{
		//окно
		SDL_Window* window = NULL;
		//Поверхность окна
		SDL_Surface* screenSurface = NULL;
		window = SDL_CreateWindow(u8"Згурский Евгений | Вариант 13", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf_s("[!] При создании окна SDL произошла ошибка. Текст ошибки:\n%s\n\n", SDL_GetError());
		}
		else
		{
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

			// Фон
			SDL_SetRenderDrawColor(renderer, 210, 223, 217, 255);
			SDL_RenderClear(renderer);

			draw_laptop_part(renderer, "frame");
			draw_laptop_part(renderer, "display");
			draw_laptop_part(renderer, "case");
			draw_laptop_part(renderer, "hinges");
			draw_laptop_part(renderer, "keyboard");
			draw_laptop_part(renderer, "touchpad");

			SDL_RenderPresent(renderer);
			SDL_Delay(DELAY_TIME);
		}
		//И удаляем из памяти окно

		SDL_DestroyWindow(window);
		SDL_FreeSurface(screenSurface);
		SDL_Quit();
	}
	return 1;
}

void draw_laptop_part(SDL_Renderer* renderer, char part[]) {
	if (part == "frame") {
		// Дисплейная рамка
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		SDL_Rect rect_2 = { SurfaceW - 155, SurfaceH - 190, 310, 190 };
		SDL_RenderDrawRect(renderer, &rect_2);
		SDL_SetRenderDrawColor(renderer, 155, 155, 150, 255);
		SDL_RenderFillRect(renderer, &rect_2);
	}
	else if (part == "display") {
		// Дисплей
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		SDL_Rect rect_1 = { SurfaceW - 150, SurfaceH - 185, 300, 180 };
		SDL_RenderDrawRect(renderer, &rect_1);
		SDL_SetRenderDrawColor(renderer, 180, 180, 200, 255);
		SDL_RenderFillRect(renderer, &rect_1);
	}
	else if (part == "case") {
		// Корпус
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		SDL_Rect rect_3 = { SurfaceW - 155, SurfaceH + 8, 310, 156 };
		SDL_RenderDrawRect(renderer, &rect_3);
		SDL_SetRenderDrawColor(renderer, 155, 155, 150, 255);
		SDL_RenderFillRect(renderer, &rect_3);
	}
	else if (part == "hinges") {
		// Петли крышки

		// Левая петля крышки
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		SDL_Rect rect_4 = { SurfaceW - 146, SurfaceH - 3, 14, 14 };
		SDL_RenderDrawRect(renderer, &rect_4);
		SDL_SetRenderDrawColor(renderer, 155, 155, 150, 255);
		SDL_RenderFillRect(renderer, &rect_4);

		// Правая петля крышки
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		SDL_Rect rect_5 = { SurfaceW + 132, SurfaceH - 3, 14, 14 };
		SDL_RenderDrawRect(renderer, &rect_5);
		SDL_SetRenderDrawColor(renderer, 155, 155, 150, 255);
		SDL_RenderFillRect(renderer, &rect_5);
	}
	else if (part == "keyboard") {
		// Клавиатура
		int size = 15;
		int x = SurfaceW - 120;
		int y = SurfaceH + 32;
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				SDL_Rect rect = { x + i * size, y + j * size, size + 1, size + 1 };


				if (i % 2 == 0 && j % 2 != 0 || i % 2 != 0 && j % 2 == 0) {
				}
				else {
					SDL_SetRenderDrawColor(renderer, 130, 130, 130, 255);
					SDL_RenderFillRect(renderer, &rect);
				}
			}
		}
	}
	else if (part == "touchpad") {
		// Тачпад
		SDL_SetRenderDrawColor(renderer, 130, 130, 130, 255);
		SDL_Rect rect_6 = { SurfaceW - 38, SurfaceH + 105, 76, 44 };
		SDL_RenderDrawRect(renderer, &rect_6);
		SDL_RenderFillRect(renderer, &rect_6);
	}
}