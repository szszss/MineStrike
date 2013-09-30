#pragma once
#include "minestrike.h"
#include "SDL.h"
#include "SDL_image.h"

int RE_InitRenderEngine();
int RE_InitWindow(char* name,int width,int height);
int RE_DestroyRenderEngine();
int RE_Render();
int RE_DrawImage(char* imageName,const SDL_Rect* srcrect,const SDL_Rect* dstrect);