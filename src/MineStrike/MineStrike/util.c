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

/*char* WrapText( char* text,unsigned int width )
{
	static unsigned int memLong = 65535;
	static char* wrapMem = NULL;
	static char* wordBuffer = NULL;
	int i,j,k,length; //i表示原下标,j表示wrap后的下标,k为一个计数变量,可以理解为本行的字符数.
	int temp,temp2;
	char c;
	if(wrapMem==NULL)
	{
		wrapMem = (char*)malloc_s(memLong*sizeof(char));
	}
	if(wordBuffer==NULL)
	{
		wordBuffer = (char*)malloc_s(1000*sizeof(char));
	}
	if((length=strlen(text))>(memLong-200))
	{
		memLong=strlen(text+200);
		wrapMem = (char*)realloc_s(wrapMem,memLong);
	}
	memset(wrapMem,0,memLong);
	width *= 1.8;
	for(i=0,j=0,k=0;i<=length;i++)
	{
		c=text[i];
		wordBuffer[j]=c;
		if(c==' '||c=='\0' || (j>10))
		{
			if(k+j<=width) //如果可以容纳下缓冲字符串,则把缓冲字符串写入分行字符串尾部.
			{
				for(temp=0;temp<=j;temp++)
				{
					wrapMem[i+temp]=wordBuffer[temp];
				}
				i+=j;
				j=0;
			}
			else //否则,尝试分割缓冲字符串
			{
				temp = k+j-width;
				for(temp2=j;temp2>=0;temp2--)
				{
					if(wordBuffer[temp2]<0 && (wordBuffer[temp2]&0x40)==0x40)
					{
						break;
					}
				}

			}
		}
		j++;
	}
	return wrapMem
}*/

//需要一个更好的实现
char* WrapText( char* text,unsigned int width )
{
	static unsigned int memLong = 65535;
	static char* wrapMem = NULL;
	int i,j,k,length; //i表示原下标,j表示wrap后的下标,k为一个计数变量,可以理解为本行的字符数.
	int temp,temp2;
	char c;
	if(wrapMem==NULL)
	{
		wrapMem = (char*)malloc_s(memLong*sizeof(char));
	}
	if((length=strlen(text))>(memLong-200))
	{
		memLong=strlen(text+200);
		wrapMem = (char*)realloc_s(wrapMem,memLong);
	}
	memset(wrapMem,0,memLong);
	width *= 1.6;
	for(i=0,j=0,k=0;i<length;i++,j++,k++) //循环遍历原字符串
	{
		c = text[i];
		//if((c&0x80)==0x80)
		//	k--;
		if(c=='\n')  //如果是换行的话,就可以把长度清零了
		{
			k=0;
		}
		if(k>=width)
		{
			if(c>=0 || (c&0x40)==0x40) //UTF8不能在中间截断,所以要判断下一个字符是不是UTF8首字符
			{
				if(c>32&&c<123) //英文不能随意切断哦
				{
					temp = j;
					while(1)
					{
						if(temp==0||wrapMem[temp]=='\n') //本行找不到合适的截断点的话,就直接换行吧!
						{
							//wrapMem[j++]=' ';
							wrapMem[j++]='\n';
							k=0;
							break;
						}
						if(wrapMem[temp]==' '|| c<0) //如果找到"合适"的阶段点的话
						{
							//temp2=temp;
							for(temp2=j;temp2>temp;temp2--) //将一定范围内的字符移位
							{
								wrapMem[temp2+1]=wrapMem[temp2];
							}
							//wrapMem[temp]=' ';
							wrapMem[temp+1]='\n';
							j+=1;
							k=j-temp;
							break;
						}
						if(c>0 || (c<0 && (c&0x40)!=0x40))
						{
							k--;
						}
						temp--;
					}
				}
				else
				{
					//wrapMem[j++]=' ';
					wrapMem[j++]='\n';
					k=0;
				}
				
			}
		}
		else if(c<0 && (c&0x40)==0x40)
		{
			k--;
		}
		wrapMem[j]=c;
	}
	wrapMem[j]=0;
	return wrapMem;
}





