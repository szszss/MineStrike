#include "minestrike.h"

char *gamePath;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
lua_State *luaState = NULL;

int main(int argc, char *argv[])
{
	int stats=0;
	if (InitLua(luaState) != 0)
	{
		return GameError(ERROR_FAILED_TO_INIT_LUA);
	}
	if ((stats=InitRenderEngine())!=0)
	{
		return GameError(stats);
	}
	if ((stats=InitResourceManager())!=0)
	{
		return GameError(stats);
	}
	if ((stats=InitWindow("Hello World!",WIDTH, HEIGHT))!=0)
	{
		return GameError(stats);
	}
	GameMainLoop();
	return GameQuit();
}

int GameMainLoop()
{
	int stats = 0;
	while(1)
	{
		if(Update()!=0 || Render()!=0)
			break;
		SDL_Delay(FRAME);
	}
	return 0;
}

int HandleEvent(SDL_Event sdlEvent)
{
	switch (sdlEvent.type)
	{
		case SDL_QUIT:
			return -1;
			break;
	}
	return 0;
}

int Update()
{
	SDL_Event sdlEvent;
	while(SDL_PollEvent(&sdlEvent))
	{
		if(HandleEvent(sdlEvent)!=0)
		{
			return -1;
		}
	}
	return 0;
}

int GameQuit()
{
	DestroyRenderEngine();
	return 0;
}

int GameError(int errorCode)
{
	//const char *cause = SDL_GetError();
	//printf(cause);
	return errorCode;
}

void GameCrash( int errorCode )
{
	GameError(errorCode);
	exit(errorCode);
}



