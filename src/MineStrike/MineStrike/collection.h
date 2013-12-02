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
BOOL HashTreeRemove(HashTree* ht,char* key,void** value);
void* HashTreeGet(HashTree* ht,char* key);
//int HashTreeLength(HashTree* ht,char* key);
BOOL HashTreeDestroy(HashTree* ht,BOOL deleteData);
#pragma endregion HashTree

#pragma region ArrayList
#define ARRAYLIST_DEFAULT_SIZE 8
#define ARRAYLIST_DEFAULT_RATIO 1.5

typedef struct {
	BOOL fragmented;
	void **arrays;
	unsigned long usedSize;
	unsigned long maxSize;
	float growRatio;
} ArrayList;

typedef struct{
	ArrayList* arrayList;
	unsigned long pointer;
} ArrayListIterator;

ArrayList* ArrayListCreate(unsigned long defSize, float defGrowRatio);
BOOL ArrayListAdd(ArrayList* arrayList, void* value);
BOOL ArrayListSet(ArrayList* arrayList, void* value, unsigned long index);
BOOL ArrayListRemove(ArrayList* arrayList, void* value, BOOL autoFree);
BOOL ArrayListRemoveByIndex(ArrayList* arrayList, unsigned long index, BOOL autoFree);
void* ArrayListGet(ArrayList* arrayList, unsigned long index);
BOOL ArrayListPush(ArrayList* arrayList, void* value);
void* ArrayListPop(ArrayList* arrayList, BOOL remove);
BOOL ArrayListIndexOf(ArrayList* arrayList, void* value, unsigned long *result);
unsigned long ArrayListGrow(ArrayList* arrayList, unsigned long size);
ArrayListIterator* ArrayListMakeIterator(ArrayList* arrayList);

BOOL ArrayListIteratorHasNext(ArrayListIterator* iterator, BOOL autoFree);
void* ArrayListIteratorGetNext(ArrayListIterator* iterator);

#pragma endregion ArrayList