#include "minestrike.h"
#include "SDL.h"
#include "SDL_image.h"

int RM_InitResourceManager();
SDL_Texture* RM_GetTexture(char* imageFile);
SDL_Texture* RM_LoadTexture(char* imageFile);