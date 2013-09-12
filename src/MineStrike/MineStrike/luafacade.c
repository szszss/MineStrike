#include "luafacade.h"

int InitLua(lua_State *initedLua)
{
	initedLua = luaL_newstate();
	if(initedLua == NULL)
	{
		return 1;
	}
	luaL_openlibs(initedLua);
	return 0;
}