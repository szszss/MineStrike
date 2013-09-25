/*
 * minestrike.h
 *
 *  Created on: 2013-9-11
 *      Author: szszss
 */

#pragma once

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include "renderengine.h"
#include "resourcemanager.h"
#include "luafacade.h"
#include "oswork.h"
#include "util.h"

#ifndef null
#define null 0
#endif

#define ERROR_FAILED_TO_INIT_SDL 1         //无法初始化SDL
#define ERROR_FAILED_TO_CREATE_WINDOW 2    //无法创建窗口
#define ERROR_FAILED_TO_CREATE_RENDERER 3  //无法创建渲染器
#define ERROR_FAILED_TO_INIT_LUA 10        //初始化Lua引擎发生错误
#define ERROR_OUT_OF_MEMORY 250            //内存不足
#define ERROR_UNKNOWN_ERROR 255            //未知错误
#define WIDTH 600
#define HEIGHT 480
#define FRAME 32

static int GameMainLoop();
static int Update();
int GameQuit();
int GameError(int errorCode);
void GameCrash(int errorCode);

/*
  　　　　　　　　　　         _,○､
　　　　　　　○､　　　　 ,　'´　〈ﾍ.）
　　　　　　／,ﾊ_）　　／　　　　｀メ.
　　　　 ／　　└-‐'´　　　　　 [__,ﾊ
　　 　./＼＿i＞-‐‐ｧ'´￣｀Yヽ､_　 |
　　　/_ｒ'"´Y_＞-‐'"´￣￣｀ヽ./｀ヽ!
　　ｒ'´7-‐'"´ 　 i　　　ﾊ_＿i　 ＼__,ﾊ
　 〈Y´　　 i　__ ,ﾊ 　 / _」__,ﾊ　　| ｀ヽ〉
　　`!　/　ﾊ´ _」_ |／ '´i,ﾉ ｀ﾘ　 /　　 !／!
　　 |　! 　 |ｨ´i,ﾉ !　 　　'､__ﾝ|／ 　　/　/ 　ﾄ 、
　　 ',　＼,ﾊ.` '､.ﾉ　 .　　　 ⊂⊃ .／､_,.!　 /　,ﾊ　　 ,|
　　　＼ | ヽ!⊃　 　 -‐ '　 ,.ｲ　 〈 　 　|／レへ,! 　/ !
　　　 　｀ヽ,|｀＞ｧ‐---rｧ' /`ﾄ､へ） .／ 　 　 　 !／　  |
　　　　　　 ﾚへ!ノレアiレ'::::/　ﾒ、 /　　 　　 　 |､/ヽ  |
　　　　 ＿_ ｀＼ 　_/ ,|.!:::::ｲ|＿　∨　　 　 　　,ﾊ　　 |
　　　　 ＼/￣ /´￣`ｧt‐ｧ'´　 ｀　i 　　　 　　/　　　/
　　　　　　｀ヽ〈　　　 | |　|　　 　 人/ 　 　／　　 ／
　　　　 ＜⌒７`ーｧ'i |￣｀i-r‐＜ヽ.__,,..イ‐--‐＜
　　　　　　＼! .／　//::::::::| |　　　,ハ　 　　 く＼
　　　　　　　rく/　く〈:ﾛ::ﾛ::|/　 　　　 ト､　　 ＜｀＞
　　　　　　 /＼ﾝ､_ `ー-‐'　　/ 　　 ﾉ'〉＞､,_＿,.＞'´
　　　　　∠..＿,ﾍ./こ＞-＜こン‐ｧ´!ノ
　　　　　　　　　 ﾄ-‐/´￣｀'トｰ‐ｧ'´
　　　　　　　 　　!__/　　 　 ﾄ-‐/
　　　　　　　　　　　　　　　 !__/

                    Grace and Mercy
 */