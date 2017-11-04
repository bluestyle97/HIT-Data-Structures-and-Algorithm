//buildbtree.cpp -- ���ݶ�������ǰ�����к��������н���������
#include <iostream>
#include <string>

using namespace std;

struct btreenode			//���������
{
	char data;				//����
	btreenode * lchild;		//�����
	btreenode * rchild;		//�Ҷ���
};
typedef btreenode * btree;	//������

struct set					//�ṹ�壺5Ԫ�飬���ڷǵݹ齨��������
{
	btree parent;			//ĿǰҪ���ĸ����ĸ���
	bool mark;				//���Ŀǰ�����������parent������ӻ����Ҷ���
	int pre;				//��ǰҪ�����������������е���ʼ���
	int mid;				//��ǰҪ�����������������е���ʼ���
	int len;				//���г���
};

struct stacknode			//ջ���
{
	set * node;
	stacknode * next;
};
typedef stacknode * Stack;		//ջ
typedef stacknode * pointer;	//ջ���ָ��

Stack CreateStack(void);	//����������һ����ջ
bool IsEmpty(Stack);		//�������ж�ջ�Ƿ�Ϊ��
void MakeEmpty(Stack);		//���������ջ
void Pop(Stack);			//��������ջ
void Push(set *, Stack);	//������ѹջ
set * Top(Stack);			//����������ջ��Ԫ��

void BuildBtreeRec(string, string, btree &);	//�������ݹ黹ԭ������
btree BuildBtree(string, string, int);			//�������ǵݹ黹ԭ������
void PreOrderRec(btree);	//�������������������
void InOrderRec(btree);		//�������������������
void PostOrderRec(btree);	//�������������������

int main()
{
	cout << " ------------------------------------------ " << endl;
	cout << "|         ��ӭʹ�ö�������ԭ����         |" << endl;
	cout << " ------------------------------------------ " << endl;
	string preorder, inorder;
	cout << "�����������������������У�";
	cin >> preorder;
	cout << "�����������������������У�";
	cin >> inorder;
	btree result = new btreenode;
	char choice = ' ';
	while (choice != '6')
	{
		cout << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "|        �밴���ּ�ѡ����Ӧ����            |" << endl;
		cout << "|        1.�ݹ黹ԭ������                  |" << endl;
		cout << "|        2.�ǵݹ黹ԭ������                |" << endl;
		cout << "|        3.�������������                  |" << endl;
		cout << "|        4.�������������                  |" << endl;
		cout << "|        5.�������������                  |" << endl;
		cout << "|        6.�˳�����                        |" << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "         ����������ѡ��";
		cin >> choice;
		cout << " ------------------------------------------ " << endl;
		switch (choice)
		{
		case '1':
			BuildBtreeRec(preorder, inorder, result);
			cout << "�������ѻ�ԭ��" << endl;
			break;
		case '2':
			result = BuildBtree(preorder, inorder, (int)preorder.size());
			cout << "�������ѻ�ԭ��" << endl;
			break;
		case '3':
			PreOrderRec(result);
			break;
		case '4':
			InOrderRec(result);
			break;
		case '5':
			PostOrderRec(result);
			break;
		case '6':
			cout << " ------------------------------------------ " << endl;
			cout << "|         ��лʹ�ö�������ԭ����         |" << endl;
			cout << " ------------------------------------------ " << endl;
			break;
		default:
			cout << " ------------------------------------------ " << endl;
			cout << "|         ���������������������룡       |" << endl;
			cout << " ------------------------------------------ " << endl;
		}
	}
	cin.get();
	cin.get();
	return 0;
}

Stack CreateStack(void)
{
	Stack s = new stacknode;
	if (s == NULL)
		cerr << "�ڴ�ռ�������" << endl;
	else
		s->next = NULL;
	return s;
}

bool IsEmpty(Stack s)
{
	return s->next == NULL;
}

void MakeEmpty(Stack s)
{
	if (s->next != NULL)
		while (!IsEmpty(s))
			Pop(s);
}

void Pop(Stack s)
{
	pointer p = new stacknode;
	if (!IsEmpty(s))
	{
		p = s->next;
		s->next = p->next;
		delete p;
	}
}

void Push(set *t, Stack s)
{
	pointer p = new stacknode;
	p->node = t;
	p->next = s->next;
	s->next = p;
}

set *Top(Stack s)
{
	if (!IsEmpty(s))
		return s->next->node;
}

void BuildBtreeRec(string pre, string in, btree &t)		//�ݹ黹ԭ������
{
	t = new btreenode;
	if (pre.size() == 0)
	{
		t = NULL;
		return;
	}
	t->data = pre[0];
	int index = 0;
	t->lchild = NULL;
	t->rchild = NULL;
	while (index < (int)in.size() && in[index] != pre[0])
		index++;
	int left_length = index;
	int right_length = pre.size() - index - 1;
	if (left_length > 0)
		BuildBtreeRec(pre.substr(1, left_length), in.substr(0, left_length), t->lchild);
	if (right_length > 0)
		BuildBtreeRec(pre.substr(1 + left_length, right_length), in.substr(1 + left_length, right_length), t->rchild);
}

btree BuildBtree(string pre, string in, int n)
{
	btree parent, head;
	bool flag;
	int prestart, midstart, length;
	Stack stk = CreateStack();
	head = new btreenode;				//����һ��ͷ��㣬�����ӽ��ָ������������
	head->lchild = head->rchild = NULL;
	set s = { head, false, 0, 0, n };
	Push(&s, stk);						//��Ԫ����ջ
	while (!IsEmpty(stk))				//��ջ���գ�ѭ������
	{
		set *tmp = Top(stk);
		tmp->parent = new btreenode;
		Pop(stk);			//ջ����Ԫ���ջ
		if (tmp->len > 0)	//�������գ��������������
		{
			if (tmp->mark == false)			//��ǰ�������parent������
			{
				tmp->parent->lchild = new btreenode;
				tmp->parent->lchild->data = pre[tmp->pre];
				tmp->parent->lchild->lchild = NULL;
				tmp->parent->lchild->rchild = NULL;
				int k = 0;
				while (k < tmp->len)
				{
					if (pre[tmp->pre] == in[tmp->mid + k])
						break;
					k++;
				}
				set s1 = { tmp->parent->lchild, false, tmp->pre + 1, tmp->mid, k };
				set s2 = { tmp->parent->rchild, true, tmp->pre + k + 1, k + 1, tmp->len - k - 1 };
				Push(&s1, stk);
				Push(&s2, stk);
			}
			else							//��ǰ�������parent���Һ���
			{
				tmp->parent->rchild = new btreenode;
				tmp->parent->rchild->data = pre[tmp->pre];
				tmp->parent->rchild->lchild = NULL;
				tmp->parent->rchild->rchild = NULL;
				int k = 0;
				while (k < tmp->len)		//����ȣ����������������ҵ����ڵ��λ�ã�����ѭ��
				{
					if (pre[tmp->pre] == in[tmp->mid + k])
						break;
					k++;
				}
				set s1 = { tmp->parent->lchild, false, tmp->pre + 1, tmp->mid, k };		//�ѵ�ǰ�����ĸ���������������Ϣ��ջ
				set s2 = { tmp->parent->rchild, true, tmp->pre + k + 1, k + 1, tmp->len - k - 1 };		//�ѵ�ǰ�����ĸ���������������Ϣ��ջ
				Push(&s1, stk);
				Push(&s2, stk);
			}
		}
	}
	return head->lchild;		//����ͷ��������ָ�룬���������ĸ����ָ��
}

void PreOrderRec(btree t)
{
	if (t != NULL)
	{
		cout << t->data;
		PreOrderRec(t->lchild);
		PreOrderRec(t->rchild);
	}
}

void InOrderRec(btree t)
{
	if (t != NULL)
	{
		InOrderRec(t->lchild);
		cout << t->data;
		InOrderRec(t->rchild);
	}
}

void PostOrderRec(btree t)
{
	if (t != NULL)
	{
		PostOrderRec(t->lchild);
		PostOrderRec(t->rchild);
		cout << t->data;
	}
}