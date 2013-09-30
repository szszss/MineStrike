#include "renderengine.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int RE_InitRenderEngine()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return ERROR_FAILED_TO_INIT_SDL;
	}
	return 0;
}

int RE_InitWindow(char* name,int width,int height)
{
	window = SDL_CreateWindow(name, 200, 200, width, height, SDL_WINDOW_SHOWN);
	if(window == null)
	{
		return ERROR_FAILED_TO_CREATE_WINDOW;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == null)
	{
		SDL_DestroyWindow(window);
		return ERROR_FAILED_TO_CREATE_RENDERER;
	}
	return 0;
}

int RE_DestroyRenderEngine()
{
	if(window!=NULL) SDL_DestroyWindow(window);
	if(renderer!=NULL) SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}

int RE_Render()
{
	SDL_RenderClear(renderer);
	RE_DrawImage("resource/image/logoMineStrike.bmp",NULL,NULL);
	SDL_RenderPresent(renderer);
	return 0;
}

int RE_DrawImage(char* imageName,const SDL_Rect* srcrect,const SDL_Rect* dstrect )
{
	SDL_Texture *tex = RE_GetTexture(imageName);
	SDL_RenderCopy(renderer, tex, NULL, NULL);
	return 0;
}
