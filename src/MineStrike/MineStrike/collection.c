#include "collection.h"
#include <string.h>
#include <stdlib.h>
#include "util.h"

#define MAX_STRING_HASH 1000000000
#define DEFAULT_HBST_ROOT 500000000
#define MAX_HBST_DEPTH 1023
typedef unsigned long long Hash;

_HashTreeNode* HashTreeNodeCreate(_HashTreeNode* parent,char* name,Hash hashCode,void* data);
Hash HashCode(char* string);

HashTree* HashTreeCreate()
{
	HashTree *ht = (HashTree*)malloc_s(sizeof(HashTree));
	ht->rootNode = HashTreeNodeCreate(NULL,NULL,DEFAULT_HBST_ROOT,NULL);
	ht->length=0;
	return ht;
}
BOOL _HashTreeInsert(_HashTreeNode* inserted,_HashTreeNode* inserting)
{
	_HashTreeNode *curNode = inserted;
	_HashTreeNode *newNode = inserting;
	while(TRUE)
	{
		if(inserting->hash < curNode->hash)
		{
			if(curNode->leftNode==NULL)
			{
				curNode->leftNode = newNode;
				newNode->parentNode=curNode;
				break;
			}
			curNode=curNode->leftNode;
		}
		else if(inserting->hash > curNode->hash)
		{
			if(curNode->rightNode==NULL)
			{
				curNode->rightNode = newNode;
				newNode->parentNode=curNode;
				break;
			}
			curNode=curNode->rightNode;
		}
		//我假设在二次插入时不存在Hash碰撞现象
	}
	return TRUE;
}
BOOL _HashTreeSet(HashTree* ht,char* key,void* value,BOOL allowOverwrite)
{
	_HashTreeNode *curNode = ht->rootNode;
	_HashTreeNode *newNode = NULL;
	Hash hash = HashCode(key);
	int depth = 0;
	while(TRUE)
	{
		if(depth>MAX_HBST_DEPTH)
			return FALSE;
		if(hash < curNode->hash)
		{
			if(curNode->leftNode==NULL)
			{
				newNode = HashTreeNodeCreate(curNode,key,hash,value);
				if(newNode==NULL)
					return FALSE;
				curNode->leftNode = newNode;
				break;
			}
			curNode=curNode->leftNode;
		}
		else if(hash > curNode->hash)
		{
			if(curNode->rightNode==NULL)
			{
				newNode = HashTreeNodeCreate(curNode,key,hash,value);
				if(newNode==NULL)
					return FALSE;
				curNode->rightNode = newNode;
				break;
			}
			curNode=curNode->rightNode;
		}
		else
		{
			if(strcmp(curNode->key,key)==0)
			{
				if(allowOverwrite)
				{
					newNode = HashTreeNodeCreate(curNode->parentNode,key,hash,value);
					if(newNode==NULL)
						return FALSE;
					newNode->nextNode = curNode->nextNode;
					newNode->leftNode = curNode->leftNode;
					newNode->rightNode = curNode->rightNode;
					if(curNode->parentNode->leftNode==curNode)
					{
						curNode->parentNode->leftNode=newNode;
					}
					else if(curNode->parentNode->rightNode==curNode)
					{
						curNode->parentNode->rightNode=newNode;
					}
					else
					{
						curNode->parentNode->nextNode=newNode;
					}
					free(curNode); //使用更专业的函数
					return TRUE;
				}
				else
				{
					return FALSE;
				}
			}
			if(curNode->nextNode==NULL)
			{
				newNode = HashTreeNodeCreate(curNode,key,hash,value);
				if(newNode==NULL)
					return FALSE;
				curNode->nextNode = newNode;
				break;
			}
			curNode=curNode->nextNode;
		}
		depth++;
	}
	return TRUE;
}
BOOL HashTreeAdd(HashTree* ht,char* key,void* value)
{
	return _HashTreeSet(ht,key,value,FALSE);
}
BOOL HashTreeSet(HashTree* ht,char* key,void* value)
{
	return _HashTreeSet(ht,key,value,TRUE);
}
_HashTreeNode* _HashTreeGet(HashTree* ht,char* key)
{
	_HashTreeNode* node = ht->rootNode;
	Hash hash = HashCode(key);
	while(TRUE)
	{
		if(node==NULL)
			return NULL;
		if(hash < node->hash)
		{
			node=node->leftNode;
		}
		else if(hash > node->hash)
		{
			node=node->rightNode;
		}
		else
		{
			if(node->nextNode==NULL || strcmp(key,node->key)==0)
				return node;
			node=node->nextNode;
		}
	}
}
BOOL HashTreeRemove(HashTree* ht,char* key)
{
	_HashTreeNode* node = NULL;
	_HashTreeNode* parent = NULL;
	node = _HashTreeGet(ht,key);
	if(node==NULL)
		return FALSE;
	parent = node->parentNode;
	if(parent->nextNode!=node && node->nextNode!=NULL)
	{
		if(parent->leftNode==node)
		{
			parent->leftNode=node->nextNode;
		}
		else if(parent->rightNode==node)
		{
			parent->rightNode=node->nextNode;
		}
		node->nextNode->parentNode=parent;
		node->nextNode->leftNode=node->leftNode;
		node->nextNode->rightNode=node->rightNode;
		free(node);
		return TRUE;
	}
	else if(parent->leftNode==node)
	{
		if(node->rightNode==NULL)
		{
			parent->leftNode=node->leftNode;
			node->leftNode->parentNode = parent;
		}
		else
		{
			parent->leftNode=node->rightNode;
			node->rightNode->parentNode = parent;
			_HashTreeInsert(node->rightNode,node->leftNode);
		}
		free(node);
		return TRUE;
	}
	else if(parent->rightNode==node)
	{
		if(node->leftNode==NULL)
		{
			parent->rightNode=node->rightNode;
			node->rightNode->parentNode = parent;
		}
		else
		{
			parent->rightNode=node->leftNode;
			node->leftNode->parentNode = parent;
			_HashTreeInsert(node->leftNode,node->rightNode);
		}
		free(node);
		return TRUE;
	}
	else if(parent->nextNode==node)
	{
		parent->nextNode=node->nextNode;
		if(node->nextNode!=NULL)
			node->nextNode=parent;
		free(node);
		return TRUE;
	}
	return FALSE;
}
void* HashTreeGet(HashTree* ht,char* key)
{
	_HashTreeNode* node = NULL;
	node = _HashTreeGet(ht,key);
	if(node==NULL)
		return NULL;
	return node->value;
}
//int HashTreeLength(HashTree* ht,char* key);
BOOL _HashTreeNodeDestroy(_HashTreeNode* node)
{
	char i = 0;
	if(node->nextNode!=NULL)
		i += _HashTreeNodeDestroy(node->nextNode);
	else
		i++;
	if(node->leftNode!=NULL)
		i += _HashTreeNodeDestroy(node->leftNode);
	else
		i++;
	if(node->rightNode!=NULL)
		i += _HashTreeNodeDestroy(node->rightNode);
	else
		i++;
	if(i!=3)
		return FALSE;
	free(node);
	return TRUE;
}
BOOL HashTreeDestroy(HashTree* ht)
{
	BOOL result = _HashTreeNodeDestroy(ht->rootNode);
	if(result == TRUE)
		free(ht);
	return result;
}

_HashTreeNode* HashTreeNodeCreate(_HashTreeNode* parent,char* name,Hash hashCode,void* data)
{
	_HashTreeNode* node = (_HashTreeNode*)malloc_s(sizeof(_HashTreeNode));
	node->hash=hashCode;
	node->key=name;
	node->leftNode=NULL;
	node->rightNode=NULL;
	node->parentNode=parent;
	node->nextNode=NULL;
	node->value=data;
	return node;
}
Hash HashCode(char* string)
{
	int i = 0;
	Hash hash = strlen(string);
	while(string[i]!='\0')
	{
		hash *= (string[i]*i);
		i++;
	}
	return hash>MAX_STRING_HASH?hash%MAX_STRING_HASH:hash;
}