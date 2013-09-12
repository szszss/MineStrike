#include <stdio.h>
#include <string.h>

#define STRING_BUILDER_MAX_BUFFER 24

typedef struct {
	char** bufferedString;
	int bufferPointer;
} StringBuilder;

char* Substring(char* source,int from,int to);
StringBuilder* SBCreate();
StringBuilder* SBAppend(StringBuilder *sb,char* str);
char* SBBuild(StringBuilder *sb);
void SBAbandon(StringBuilder *sb);