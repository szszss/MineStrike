#include "resourcemanager.h"
#include "renderengine.h"
#include "collection.h"

HashTree *textureHT = NULL;
extern SDL_Renderer *renderer;

int RM_InitResourceManager()
{
	textureHT = HashTreeCreate();
	return 0;
}

SDL_Texture* RE_GetTexture( char* imageFile )
{
	SDL_Texture* texture = NULL;
	texture = (SDL_Texture*)HashTreeGet(textureHT,imageFile);
	if(texture==NULL)
		return RE__LoadTexture(imageFile);
	return texture;
}

SDL_Texture* RE__LoadTexture( char* imageFile )
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, imageFile);
	if (texture == NULL)
		return NULL; //TODO:A ERROR IMAGE.
	HashTreeAdd(textureHT,imageFile,texture);
	return texture;
}


