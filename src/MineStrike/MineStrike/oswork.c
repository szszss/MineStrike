#include "oswork.h"
#include <string.h>
#include <stdio.h>
#include "util.h"
#include "collection.h"

extern SDL_Window *window;

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

char* OS_GetFontPath( char* fontName,char* backupFontName )
{
	char* fontFolder = getenv("WINDIR");
	int length = strlen(fontName)+strlen(fontFolder)+8;
	char* fontPath = (char*)malloc_s(length*sizeof(char));
	memset(fontPath,0,length);
	strcat(fontPath,fontFolder);
	strcat(fontPath,"\\fonts\\");
	strcat(fontPath,fontName);
	if(OS_PathExist(fontPath))
	{
		return fontPath;
	}
	else
	{
		if(backupFontName!=NULL)
		{
			return OS_GetFontPath(backupFontName,NULL);
		}
		else
		{
			GameCrash(0); //TODO:一个错误码
		}
	}
	return NULL;
}

//Author:冰点青蛙
BOOL FindFirstFileExists(LPCTSTR lpPath, DWORD dwFilter)
{
    WIN32_FIND_DATA fd;
    HANDLE hFind = FindFirstFile(lpPath, &fd);
    BOOL bFilter = (FALSE == dwFilter) ? TRUE : fd.dwFileAttributes & dwFilter;
    BOOL RetValue = ((hFind != INVALID_HANDLE_VALUE) && bFilter) ? TRUE : FALSE;
    FindClose(hFind);
    return RetValue;
}

//Author:冰点青蛙
BOOL FilePathExists(LPCTSTR lpPath)
{
    return FindFirstFileExists(lpPath, FALSE);
}

BOOL OS_PathExist(char* path)
{
	return FilePathExists(path);
}

/*char* OS_UTF8ToOSEncoding( char* utf8text,BOOL autoFreeOldText )
{
	int i;
	char *newText = NULL;
	size_t size = MultiByteToWideChar(CP_UTF8,0,utf8text,-1,NULL,0);
	wchar_t *newWText = (wchar_t*)malloc_s((size+1)*sizeof(wchar_t));
	newText = (char*)malloc_s((size*4+1)*sizeof(char));
	memset(newWText,0,size+1);
	memset(newText,0,size*4+1);
	MultiByteToWideChar(CP_UTF8,0,utf8text,-1,newWText,size);
	wcstombs(newText,newWText,size*4);
	newText = (char*)realloc_s(newText,(strlen(newText)+1)*sizeof(char));
	if(autoFreeOldText)
		free(utf8text);
	free(newWText);
	return newText;
}*/

/*ArrayList* OS_GetFilesOfFolder(char* path)
{
	HANDLE hFile;
	WIN32_FIND_DATA c_file;
	char* pathFilter = (char*)malloc_s((strlen(path)+7)*sizeof(char));
	ArrayList* arrayList = NULL;
	//char** files = *result;
	memset(pathFilter,0,(strlen(path)+7));
	strcat(pathFilter,path);
	strcat(pathFilter,"\\*.lua");
	hFile = FindFirstFile(pathFilter, &c_file);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		arrayList = ArrayListCreate(ARRAYLIST_DEFAULT_SIZE,ARRAYLIST_DEFAULT_RATIO);
		return arrayList;
	}
	FindNextFile
	if(!(c_file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{

	}
}*/

#endif

//是不是应该挪到别处?毕竟看起来它不是平台相关的.
char* OS_SetWindowTitle( char* title )
{
	SDL_SetWindowTitle(window,title);
}
