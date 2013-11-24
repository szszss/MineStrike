#include "renderengine.h"
#include "collection.h"
#include <string.h>
#include <wchar.h>
#include "oswork.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
extern unsigned long long tickTime;
static HashTree *availableFont;

int RE_InitRenderEngine()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return ERROR_FAILED_TO_INIT_SDL;
	}
	if (TTF_Init() == -1)
	{
		return ERROR_FAILED_TO_INIT_TTF;
	}
	availableFont = HashTreeCreate();
	return 0;
}

int RE_InitWindow(char* name,int width,int height)
{
	window = SDL_CreateWindow(name, 200, 200, width, height, SDL_WINDOW_SHOWN);
	if(window == null)
	{
		return ERROR_FAILED_TO_CREATE_WINDOW;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == null)
	{
		SDL_DestroyWindow(window);
		return ERROR_FAILED_TO_CREATE_RENDERER;
	}
	return 0;
}

int RE_DestroyRenderEngine()
{
	if(window!=NULL) SDL_DestroyWindow(window);
	if(renderer!=NULL) SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

int RE_Render()
{
	SDL_Color color = {255,255,255};
	SDL_RenderClear(renderer);
	RE_DrawImage("resource/image/logoMineStrike.bmp",NULL,NULL);
	//RE_DrawTextUNICODE(L"ohahahaha This is Power daze aaaaaaaaaaa 这就是爱 不爽不要来",10,10,24,-1,color,"msyh.ttf");
	if(LuaRender(tickTime))
		return -1;
	SDL_RenderPresent(renderer);
	return 0;
}

int RE_DrawImage(char* imageName,const SDL_Rect* srcrect,const SDL_Rect* dstrect )
{
	SDL_Texture *tex = GetTexture(imageName);
	return SDL_RenderCopy(renderer, tex, srcrect, dstrect);
}

int RE_DrawTextUTF8(char* text,int x,int y,int fontSize,int width,SDL_Color color,char* fontFile )
{
	SDL_Texture *texture;
	SDL_Rect dstrect;
	char* fontFilePath = NULL;
	fontFilePath = (char*)HashTreeGet(availableFont,fontFile);
	if(fontFilePath==NULL)
	{
		fontFilePath = OS_GetFontPath(fontFile,NULL);
		HashTreeAdd(availableFont,fontFile,fontFilePath);
	}
	dstrect.x=x;
	dstrect.y=y;
	texture = RE_GenTextTextureUTF8(text,fontFilePath,color,fontSize,width);
	SDL_QueryTexture(texture,NULL,NULL,&dstrect.w,&dstrect.h);
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_DestroyTexture(texture);
	return 0;
}

SDL_Texture* RE_GenTextTextureUTF8(char* text,char* fontFile,SDL_Color color, int fontSize, int width )
{
	SDL_Surface *surf;
	SDL_Texture *texture;
	TTF_Font *font = NULL;
	font = TTF_OpenFont(fontFile, fontSize);
	if (font == NULL)
		GameCrash(0); //TODO:一个正确的错误码
	//surf = TTF_RenderUTF8_Blended(font, text, color);
	surf = TTF_RenderUTF8_Blended_Wrapped(font, text, color,width==-1?WIDTH:(Uint32)width);
	texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}

int RE_DrawTextUNICODE(wchar_t* text,int x,int y,int fontSize,int width,SDL_Color color,char* fontFile )
{
	SDL_Texture *texture;
	SDL_Rect dstrect;
	char* fontFilePath = NULL;
	fontFilePath = (char*)HashTreeGet(availableFont,fontFile);
	if(fontFilePath==NULL)
	{
		fontFilePath = OS_GetFontPath(fontFile,NULL);
		HashTreeAdd(availableFont,fontFile,fontFilePath);
	}
	dstrect.x=x;
	dstrect.y=y;
	texture = RE_GenTextTextureUNICODE(text,fontFilePath,color,fontSize,width);
	SDL_QueryTexture(texture,NULL,NULL,&dstrect.w,&dstrect.h);
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_DestroyTexture(texture);
	return 0;
}

SDL_Texture* RE_GenTextTextureUNICODE(wchar_t* text,char* fontFile,SDL_Color color, int fontSize, int width )
{
	SDL_Surface *surf;
	SDL_Texture *texture;
	TTF_Font *font = NULL;
	font = TTF_OpenFont(fontFile, fontSize);
	if (font == NULL)
		GameCrash(0); //TODO:一个正确的错误码
	//surf = TTF_RenderUNICODE_Blended(font, text, color);
	surf = TTF_RenderUNICODE_Blended_Wrapped(font, text, color,width==-1?WIDTH:(Uint32)width);
	texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}
