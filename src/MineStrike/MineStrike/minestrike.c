#include "minestrike.h"

char *gamePath;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
lua_State *luaState = NULL;

int main(int argc, char *argv[])
{
	SDL_Surface *bmp = null;
	SDL_Texture *tex = null;
	if (InitLua(luaState) != 0)
	{
		return GameError(ERROR_FAILED_TO_INIT_LUA);
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return GameError(ERROR_FAILED_TO_INIT_SDL);
	}
	window = SDL_CreateWindow("Hello World!", 200, 200, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if(window == null)
	{
		return GameError(ERROR_FAILED_TO_CREATE_WINDOW);
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == null)
	{
		SDL_DestroyWindow(window);
		return GameError(ERROR_FAILED_TO_CREATE_RENDERER);
	}
	bmp = SDL_LoadBMP("resource/image/logoMineStrike.bmp");
	if (bmp == null)
	{
        return GameError(1);    
	}
	tex = SDL_CreateTextureFromSurface(renderer, bmp);
	SDL_FreeSurface(bmp);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, tex, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
	SDL_DestroyTexture(tex);
	return GameQuit();
}

int GameQuit()
{
	if(window!=NULL) SDL_DestroyWindow(window);
	if(renderer!=NULL) SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}

int GameError(int errorCode)
{
	const char *cause = SDL_GetError();
	printf(cause);
	return errorCode;
}

void GameCrash( int errorCode )
{
}



