#include "luafacade.h"
#include "renderengine.h"
#include <stdlib.h>
#include "util.h"

lua_State *luaState = NULL;

void* Lua_malloc(void *ud,void *ptr,size_t osize,size_t nsize);
int Lua_registerFunctions();
int Lua_register(lua_CFunction function,char* name);
int CDrawText(lua_State *L);
int CDrawImage(lua_State *L);
int CEnableTextInput(lua_State *L);
int CDisableTextInput(lua_State *L);
int CWindowSetTitle(lua_State *L);

int InitLua()
{
	char* err;
	luaState = lua_newstate(Lua_malloc,NULL);
	if(luaState == NULL) //初始化LUA失败
	{
		return 1;
	}
	luaL_openlibs(luaState);
	if(Lua_registerFunctions())
	{
		return 1;
	}
	if(luaL_loadfile(luaState,"data/lua/boot.lua") || lua_pcall(luaState,0,1,0)) //未能再入boot
	{
		return 1;
	}
	lua_getglobal(luaState,"main");
	lua_pcall(luaState,0,1,0);
	if((int)lua_tonumber(luaState,-1)!=0) //boot的main没有返回0
	{
		return 1;
	}
	lua_pop(luaState,-1);
	return 0;
}

void* Lua_malloc(void *ud,void *ptr,size_t osize,size_t nsize)
{
	if(nsize==0){
		if(ptr!=NULL)
			free(ptr);
		return NULL;
	}
	else{
		if(ptr==NULL)
			return malloc_s(nsize);
		else return realloc_s(ptr,nsize);
	}
}

int LuaTick(unsigned long long tick)
{
	char* error = NULL;
	lua_getglobal(luaState,"tick");
	lua_pushnumber(luaState,(double)tick);
	if(lua_pcall(luaState,1,1,0) || !lua_isnumber(luaState,-1) || lua_tonumber(luaState,-1))
	{
		error = (char*)lua_tostring(luaState,-1);
		return 1;
	}
	lua_pop(luaState,-1);
	return 0;
}

int LuaRender(unsigned long long tick)
{
	char* error = NULL;
	lua_getglobal(luaState,"render");
	lua_pushnumber(luaState,(double)tick);
	if(lua_pcall(luaState,1,1,0) || !lua_isnumber(luaState,-1) || lua_tonumber(luaState,-1))
	{
		error = (char*)lua_tostring(luaState,-1);
		return 1;
	}
	lua_pop(luaState,-1);
	return 0;
}


int LuaInputText( char* text )
{
	char* error = NULL;
	lua_getglobal(luaState,"Input");
	lua_getfield(luaState,-1,"inputText");
	lua_pushstring(luaState,text);
	if(lua_pcall(luaState,1,1,0) || !lua_isnumber(luaState,-1) || lua_tonumber(luaState,-1))
	{
		error = (char*)lua_tostring(luaState,-1);
		return 1;
	}
	lua_pop(luaState,-1);
	return 0;
}

int LuaInputKeyDown(const int key)
{
	char* error = NULL;
	lua_getglobal(luaState,"Input");
	lua_getfield(luaState,-1,"inputKeyDown");
	lua_pushnumber(luaState,key);
	if(lua_pcall(luaState,1,1,0) || !lua_isnumber(luaState,-1) || lua_tonumber(luaState,-1))
	{
		error = (char*)lua_tostring(luaState,-1);
		return 1;
	}
	lua_pop(luaState,-1);
	return 0;
}

int Lua_register(lua_CFunction function,char* name)
{
	lua_pushcfunction(luaState,function);
	lua_setglobal(luaState,name);
	return 0;
}

int Lua_registerFunctions()
{
	Lua_register(CDrawText,"CDrawText");
	Lua_register(CDrawImage,"CDrawImage");
	Lua_register(CWindowSetTitle,"CWindowSetTitle");
	Lua_register(CEnableTextInput,"CEnableTextInput");
	Lua_register(CDisableTextInput,"CDisableTextInput");
	return 0;
}

int CDrawText( lua_State *L )
{
	char *text = (char*)lua_tostring(L,1);
	int x = (int)lua_tonumber(L,2);
	int y = (int)lua_tonumber(L,3);
	int size = (int)lua_tonumber(L,4);
	int width = (int)lua_tonumber(L,5);
	int r = (int)lua_tonumber(L,6);
	int g = (int)lua_tonumber(L,7);
	int b = (int)lua_tonumber(L,8);
	SDL_Color color = {r,g,b};
	char* font = (char*)lua_tostring(L,9);
	int result = RE_DrawTextUTF8(text,x,y,size,width,color,font);
	lua_pushboolean(L,result);
	return 1;
}

int CDrawImage(lua_State *L)
{
	char *imageName = (char*)lua_tostring(L,1);
	int x = (int)lua_tonumber(L,2);
	int y = (int)lua_tonumber(L,3);
	int w = (int)lua_tonumber(L,4);
	int h = (int)lua_tonumber(L,5);
	int u = (int)lua_tonumber(L,6);
	int v = (int)lua_tonumber(L,7);
	int uw = (int)lua_tonumber(L,8);
	int vh = (int)lua_tonumber(L,9);
	int result;
	result = RE_DrawImageRaw(imageName,x,y,w,h,u,v,uw,vh);
	lua_pushboolean(L,result);
	return 1;
}

int CWindowSetTitle( lua_State *L )
{
	char* title = (char*)lua_tostring(L,1);
	OS_SetWindowTitle(title);
	//GameSetTitle("卧槽!");
	return 0;
}

int CEnableTextInput(lua_State *L)
{
	SDL_StartTextInput();
	return 0;
}

int CDisableTextInput(lua_State *L)
{
	SDL_StopTextInput();
	return 0;
}
