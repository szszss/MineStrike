#pragma once
#include "minestrike.h"
#include "SDL.h"
#include "SDL_image.h"

int InitRenderEngine();
int InitWindow(char* name,int width,int height);
int DestroyRenderEngine();
int Render();