#include "oswork.h"
#include "util.h"

#ifdef WINDOWS
/*
ThreadProxy* ThreadCreate( unsigned int pid,char* name,void (*func)(void* param))
{
	ThreadProxy *thread = (ThreadProxy*)malloc_s(sizeof(ThreadProxy));
	thread->pid = pid;
	thread->name = name;
	thread->result = 0;
	thread->thread = NULL;
	thread->thread = &_beginthreadex(NULL,0,func,NULL,CREATE_SUSPENDED,&thread->result);
	return thread;
}

BOOL* ThreadStart( ThreadProxy* thread )
{
	if(thread->thread==NULL)
		return FALSE;
	ResumeThread(*(thread->thread));
	return TRUE;
}

BOOL* ThreadStop( ThreadProxy* thread )
{
	if(thread->thread==NULL)
		return FALSE;
	CloseHandle(*(thread->thread));
	return TRUE;
}
*/
#endif