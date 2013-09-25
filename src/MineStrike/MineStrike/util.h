#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRING_BUILDER_MAX_BUFFER 24

/*StringBuilder��һ���ܽ�����ַ���ƴ��Ϊһ���Ĺ���.*/
typedef struct {
	char** bufferedString;
	int bufferPointer;
} StringBuilder;

/*����һ���µ�StringBuilder.*/
StringBuilder* SBCreate();
/*��StringBuilder��׷��һ���ַ���.*/
StringBuilder* SBAppend(StringBuilder *sb,char* str);
/*����һ�����ַ���,������Ϻ���Զ�����StringBuilder.*/
char* SBBuild(StringBuilder *sb);
/*�ֶ�����һ��StringBuilder,��Build��StringBuilder����˲���.*/
void SBAbandon(StringBuilder *sb);
/*�����ڴ沢�Ҽ���Ƿ�ɹ�,ʧ�ܻ�ֱ����ֹ��Ϸ�����ش�����250.*/
void* malloc_s(size_t size);