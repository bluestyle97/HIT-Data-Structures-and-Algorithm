// linkedlist.cpp -- ���Ա���α�ʵ��
#include <iostream>
#define MAXSIZE 100

using namespace std;

//���Ͷ���
template <typename elementtype>
struct space
{
	elementtype element;
	int next;
};
template <typename elementtype>
space SPACE[MAXSIZE];		//�洢��
typedef int cursor;
cursor av;		//�α��������ʶ���Ա�

				//�洢�ع������ÿռ�ĳ�ʼ��
template <typename elementtype>
void Initialize(space &S, int *av)
{
	int i;
	for (j = 0; j < MAXSIZE - 1; j++)
		S[j].next = j + 1;
	S[j].next = -1;
	*av = 0;
}

//����������
template <typename elementtype>
void Insert(elementtype x, cursor p, space &S)		//����p����
{
	cursor q;
	S[q].element = x;
	S[q].next = S[q].next;
	S[p].next = q;
}

//������ɾ��
template <typename elementtype>
void Delete(cursor p, space &S)
{
	cursor q;
	if (S[p].next != -1)
	{
		q = S[p].next;
		S[p].next = S[q].next;
	}
}
