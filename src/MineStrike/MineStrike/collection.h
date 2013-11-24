#pragma once

#ifndef _WINDEF_
#ifndef BOOL
typedef int BOOL;
#define FALSE 0
#define TRUE 1
#endif
#endif

/*
哈希二叉搜索树
Hash Binary Search Tree
HBST简称为HashTree,其本质是一个二叉搜索树,键(Key)使用字符串,通过对字符串的Hash运算来作为每个节点的值.
值得一提的是,同BST一样,HashTree不是一个平衡树,在极端情况下会退化成链表.
*/
#pragma region HashTree
typedef struct _HashTreeNode{
	unsigned long long int hash;
	char *key;
	void *value;
	struct _HashTreeNode *parentNode;
	struct _HashTreeNode *leftNode;
	struct _HashTreeNode *rightNode;
	struct _HashTreeNode *nextNode; //当发生Hash冲突时,节点就会变成一个链表
} _HashTreeNode;

typedef struct {
	int length;
	struct _HashTreeNode *rootNode;
} HashTree;

HashTree* HashTreeCreate();
BOOL HashTreeAdd(HashTree* ht,char* key,void* value);
BOOL HashTreeSet(HashTree* ht,char* key,void* value);
BOOL HashTreeRemove(HashTree* ht,char* key);
void* HashTreeGet(HashTree* ht,char* key);
//int HashTreeLength(HashTree* ht,char* key);
BOOL HashTreeDestroy(HashTree* ht);
#pragma endregion HashTree

#pragma region ArrayList
typedef struct {
	void **arrays;
	int available;
	int usedLength;
	int maxLength;
} ArrayList;

typedef struct{
	ArrayList* arrayList;
	int pointer;
} ArrayListIterator;

ArrayList* ArrayListCreate(int defLength);
BOOL ArrayListAdd(ArrayList* arrayList,void* value);
BOOL ArrayListSet(ArrayList* arrayList,void* value,int index);
BOOL ArrayListRemove(ArrayList* arrayList,void* value);
void* ArrayListGet(ArrayList* arrayList,int index);
int ArrayListIndexOf(ArrayList* arrayList,void* value);
ArrayListIterator* ArrayListMakeIterator(ArrayList* arrayList);

BOOL ArrayListIteratorHasNext(ArrayListIterator* iterator,BOOL autoFree);
void* ArrayListIteratorGetNext(ArrayListIterator* iterator);

#pragma endregion ArrayList