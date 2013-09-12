//以下为目标环境操作系统,宏应当由编译器来指定
//#define WINDOWS
//#define UNIX

#pragma once

#ifdef WINDOWS
#include <Windows.h>
#endif

#include "minestrike.h"