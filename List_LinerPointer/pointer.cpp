// linkedlist.cpp -- ���Ա��ָ��ʵ��
#include <iostream>

using namespace std;

//���Ͷ���
template <typename elementtype>
struct celltype
{
	elementtype element;
	celltype * next;
};
template <typename elementtype>
typedef celltype * LIST;
template <typename elementtype>
typedef celltype * position;

//����������
template <typename elementtype>
position Insert(elementtype x, position p, LIST &L)		//����λ��p֮ǰ
{
	position q = new celltype;
	position s = L;
	if (p == L)
	{
		q->element = x;
		q->next = p;
		return q;
	}
	else
	{
		while (s->next != p && s->next != NULL)
			s = s->next;
		q->element = x;
		q->next = s->next;
		s->next = q;
		return L;
	}
}

//��������λ
template <typename elementtype>
position Locate(elementtype x, LIST L)
{
	position p = L;
	while (p != NULL)
	{
		if (p->element == x)
			return p;
		p = p->next;
	}
	return p;
}

//������ȡԪ��ֵ
template <typename elementtype>
elementtype Retrieve(position p, LIST��L)
{
	return p->element;
}

//������ɾ��
template <typename elementtype>
void Delete(position p, LIST L)		//ɾ��p�����Ԫ��
{
	position q = new celltype;
	if (p->next != NULL)
	{
		q = p->next;
		p->next = q->next;
		delete q;
	}
}

//������ǰ��
template <typename elementtype>
position Previous(position p, LIST L)
{
	position q = new celltype;
	if (p == L)
		cerr << "ǰ��Ԫ�ز�����" << endl;
	else
	{
		q = L;
		while (q->next != p)
			q = q->next;
		return q;
	}
}

//���������
template <typename elementtype>
position Next(position p, LIST L)
{
	position q;
	if (p->next == NULL)
		cerr << "���Ԫ�ز�����" << endl;
	else
	{
		q = p->next;
		return q;
	}
}

//���������
template <typename elementtype>
position Makenull(LIST &L)
{
	L = new celltype;
	L->next = NULL;
	return L;
}

//��������ͷ
template <typename elementtype>
position First(LIST L)
{
	return L;
}

//��������β
template <typename elementtype>
position End(LIST L)
{
	position q = L;
	while (q->next != NULL)
		q = q->next;
	return q;
}