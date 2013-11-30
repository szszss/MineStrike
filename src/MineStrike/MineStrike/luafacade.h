#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

int InitLua();
int LuaTick(unsigned long long tick);
int LuaRender(unsigned long long tick);
int LuaInputText(char* text);
int LuaInputKeyDown(const int key);