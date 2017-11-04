//@Filename:	btreeTravesal.cpp
//@Description:	Traversal of binary tree
//@Author:		Xu Jiale
//@Create Time:	2016/11/29, 11:20
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

//Struct:		BtreeNode
//Description:	Node of binary tree
//Members:		data: the data stored in the node
//				lchild: the left child node
//				rchild: the right child node
struct BtreeNode
{
	char data;
	BtreeNode * lchild;
	BtreeNode * rchild;
};
//Btree:		the root of a binary tree
typedef BtreeNode * Btree;

//Function:		CreateBtree
//Description:	Create a binary tree and return its root
//Arguments:	void
//Return:		Btree: the root of the created binary tree
Btree CreateBtree(void);
//Function:		PreOrderRec
//Description:	Preorder travesal of binary tree(recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void PreOrderRec(Btree);
//Function:		InOrderRec
//Description:	Inorder travesal of binary tree(recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void InOrderRec(Btree);
//Function:		PostOrderRec
//Description:	Postorder travesal of binary tree(recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void PostOrderRec(Btree);
//Function:		PreOrder
//Description:	Preorder travesal of binary tree(non-recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void PreOrder(Btree);
//Function:		InOrder
//Description:	Inorder travesal of binary tree(non-recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void InOrder(Btree);
//Function:		PostOrder
//Description:	Postorder travesal of binary tree(non-recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void PostOrder(Btree);
//Function:		LevelOrder
//Description:	Levelorder travesal of binary tree(non-recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void LevelOrder(Btree);

int main()
{
	Btree t = NULL;
	bool flag = true;
	while (flag)
	{
		char choice;
		cout << endl;
		cout << " ---------------------------------------------- " << endl;
		cout << "|              ������������������              |" << endl;
		cout << "|              0.����������                    |" << endl;
		cout << "|              1.�ݹ��������                  |" << endl;
		cout << "|              2.�ݹ��������                  |" << endl;
		cout << "|              3.�ݹ�������                  |" << endl;
		cout << "|              4.�ǵݹ��������                |" << endl;
		cout << "|              5.�ǵݹ��������                |" << endl;
		cout << "|              6.�ǵݹ�������                |" << endl;
		cout << "|              7.�������                      |" << endl;
		cout << "|              8.�˳�����                      |" << endl;
		cout << " ---------------------------------------------- " << endl;
		cout << "               ��ѡ���ܣ�";
		cin >> choice;
		switch (choice)
		{
		case '0':
			cout << "�밴���������������ݣ���Ϊ��������#����" << endl;
			t = CreateBtree();
			break;
		case '1':
			cout << "�ݹ���������Ľ��Ϊ��";
			PreOrderRec(t);
			break;
		case '2':
			cout << "�ݹ���������Ľ��Ϊ��";
			InOrderRec(t);
			break;
		case '3':
			cout << "�ݹ��������Ľ��Ϊ��";
			PostOrderRec(t);
			break;
		case '4':
			cout << "�ǵݹ���������Ľ��Ϊ��";
			PreOrder(t);
			break;
		case '5':
			cout << "�ǵݹ���������Ľ��Ϊ��";
			InOrder(t);
			break;
		case '6':
			cout << "�ǵݹ��������Ľ��Ϊ��";
			PostOrder(t);
			break;
		case '7':
			cout << "��������Ľ��Ϊ��";
			LevelOrder(t);
			break;
		case '8':
			flag = false;
			cout << "�������н�����";
			break;
		default:
			cout << "���������������������룡";
		}
	}
	system("pause");
	return 0;
}

Btree CreateBtree(void)			//�����������������д���һ�ö�����
{
	Btree t;
	char ch;
	cin >> ch;
	if (ch == '#')				//���롰#��ʱ֤���ý�㴦Ϊ��
		return NULL;
	else
	{
		t = new BtreeNode;
		t->data = ch;
		t->lchild = CreateBtree();
		t->rchild = CreateBtree();
	}
	return t;
}

void PreOrderRec(Btree t)		//��������������������ĵݹ�ʵ��
{
	if (t != NULL)
	{
		cout << t->data;
		PreOrderRec(t->lchild);
		PreOrderRec(t->rchild);
	}
}

void InOrderRec(Btree t)		//��������������������ĵݹ�ʵ��
{
	if (t != NULL)
	{
		InOrderRec(t->lchild);
		cout << t->data;
		InOrderRec(t->rchild);
	}
}

void PostOrderRec(Btree t)		//���������������������ĵݹ�ʵ��
{
	if (t != NULL)
	{
		PostOrderRec(t->lchild);
		PostOrderRec(t->rchild);
		cout << t->data;
	}
}

void PreOrder(Btree t)			//��������������������ķǵݹ�ʵ��
{
	if (t == NULL)
		return;
	Btree p = t;
	stack<Btree> S;
	while (p != NULL || !S.empty())
	{
		while (p != NULL)
		{
			cout << p->data;
			S.push(p);
			p = p->lchild;
		}
		if (!S.empty())		//����������
		{
			p = S.top();
			S.pop();
			p = p->rchild;
		}
	}
}

void InOrder(Btree t)			//��������������������ķǵݹ�ʵ��
{
	if (t == NULL)
		return;
	Btree p = t;
	stack<Btree> S;
	while (p != NULL || !S.empty())
	{
		while (p != NULL)
		{
			S.push(p);		//��������ջ
			p = p->lchild;
		}
		if (!S.empty())		//����������
		{
			p = S.top();
			S.pop();
			cout << p->data;
			p = p->rchild;
		}
	}
}

void PostOrder(Btree t)			//��������������������ķǵݹ�ʵ��
{
	Btree p = t;
	Btree pre = NULL;
	stack<Btree> S;
	while (p != NULL || !S.empty())
	{
		while (p != NULL)
		{
			S.push(p);		//��������ջ
			p = p->lchild;
		}
		p = S.top();
		if (p->rchild == NULL || p->rchild == pre)
		{
			cout << p->data;
			pre = p;
			S.pop();
			p = NULL;
		}
		else					//����������
			p = p->rchild;
	}
}

void LevelOrder(Btree t)		//�������������������
{
	queue<Btree> Q;
	if (t == NULL)
		return;
	Q.push(t);
	while (!Q.empty())		//�������
	{
		cout << Q.front()->data;
		if (Q.front()->lchild != NULL)
			Q.push(Q.front()->lchild);		//���������
		if (Q.front()->rchild != NULL)
			Q.push(Q.front()->rchild);		//���������
		Q.pop();
	}
}