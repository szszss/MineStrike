#pragma once

#ifndef BOOL
#define BOOL int
#define FALSE 0
#define TRUE 1
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
};

typedef struct {
	int length;
	struct _HashTreeNode rootNode;
} HashTree;

HashTree* HashTreeCreate();
BOOL HashTreePut(HashTree* ht,char* key,void* value);
BOOL HashTreeSet(HashTree* ht,char* key,void* value);
BOOL HashTreeRemove(HashTree* ht,char* key);
void* HashTreeGet(HashTree* ht,char* key);
int HashTreeLength(HashTree* ht,char* key);
int HashTreeLength(HashTree* ht,char* key);
#pragma endregion HashTree

#pragma region ArrayList
typedef struct {

} ArrayList;
#pragma endregion ArrayList