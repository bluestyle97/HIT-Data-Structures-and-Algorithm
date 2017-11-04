//findancestor.cpp -- Ѱ�Ҷ������������������Ĺ�������
#include <iostream>

using namespace std;

struct btreenode					//���������
{
	char data;						//�������
	btreenode * lchild;				//�����
	btreenode * rchild;				//�Ҷ���
	btreenode * parent;				//˫��
};
typedef btreenode * btree;			//������

btree CreateBtree(void);			//�����������������������ظ��ڵ�ָ��
void PreOrder(btree);				//�������������������
void InOrder(btree);				//�������������������
void PostOrder(btree);				//��������������������
btree SearchNode(char, btree);		//������Ѱ�Ҷ�����������Ϊ�ַ�c�Ľ�㣬��������ָ��
btree FindAncestor(btree, btree);	//������Ѱ�Ҷ�����������������������ȣ�������ָ��

int main()							//������
{
	cout << " ---------------------------------------- " << endl;
	cout << "|       ��ӭʹ�ö��������Ѱ��ϵͳ       |" << endl;
	cout << " ---------------------------------------- " << endl;
	btree t = new btreenode;
	btree ancestor = new btreenode;
	btree p = new btreenode;
	btree q = new btreenode;
	char choice = ' ';
	while (choice != '6')			//����6ʱ�˳�����
	{
		cout << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "|       �밴���ּ�ѡ����Ӧ���ܣ�           |" << endl;
		cout << "|       1.������������ʹ����������ǰ��ѡ�� |" << endl;
		cout << "|       2.Ѱ������㹫������               |" << endl;
		cout << "|       3.��������������������           |" << endl;
		cout << "|       4.��������������������           |" << endl;
		cout << "|       5.��������������������           |" << endl;
		cout << "|       6.�˳�����                         |" << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "        ����������ѡ��";
		cin >> choice;
		cout << " ------------------------------------------ " << endl;
		switch (choice)
		{
		case '1':
			cout << "�밴���������������ݣ���Ϊ��������#����" << endl;
			t = CreateBtree();
			cout << "********������������ɣ�********" << endl;
			break;
		case '2':
			char a, b;
			cout << "����������Ҫ���ҵ������ڵ�����ݣ�" << endl;
			cin >> a >> b;
			p = SearchNode(a, t);	//�ڶ�����������Ҫ���ҵ��������
			q = SearchNode(b, t);
			if (p != NULL && q != NULL)		//��������㶼���ҳɹ�����������ǵ����������������
			{
				ancestor = FindAncestor(p, q);
				cout << "�������������������ȵ�����Ϊ��" << ancestor->data << endl;
			}
			else
				cout << "������Ľڵ���������";
			break;
		case '3':
			PreOrder(t);
			break;
		case '4':
			InOrder(t);
			break;
		case '5':
			PostOrder(t);
			break;
		case '6':
			cout << endl;
			cout << " ------------------------------------------ " << endl;
			cout << "|       ��лʹ�ö��������Ѱ��ϵͳ         |" << endl;
			cout << " ------------------------------------------ " << endl;
			break;
		default:
			cout << " ------------------------------------------ " << endl;
			cout << "|       ���������������������룡         |" << endl;
			cout << " ------------------------------------------ " << endl;
		}
	}
	cin.get();
	return 0;
}

btree CreateBtree(void)			//�����������еݹ����ɶ������������ظ����
{
	btree t;
	char ch;
	cin >> ch;
	if (ch == '#')
		return NULL;
	else
	{
		t = new btreenode;
		t->parent = NULL;
		t->data = ch;
		t->lchild = CreateBtree();
		if (t->lchild != NULL)
			t->lchild->parent = t;
		t->rchild = CreateBtree();
		if (t->rchild != NULL)
			t->rchild->parent = t;
	}
	return t;
}

void PreOrder(btree t)
{
	if (t != NULL)
	{
		cout << t->data;
		PreOrder(t->lchild);
		PreOrder(t->rchild);
	}
}

void InOrder(btree t)
{
	if (t != NULL)
	{
		InOrder(t->lchild);
		cout << t->data;
		InOrder(t->rchild);
	}
}

void PostOrder(btree t)
{
	if (t != NULL)
	{
		PostOrder(t->lchild);
		PostOrder(t->rchild);
		cout << t->data;
	}
}

btree SearchNode(char c, btree t)			//�ڶ�����t�в�������Ϊ�ַ�c�Ľ�㣬��������ָ��
{
	btree a = NULL, b = NULL;
	if (t != NULL)
	{
		if (t->data == c)
			return t;
		else
		{
			a = SearchNode(c, t->lchild);	//��������ݹ����
			b = SearchNode(c, t->rchild);
			if (a == NULL && b == NULL)
				return NULL;
			else
				return (b == NULL) ? a : b;
		}
	}
	return NULL;
}

btree FindAncestor(btree p, btree q)	//���ҽ��p��q�������������
{
	if (p == q)							//��p��q��ͬһ��㣬�����ǵ�����������Ⱦ������Ǳ���
		return p;
	btree a = p;						//ʹָ��a��ʼ��ָ��p���
	while (a != NULL)
	{
		btree b = q;					//ʹָ��b��ʼ��ָ��q���
		while (a != b && b != NULL)		//bָ�������˫�׽���ƶ���ֱ������a���򵽴�����
			b = b->parent;
		if (a == b)						//��a��bָ��ͬһ��㣬�������������˳�ѭ��
			break;
		else							//��bδ����a��������ʹaָ����˫�׷����ƶ�
			a = a->parent;
	}
	return a;							//ѭ��������ָ��a��bָ��ͬһ��㣬����a��Ϊp��q�������������
}