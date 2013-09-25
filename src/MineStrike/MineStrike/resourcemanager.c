#include "resourcemanager.h"
#include "renderengine.h"
#include "collection.h"

HashTree *textureHT = NULL;
extern SDL_Renderer *renderer;

int InitResourceManager()
{
	textureHT = HashTreeCreate();
	return 0;
}

SDL_Texture* GetTexture( char* imageFile )
{
	SDL_Texture* texture = NULL;
	texture = HashTreeGet(textureHT,imageFile);
	if(texture==NULL)
		return LoadTexture(imageFile);
	return texture;
}

SDL_Texture* LoadTexture( char* imageFile )
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, imageFile);
	if (texture == NULL)
		return NULL; //TODO:A ERROR IMAGE.
	HashTreeAdd(textureHT,imageFile,texture);
	return texture;
}


