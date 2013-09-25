#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRING_BUILDER_MAX_BUFFER 24

/*StringBuilder是一个能将多个字符串拼接为一个的工具.*/
typedef struct {
	char** bufferedString;
	int bufferPointer;
} StringBuilder;

/*创建一个新的StringBuilder.*/
StringBuilder* SBCreate();
/*向StringBuilder后追加一个字符串.*/
StringBuilder* SBAppend(StringBuilder *sb,char* str);
/*生成一个新字符串,生成完毕后会自动销毁StringBuilder.*/
char* SBBuild(StringBuilder *sb);
/*手动销毁一个StringBuilder,已Build的StringBuilder无需此步骤.*/
void SBAbandon(StringBuilder *sb);
/*分配内存并且检查是否成功,失败会直接终止游戏并返回错误码250.*/
void* malloc_s(size_t size);