//@Filename:	bstree.cpp
//@Description: binary search tree
//@Author:		Xu Jiale
//@Create Time: 2016/12/14, 17:33
//Copyright (C) 2016 HIT. All rights reserved
#include <iostream>

using namespace std;

//Struct:		records
//Description:	A record
//Members:		key: the key of the records
//				number: the number of the same key
struct records
{
	int key;
	int number;
};
//Struct:		BSTNode
//Description:	The node of a binary search tree
//Members:		data: the record stored in the node
//				lchild: the left child of the node
//				rchild: the right child of the node
struct BSTNode
{
	records data;
	BSTNode * lchild;
	BSTNode * rchild;
};
typedef BSTNode * BST;

//FUnction:		CreateBST
//Description:	Create a new binary search tree
//Arguments:	void
//Return:		BST: the root of the created binary search tree
BST CreateBST(void);
//Function:		SearchBST
//Description:	Search a record in the binary search tree
//Arguments:	int: the key of the record to be searched
//				BST: the root of the binary search tree
//Return:		BST: the search result
BST SearchBST(int, BST);
//Function:		InsertBST
//Description:	Insert a new record to the binary search tree
//Arguments:	int: the key of the record to be inserted
//				BST &: the root of the binary search tree
//Return:		void
void InsertBST(int, BST &);
//Function:		DeleteBST
//Description:	Delete a record from a bianry search tree
//Arguments:	int: the key of the record to be deleted
//				BST &: the root of the binary search tree
//Return:		void
void DeleteBST(int, BST &);
//Function:		DeleteMin
//Description:	Delete the minimum node from the binary search tree and return the record inside it
//Arguments:	BST &: the root of a binary search tree
//Return:		records: the record stored in the deleted node
records DeleteMin(BST &);
//Funtion:		InOrder
//Description:	Traverse the binary search tree in inorder
//Arguments:	BST: the root of the binary search tree
//Return:		void
void InOrder(BST);

int main()
{
	cout << " ---------------------------------------- " << endl;
	cout << "|       ��ӭʹ�ö��������ϵͳ��         |" << endl;
	cout << " ---------------------------------------- " << endl;
	char choice = ' ';
	int key;
	BST T = new BSTNode;
	while (choice != '6')
	{
		cout << endl;
		cout << " ---------------------------------------- " << endl;
		cout << "|       �밴���ּ�ѡ����Ӧ���ܣ�         |" << endl;
		cout << "|       1.�������������                 |" << endl;
		cout << "|       2.����������������             |" << endl;
		cout << "|       3.���Ҽ�¼                       |" << endl;
		cout << "|       4.�����¼                       |" << endl;
		cout << "|       5.ɾ����¼                       |" << endl;
		cout << "|       6.�˳�����                       |" << endl;
		cout << " ---------------------------------------- " << endl;
		cout << "        ����������ѡ��";
		cin >> choice;
		cout << " ---------------------------------------- " << endl;
		switch (choice)
		{
		case '1':
			cout << "��������������Ԫ�أ�";
			T = CreateBST();
			cout << "��������������ɹ���" << endl;
			break;
		case '2':
			cout << "���������������������Ϊ��";
			InOrder(T);
			cout << endl;
			break;
		case '3':
			BST pointer;
			cout << "������������Ҽ�¼�Ĺؼ��֣�";
			cin >> key;
			pointer = SearchBST(key, T);
			if (pointer != NULL)
				cout << "���ҳɹ�������������й���" << pointer->data.number << "����¼�ؼ���Ϊ" << key << endl;
			else
				cout << "����ʧ�ܣ������������û�м�¼�ؼ���Ϊ" << key << endl;
			break;
		case '4':
			cout << "��������������¼�Ĺؼ��֣�";
			cin >> key;
			InsertBST(key, T);
			cout << "��¼�Ѳ��룡" << endl;
			break;
		case '5':
			cout << "����������ɾ����¼�Ĺؼ��֣�";
			cin >> key;
			DeleteBST(key, T);
			cout << "��¼��ɾ����" << endl;
			break;
		case '6':
			cout << " ------------------------------------------ " << endl;
			cout << "|       ��лʹ�ö��������ϵͳ             |" << endl;
			cout << " ------------------------------------------ " << endl;
			break;
		default:
			cout << " ------------------------------------------ " << endl;
			cout << "|       ���������������������룡         |" << endl;
			cout << " ------------------------------------------ " << endl;
		}
	}
	return 0;
}

BST CreateBST(void)
{
	BST T = NULL;
	int key;
	while (cin >> key)
		InsertBST(key, T);
	cin.clear();
	return T;
}
void InOrder(BST T)
{
	if (T != NULL)
	{
		InOrder(T->lchild);
		for (int i = 0; i < T->data.number; i++)
			cout << T->data.key << " ";
		InOrder(T->rchild);
	}
}
BST SearchBST(int k, BST T)
{
	if (T == NULL || k == T->data.key)
		return T;
	else if (k < T->data.key)
		return SearchBST(k, T->lchild);
	else
		return SearchBST(k, T->rchild);
}
void InsertBST(int k, BST &T)
{
	if (T == NULL)
	{
		T = new BSTNode;
		T->data.key = k;
		T->data.number = 1;
		T->lchild = NULL;
		T->rchild = NULL;
	}
	else if (k < T->data.key)
		InsertBST(k, T->lchild);
	else if (k > T->data.key)
		InsertBST(k, T->rchild);
	else
		T->data.number++;
}
void DeleteBST(int k, BST &T)
{
	if (T != NULL)
	{
		if (k < T->data.key)
			DeleteBST(k, T->lchild);
		else if (k > T->data.key)
			DeleteBST(k, T->rchild);
		else
		{
			if (T->data.number > 1)
				--T->data.number;
			else
			{
				if (T->lchild == NULL)
					T = T->rchild;
				else if (T->rchild == NULL)
					T = T->lchild;
				else
					T->data = DeleteMin(T->rchild);
			}
		}
	}
}
records DeleteMin(BST &T)
{
	records tmp;
	BST p;
	if (T->lchild == NULL)
	{
		p = T;
		tmp = T->data;
		T = T->rchild;
		delete p;
		return tmp;
	}
	else
		return DeleteMin(T->lchild);
}
