#include "luafacade.h"
#include "renderengine.h"
#include <stdlib.h>
#include "util.h"

lua_State *luaState = NULL;

void* Lua_malloc(void *ud,void *ptr,size_t osize,size_t nsize);
int Lua_registerFunction();
int CDrawText(lua_State *L);

int InitLua()
{
	char* err;
	luaState = lua_newstate(Lua_malloc,NULL);
	if(luaState == NULL) //初始化LUA失败
	{
		return 1;
	}
	luaL_openlibs(luaState);
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
	if(Lua_registerFunction(luaState))
	{
		return 1;
	}
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

int Lua_registerFunction(lua_State *L)
{
	lua_pushcfunction(L,CDrawText);
	lua_setglobal(L,"CDrawText");
	return 0;
}

int CDrawText( lua_State *L )
{
	char* text = (char*)lua_tostring(L,1);
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
