#pragma once
#include "minestrike.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <wchar.h>

#define RE_DrawTextUnicode(text,x,y,fontSize,width,color,fontFile) RE_DrawTextUNICODE(text,x,y,fontSize,width,color,fontFile)
#define RE_GenTextTextureUnicode(text,fontSize,color,fontFile,width) RE_GenTextTextureUNICODE(text,fontSize,color,fontFile,width)

int RE_InitRenderEngine();
int RE_InitWindow(char* name,int width,int height);
int RE_DestroyRenderEngine();
int RE_Render();
int RE_DrawImage(char* imageName,const SDL_Rect* srcrect,const SDL_Rect* dstrect);
int RE_DrawImageRaw(char* imageName,int x,int y,int w,int h,int u,int v,int uw,int vh);
int RE_DrawTextUTF8(char* text,int x,int y,int fontSize,int width,SDL_Color color,char* fontFile);
SDL_Texture* RE_GenTextTextureUTF8(char* text,char* fontFile,SDL_Color color, int fontSize, int width);
int RE_DrawTextUNICODE(wchar_t* text,int x,int y,int fontSize,int width,SDL_Color color,char* fontFile);
SDL_Texture* RE_GenTextTextureUNICODE(wchar_t* text,char* fontFile,SDL_Color color, int fontSize, int width);