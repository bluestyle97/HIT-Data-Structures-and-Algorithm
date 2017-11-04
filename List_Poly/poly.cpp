// poly.cpp -- ����ʽ�˷�
#include <iostream>

using namespace std;

struct polynode			//�ṹ������ʽ�еĵ���ʽ�ڵ�����
{
	int coef;			//�ṹ��Աcoef������ʽ��ϵ��
	int exp;			//�ṹ��Աexp������ʽ�Ĵ���
	polynode *link;		//�ṹ��Աlink:ָ����һ�ڵ�λ�õ�ָ��
};
typedef polynode * poly;		//����poly������ʽ����
typedef polynode * pointer;		//����pointer��ָ������ڵ��ָ��

pointer Attach(int, int, pointer);		//����������һ������ʽ�ڵ㣬�������ӵ�����ָ��֮�󣬲�����ָ��ýڵ��ָ��
void Initialize(poly);					//��������ʼ������ʽ����
pointer MultiMono(pointer, pointer);	//������������������ʽ��˵Ľ����Ϊ������һ���ڵ㣬������ָ��ýڵ��ָ��
poly Multiply(poly, poly);				//����������������ʽ������ˣ�������浽�����У�������ָ��������ָ��
pointer Delete(poly, pointer);			//������ɾ������ʽ�����в���ָ����ָ���Ԫ��
poly Simplify(poly);					//�������������ʽ���ϲ�ͬ����
void PrintPoly(poly);					//��������ӡ����ʽ

int main()
{
	poly f = new polynode;				//f��g������˵���������ʽ
	poly g = new polynode;
	poly result;						//result���洢f��g��˵Ľ��
	Initialize(f);						//��ʼ������ʽf��g
	Initialize(g);
	result = Multiply(f, g);			//�������ʽ�˻�
	cout << endl;
	cout << "����ʽ��˵Ľ������ǰΪ��" << endl;
	PrintPoly(result);
	result = Simplify(result);
	cout << "����ʽ��˵Ľ�������Ϊ��" << endl;
	PrintPoly(result);
	cin.get();
	cin.get();
	return 0;
}

pointer Attach(int c, int e, pointer d)
{
	pointer q = new polynode;
	q->coef = c;
	q->exp = e;
	q->link = NULL;
	d->link = q;		//׷�ӽ��q��dָ��ָ��Ľ��֮��
	return q;			//��������ĩ�ڵ�
}

void Initialize(poly f)
{
	pointer p = new polynode;
	int c, e;
	int count = 1;		//����count����ǰ�������������
	cout << "==========��ʼ������ʽ==========" << endl;
	cout << "<<<��ʾ������һ��0��ʾ��������>>>" << endl;
	cout << "�������" << count << "���ϵ���ʹ������ÿո�ָ�����";
	cin >> c >> e;
	f->coef = c;		//��ʼ������ʽ����ͷ���
	f->exp = e;
	f->link = NULL;
	p = f;
	count++;
	while (true)
	{
		cout << "�������" << count << "���ϵ���ʹ������ÿո�ָ�����";
		cin >> c >> e;
		if (c == 0 && e == 0)		//����һ��0��ʾ����������˳�ѭ��
			break;
		p = Attach(c, e, p);		//�����ʽ����ĩβ׷���½ڵ㣬ʹpָ���µ�ĩ���
		count++;
	}
}

pointer MultiMono(pointer a, pointer b)
{
	pointer p = new polynode;		//ָ��p��ָ����ʽa��b������ý��
	p->coef = a->coef * b->coef;	//��������ʽ��ˣ�ϵ�����
	p->exp = a->exp + b->exp;		//��������ʽ��ˣ��������
	p->link = NULL;					//ָ���Ա��ʼ��Ϊ��
	return p;						//����ָ����ʽ��˽����ָ��
}

poly Multiply(poly f, poly g)
{
	pointer a = f, b = g->link;
	int c, e;
	pointer p;
	pointer result = MultiMono(f, g);		//��ʼ���˻�����ʽ����ͷ���
	p = result;
	while (a != NULL)				//��������ʽ�еĵ���ʽ�������
	{
		while (b != NULL)
		{
			c = a->coef * b->coef;
			e = a->exp + b->exp;
			p = Attach(c, e, p);	//������˽����������
			b = b->link;
		}
		b = g;
		a = a->link;
	}
	return result;					//���س˻��������ͷָ��
}

pointer Delete(poly f, pointer p)
{
	pointer pos = f;
	pointer s = new polynode;
	s = f;
	if (p == f)						//��ɾ��ͷ��㣬�򷵻��µ�ͷ���
	{
		s = s->link;
		return s;
	}
	while (s->link != p && s != NULL)		//���Ҵ�ɾ���Ľ��λ��
		s = s->link;
	s->link = p->link;				//ɾ�����p
	return pos;						//����ͷָ��
}

poly Simplify(poly f)
{
	pointer p, q, head;
	head = p = f;					//pָ������ָ���һ��
	while (!(p == NULL || p->link == NULL))
	{
		q = p->link;				//qָ��p�����һ��
		while (q != NULL)
		{
			if (q->exp == p->exp)			//��q��Ĵ�����p����ͬ����ϲ�p��p���ɾ��q��
			{
				p->coef = p->coef + q->coef;
				head = Delete(f, q);
				q = q->link;		//q����ƶ���������p�Ƚ��ж��Ƿ��ܺϲ�
				continue;
				if (p->coef == 0)	//��p��ϵ��Ϊ0��ɾ��p��
					head = Delete(f, p);
			}
			else q = q->link;
		}
		p = p->link;				//p����ƶ�
	}
	return head;					//����ͷָ��
}

void PrintPoly(poly f)				//��ӡ����ʽ
{
	pointer p = f;
	while (p != NULL)
	{
		if (p->coef > 0 && p != f)
		{
			if (p->exp == 0)
				cout << "+" << p->coef;
			else
				cout << "+" << p->coef << "x^" << p->exp;
		}
		else if (p->coef < 0)
		{
			if (p->exp == 0)
				cout << p->coef;
			else
				cout << p->coef << "x^" << p->exp;
		}
		else
			if (p->exp == 0)
				cout << p->coef;
			else
				cout << p->coef << "x^" << p->exp;
		p = p->link;
	}
	cout << endl;
}
