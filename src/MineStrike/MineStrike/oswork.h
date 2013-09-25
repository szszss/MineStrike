//以下为目标环境操作系统,应当由编译器来声明
//#define WINDOWS
//#define UNIX
/*
别TM用这个类!!还没有实现呢!
*/
#pragma once

#ifdef WINDOWS
#include <Windows.h>
#include <process.h>
#endif
#ifdef UNIX
#include <pthread.h>
#endif

#include "minestrike.h"

#ifndef BOOL
#define BOOL int
#define FALSE 0
#define TRUE 1
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