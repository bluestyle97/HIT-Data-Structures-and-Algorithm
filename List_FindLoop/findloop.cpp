// findloop.cpp -- �ж��������Ƿ��л�
#include <iostream>

using namespace std;

struct node						//�������
{
	int data;					//����
	node *next;					//ָ����һ����ָ��
};
typedef node * LIST;			//��������
typedef node * pointer;			//���ָ������

pointer Append(int, pointer);	//������������ĩβ��ӽ��
void Initialize(LIST);			//��������ʼ������
void Findloop(LIST);			//�������ж��������Ƿ��л�

int main()
{
	LIST l = new node;
	Initialize(l);
	Findloop(l);
	cin.get();
	cin.get();
	return 0;
}

pointer Append(int x, pointer p)
{
	pointer q = new node;
	q->data = x;
	q->next = NULL;			//����ĩ�ڵ��next��Աָ���ָ��
	p->next = q;			//������ĩβ׷�ӽڵ�
	return q;				//����ָ������ӽ���ָ��
}
void Initialize(LIST l)
{
	pointer p = new node;
	pointer q = new node;
	int d;
	int choice;				//����choice�����û�ѡ�񻷵����λ��
	cout << "��������������ݣ�����-1����������룺" << endl;			//���뻷�ĸ��������
	cin >> d;
	l->data = d;			//��ʼ������ͷ���
	l->next = NULL;
	p = q = l;
	while (true)			//��ʼ���������
	{
		cin >> d;
		if (d == -1)
			break;
		p = Append(d, p);
	}
	cout << "��ϣ�����ڼ��������Ϊ������ڣ�������0�����ɻ���" << endl;
	cin >> choice;
	if (choice != 0)		//���û�����ڽ��
	{
		for (int i = 1; i < choice; i++)
			q = q->next;
		p->next = q;		//�������ĩ���ָ�򻷵���ڽ��
	}
	cout << "�����ʼ����ɣ�" << endl;
}
void Findloop(LIST l)
{
	pointer p = new node;
	pointer q = new node;
	int m = 0, n = 0;					//����m���ڼ�¼���㻷�ĳ��ȣ�����n���ڼ��㻷����ڽ��������ͷ���ľ���
	p = q = l;							//��ʼ������ָ�벢ʹ��ָ��ͷ���
	while (p != NULL && q != NULL)
	{
		p = p->next;					//pָ��ÿ�����һ����qָ�����������
		q = q->next->next;
		if (p == q)						//���ƶ����ɴκ�p��qָ��ָ��ͬһ��㣬��˵�����������л�
		{
			cout << "���������л���" << endl;
			p = p->next;				//p��q�ƶ���ͬһλ�ú�qָ�벻����pָ������ƶ�����ÿ�ƶ�һ��mֵ��1
			m++;
			while (p != q)				//��p�ٴ���qָ��ͬһ���ʱ��m��ֵ���ǻ��ĳ���
			{
				p = p->next;
				m++;
			}
			cout << "���ĳ���Ϊ" << m << endl;
			p = q = l;							//��p��qָ�븴λ������ͷ���
			for (int i = 0; i < m; i++)			//��qָ������ƶ�����ͷ�����໷�ĳ��ȵ�λ�ô�
				q = q->next;
			while (p != q)				//p��qָ��ͬʱ����ƶ���ÿ�ƶ�һ��nֵ��1
			{
				p = p->next;
				q = q->next;
				n++;
			}							//��p��qָ���ٴ�ָ��ͬһ���ʱ���ý����ǻ�����ڽ�㣬��ʱnֵ���Ǹý����ͷ���ľ���
			cout << "��������������еĵ�" << n + 1 << "����㣬�ý�������Ϊ" << p->data << endl;
			return;
		}
	}
	cout << "��������û�л���" << endl;			//ѭ�������������в����ڻ�
}