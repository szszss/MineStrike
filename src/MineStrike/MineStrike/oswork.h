//����ΪĿ�껷������ϵͳ,Ӧ���ɱ�����������
//#define WINDOWS
//#define UNIX
/*
��TM�������!!��û��ʵ����!
*/
//13-11-24:ʵ����Windows�µ�����
#pragma once

#ifdef WINDOWS
#include <Windows.h>
#include <process.h>
#endif
#ifdef UNIX
#include <pthread.h>
#endif

#include "minestrike.h"

#ifndef _WINDEF_
#ifndef BOOL
#define BOOL int
#define FALSE 0
#define TRUE 1
#endif
#endif

typedef struct  
{
	unsigned int pid;
	char* name;
	void* thread;
	unsigned int result;
	BOOL isStop;
} ThreadProxy;

ThreadProxy* ThreadCreate(unsigned int pid,char* name,void (*func)(void* param));
BOOL* ThreadStart(ThreadProxy* thread);
BOOL* ThreadStop(ThreadProxy* thread);

char* OS_GetFontPath(char* fontName,char* backupFontName);
BOOL OS_PathExist(char* path);