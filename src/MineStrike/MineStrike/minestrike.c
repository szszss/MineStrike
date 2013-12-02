#include "minestrike.h"

char *gamePath;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern lua_State *luaState;
unsigned long long tickTime = 0;

int main(int argc, char *argv[])
{
	int stats=0;
	if ((stats=RE_InitRenderEngine())!=0)
	{
		return GameError(stats);
	}
	if ((stats=RM_InitResourceManager())!=0)
	{
		return GameError(stats);
	}
	if ((stats=RE_InitWindow("Hello World!",WIDTH, HEIGHT))!=0)
	{
		return GameError(stats);
	}
	if (InitLua()!=0)
	{
		return GameError(ERROR_FAILED_TO_INIT_LUA);
	}
	//printf("System ONLINE! Have a good lu!\n");
	GameMainLoop();
	return GameQuit();
}

int GameMainLoop()
{
	int stats = 0;
	while(1)
	{
		if(Update()!=0 || RE_Render()!=0)
			break;
		SDL_Delay(FRAME);
		tickTime++;
	}
	return 0;
}

int HandleEvent(SDL_Event sdlEvent)
{
	switch (sdlEvent.type)
	{
		case SDL_KEYDOWN:
			LuaInputKeyDown(sdlEvent.key.keysym.sym);
		break;
		case SDL_TEXTINPUT:
			LuaInputText(sdlEvent.text.text);
			break;
		case SDL_TEXTEDITING:

			break;
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
	if(LuaTick(tickTime))
		return -1;
	return 0;
}

int GameQuit()
{
	RE_DestroyRenderEngine();
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