//judgebtree.cpp -- �ж��Ƿ�Ϊ��ȫ������
#include <iostream>
#include <queue>

using namespace std;

struct node						//���������
{
	char data;					//����
	struct node * lchild;		//�����
	struct node * rchild;		//�Ҷ���
};
typedef struct node * btree;	//������

btree CreateBtree(void);		//���������������������ɶ�����
bool JudgeBtree(btree);			//�������ж϶������Ƿ�Ϊ��ȫ������
void PreOrder(btree);			//�������������������
void InOrder(btree);			//�������������������
void PostOrder(btree);			//��������������������

int main()						//������
{
	cout << " ---------------------------------------- " << endl;
	cout << "|       ��ӭʹ����ȫ�������ж�ϵͳ       |" << endl;
	cout << " ---------------------------------------- " << endl;
	char choice = ' ';
	btree T = new node;
	while (choice != '6')
	{
		cout << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "|       �밴���ּ�ѡ����Ӧ���ܣ�           |" << endl;
		cout << "|       1.������������ʹ����������ǰ��ѡ�� |" << endl;
		cout << "|       2.�ж���ȫ������                   |" << endl;
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
			T = CreateBtree();
			cout << "********������������ɣ�********" << endl;
			break;
		case '2':
			if (JudgeBtree(T))
				cout << "�ö�������һ����ȫ��������" << endl;
			else
				cout << "�ö���������һ����ȫ��������" << endl;
			break;
		case '3':
			PreOrder(T);
			break;
		case '4':
			InOrder(T);
			break;
		case '5':
			PostOrder(T);
			break;
		case '6':
			cout << endl;
			
		default:
			cout << " ------------------------------------------ " << endl;
			cout << "|       ���������������������룡         |" << endl;
			cout << " ------------------------------------------ " << endl;
		}
	}
	cin.get();
	return 0;
}

btree CreateBtree(void)			//�ݹ齨��������
{
	btree t;
	char ch;
	cin >> ch;
	if (ch == '#')				//�����ַ�Ϊ#��ʾ��λ�ô����Ϊ��
		return NULL;
	else
	{
		t = new node;			//���ڵ��ʼ��
		t->data = ch;
		t->lchild = CreateBtree();
		t->rchild = CreateBtree();
	}
	return t;
}

bool JudgeBtree(btree T)		//��������ж϶������Ƿ�Ϊ��ȫ������
{
	bool flag = false;			//flag���ж��Ƿ��ҵ��ս��
	btree p;
	queue<btree> Q;
	if (T == NULL)				//��������Ϊ�գ���������ȫ������
		return true;
	Q.push(T);
	while (!Q.empty())		//�����в�Ϊ��
	{
		p = Q.front();
		Q.pop();
		if (p == NULL)			//������������ս�㣬��flag���Ϊtrue
			flag = true;
		else if (flag)			//���Ѿ����ֿս�㣬���жϸý��֮���Ƿ��ǿս�㣬���ҵ��ǿս�㣬��ö�����������ȫ������
			return false;
		else					//����ǰ���ǿգ���֮ǰû���ҵ��ս�㣬�򽫸ýڵ�����Ҷ���������ӣ����������ʹ��
		{
			Q.push(p->lchild);
			Q.push(p->rchild);
		}
	}
	return true;				//ѭ����ɣ�֤���ö���������ȫ������
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