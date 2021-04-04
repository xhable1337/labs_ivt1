#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT  600
#define DELAY_TIME 9000

int SurfaceW = SCREEN_WIDTH / 2;
int SurfaceH = SCREEN_HEIGHT;

void draw_circle(SDL_Renderer* render, int x, int y, int radius);
void draw_hands(SDL_Renderer* render, int x, int y, int length, int left_degree, int right_degree);
void draw_snowman(SDL_Renderer* renderer, int radius_small, int radius_medium, int radius_big);

int main(int argc, char* argv[])
{
	int radius_small = 25;
	int radius_medium = 50;
	int radius_big = 100;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf_s(" SDL_Error: \n%s\n\n", SDL_GetError());
	}
	else
	{
		// Окно
		SDL_Window* window = NULL;

		// Поверхность окна
		SDL_Surface* screenSurface = NULL;
		window = SDL_CreateWindow(u8"Згурский Евгений | Вариант 13", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf_s(" SDL_Error: \n%s\n\n", SDL_GetError());
		}
		else
		{
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

			// Фон
			SDL_SetRenderDrawColor(renderer, 210, 223, 217, 255);
			SDL_RenderClear(renderer);

			draw_snowman(renderer, radius_small, radius_medium, radius_big); // Отрисовка снеговика

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

// Отрисовывает круг c центром в точке с координатами [x; y] радиусом radius.
void draw_circle(SDL_Renderer* render, int x, int y, int radius) {
	int point_x;
	int point_y;
	float pi = M_PI;

	while (radius > 0)
	{
		for (float t = 0; t < 360; t += 0.1)
		{

			point_x = x + radius * cos(t * pi / 180);
			point_y = y + radius * sin(t * pi / 180);
			SDL_RenderDrawPoint(render, point_x, point_y);
		}

		radius--;
	}

}

// Рисует руки снеговика в координатах [x; y] длиной length под углами left_degree и right_degree для левой и правой руки соответственно.
void draw_hands(SDL_Renderer* render, int x, int y, int length, int left_degree, int right_degree) {
	int point_x;
	int point_y;
	float pi = M_PI;

	point_x = x + 2.0 * length * cos(left_degree * pi / 180);
	point_y = y + 2.0 * length * sin(left_degree * pi / 180);
	SDL_RenderDrawLine(render, x - length, y, point_x, point_y);
	SDL_RenderDrawLine(render, x - length - 1, y, point_x + 1, point_y + 1);

	point_x = x + 2.0 * length * cos(right_degree * pi / 180);
	point_y = y + 2.0 * length * sin(right_degree * pi / 180);
	SDL_RenderDrawLine(render, x + length, y, point_x, point_y);
	SDL_RenderDrawLine(render, x + length + 1, y, point_x - 1, point_y - 1);
}

// Рисует снеговика с из трёх кругов радиусами radius_small, radium _medium и radius_big.
void draw_snowman(SDL_Renderer* renderer, int radius_small, int radius_medium, int radius_big) {
	//
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	draw_circle(renderer, SurfaceW, SurfaceH / 2.5, radius_small);
	//
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
	draw_circle(renderer, SurfaceW, SurfaceH / 2, radius_medium);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	draw_hands(renderer, SurfaceW, SurfaceH / 2, radius_medium, 170, 370);
	//
	SDL_SetRenderDrawColor(renderer, 235, 235, 235, 255);
	draw_circle(renderer, SurfaceW, SurfaceH / 1.5, radius_big);

	//
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
	SDL_Rect rect_1 = { SurfaceW - 20, (SurfaceH) / 2 - 106, 40, 30 };
	SDL_RenderFillRect(renderer, &rect_1);

	SDL_Rect rect_2 = { SurfaceW - 35, (SurfaceH) / 2 - 78, 70, 8 };
	SDL_RenderFillRect(renderer, &rect_2);

}