#include "util.h"
#include "minestrike.h"

StringBuilder* SBCreate()
{
	StringBuilder *sb = (StringBuilder*)malloc_s(sizeof(StringBuilder));
	sb->bufferedString = (char**)malloc_s(sizeof(char*)*STRING_BUILDER_MAX_BUFFER);
	sb->bufferPointer = 0;
	return sb;
}

StringBuilder* SBAppend( StringBuilder *sb,char* str )
{
	if(sb->bufferPointer==STRING_BUILDER_MAX_BUFFER)
		return sb;
	sb->bufferedString[sb->bufferPointer]=str;
	sb->bufferPointer++;
	return sb;
}

char* SBBuild( StringBuilder *sb )
{
	int i,length=1;
	char* str=NULL;
	for(i=0;i<sb->bufferPointer;i++)
	{
		length+=strlen(sb->bufferedString[i]);
	}
	str = (char*)malloc_s(length*sizeof(char));
	memset(str,0,length*sizeof(char));
	for(i=0;i<sb->bufferPointer;i++)
	{
		strcat(str,sb->bufferedString[i]);
	}
	free(sb);
	return str;
}

void SBAbandon(StringBuilder *sb)
{
	free(sb);
}

void* malloc_s(size_t size)
{
	void *mem = NULL;
	mem = malloc(size);
	if(mem == NULL)
	{
		printf("Out of memory!\n");
		GameCrash(ERROR_OUT_OF_MEMORY);
	}
	return mem;
}

void* realloc_s( void* ptr,size_t size )
{
	ptr = realloc(ptr,size);
	if(ptr == NULL)
	{
		printf("Out of memory!\n");
		GameCrash(ERROR_OUT_OF_MEMORY);
	}
	return ptr;
}





