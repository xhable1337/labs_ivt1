#include <SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH   700
#define SCREEN_HEIGHT  700
#define DELAY_TIME     2000

int SurfaceW = SCREEN_WIDTH / 2;
int SurfaceH = SCREEN_HEIGHT / 2;

// Отрисовывает круг c центром в точке с координатами [x; y] радиусом radius.
void draw_circle(SDL_Renderer* renderer, int x, int y, int radius) {
	int point_x;
	int point_y;
	float pi = M_PI;

	while (radius > 0)
	{
		for (float t = 0; t < 360; t += 0.1)
		{

			point_x = x + radius * cos(t * pi / 180);
			point_y = y + radius * sin(t * pi / 180);
			SDL_RenderDrawPoint(renderer, point_x, point_y);
		}

		radius--;
	}

}

// Отрисовывает прыгающий мяч с центром в [x; y] радиусом radius. 
void move_ball(SDL_Renderer* renderer, int x, int y, int radius) {
	int falling = 1;
	int limit = y;

	while (1)
	{
		SDL_SetRenderDrawColor(renderer, 210, 223, 217, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		draw_circle(renderer, x, y, radius);
		SDL_RenderPresent(renderer);
		//SDL_Delay(10);

		if (y + radius >= SCREEN_HEIGHT)
		{
			falling = !falling;
			y -= 5;
		}

		else if (y - radius <= limit && !falling)
		{
			falling = !falling;
			limit += 50;
			SDL_Delay(75);
		}

		if (falling) y += 5;
		else         y -= 5;

		if (limit >= SCREEN_HEIGHT && y >= SCREEN_HEIGHT - radius)
		{
			SDL_SetRenderDrawColor(renderer, 210, 223, 217, 255);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			draw_circle(renderer, x, SCREEN_HEIGHT - radius, radius);
			break;
		}
	}
}

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

			int x = SurfaceW;
			int y = SurfaceH;
			move_ball(renderer, x, y, 20);
			
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