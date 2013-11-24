#pragma once

#ifndef _WINDEF_
#ifndef BOOL
typedef int BOOL;
#define FALSE 0
#define TRUE 1
#endif
#endif

/*
��ϣ����������
Hash Binary Search Tree
HBST���ΪHashTree,�䱾����һ������������,��(Key)ʹ���ַ���,ͨ�����ַ�����Hash��������Ϊÿ���ڵ��ֵ.
ֵ��һ�����,ͬBSTһ��,HashTree����һ��ƽ����,�ڼ�������»��˻�������.
*/
#pragma region HashTree
typedef struct _HashTreeNode{
	unsigned long long int hash;
	char *key;
	void *value;
	struct _HashTreeNode *parentNode;
	struct _HashTreeNode *leftNode;
	struct _HashTreeNode *rightNode;
	struct _HashTreeNode *nextNode; //������Hash��ͻʱ,�ڵ�ͻ���һ������
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