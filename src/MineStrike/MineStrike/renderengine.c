#include "renderengine.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int InitRenderEngine()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return ERROR_FAILED_TO_INIT_SDL;
	}
	return 0;
}

int InitWindow(char* name,int width,int height)
{
	window = SDL_CreateWindow(name, 200, 200, width, height, SDL_WINDOW_SHOWN);
	if(window == null)
	{
		return ERROR_FAILED_TO_CREATE_WINDOW;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == null)
	{
		SDL_DestroyWindow(window);
		return ERROR_FAILED_TO_CREATE_RENDERER;
	}
	return 0;
}

int DestroyRenderEngine()
{
	if(window!=NULL) SDL_DestroyWindow(window);
	if(renderer!=NULL) SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}

int Render()
{
	SDL_Texture *tex = LoadTexture("resource/image/logoMineStrike.bmp");
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, tex, NULL, NULL);
	SDL_RenderPresent(renderer);
	return 0;
}
