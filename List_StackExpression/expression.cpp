//@Filename:	expression.cpp
//@Description:	Transform expressions by stack
//@Author:		Xu Jiale
//@Last Modify:	2016/01/18, 15:07
//Copyright (C) 2017 HIT. All rights reserved

#include <iostream>
#include <cmath>
#include <cstring>
#define MAXLEN 100

using namespace std;

//Struct:		node
//Description:	The node of stack
//Members:		bool: mark the data type of the node(true-double, false-char)
//				union: anonymous union
//				node *: the linked node
struct node
{
	bool flag;
	union
	{
		double Data;
		char Operator;
	};
	node * next;
};

//The pointer of a node
typedef node * Pointer;
//Stack
typedef node * Stack;

//Function:		CreateStack
//Description:	Create a new empty stack
//Arguments:	void
//Return:		Stack: the top pointer of a stack
Stack CreateStack(void);
//Function:		IsEmpty
//Description:	Judge whether a stack is empty or not
//Arguments:	Stack: the stack to be judged
//Return:		bool: the judge result
bool IsEmpty(Stack);
//Function:		MakeEmpty
//Description:	Clear a empty
//Arguments:	Stack: the stack to be cleared
//Return:		void
void MakeEmpty(Stack);
//Function:		Pop
//Description:	Delete the stack's top
//Arguments:	Stack: the stack to be modified
//Return:		void
void Pop(Stack);
//Function:		Pushdata
//Description:	Push a double-type data into the stack
//Arguments:	double: the data to be pushed
//				stacked: the stack
//Return:		void
void Pushdata(double, Stack);
//Fucntion:		Pushchar
//Description:	Push a char-type data into the stack
//Arguments:	char: the data to be pushed
//				Stack: the stack
//Return:		void
void Pushchar(char, Stack);
//Function:		Topdata
//Description:	Return the double-type data of the stack top
//Arguments:	Stack: the stack
//Return:		double: the double-type data
double Topdata(Stack);
//Fucntion:		Topchar
//Description:	Return the char-type data of the stack top
//Arguments:	Stack: the stack
//Return:		char: the char-type data
char Topchar(Stack);
//Function:		Calculate
//Description:	Calculate the value of theb expression
//Arguments:	Stack: the stack which stores the expression
//Return:		void
void Calculate(Stack);
//Function:		ToPostfix
//Description:	Transform infix expression into postfix expression
//Arguments:	char[]: inputed infix expression
//Return:		Stack: a stack which stores the transformed postfix expression
Stack ToPostfix(char[]);
//Function:		RevStack
//Description:	Reverse the elements in a stack
//Arguments:	Stack: the stack to be reversed
//Return:		Stack: the reversed stack
Stack RevStack(Stack);
//Function:		PrintStack
//Description:	Print the elements in a stack
//Arguments:	Stack: the stack to be printed
//Return:		void
void PrintStack(Stack);	
//Function:		Compare
//Description:	Compare the priority of operators
//Arguements:	char: the first operator
//				char: the second operator
//Return:		bool: the compare result
bool Compare(char, char);
//Function:		JudgeOpt
//Description:	Judge whether an operator is legal
//Arguemnts:	char: the operator to be judged
//Return:		bool: the judge result
bool JudgeOpt(char);
//Function:		Factorial
//Description:	Calculate the factorial of an integer
//Arguments:	int: the integer to be calculated
//Return:		int: the result
int Factorial(int);

int main()
{
	char s[MAXLEN];				//�ַ����飺���ڶ�ȡ����
	Stack stk = CreateStack();	//����һ����ջ
	while (true)
	{
		cout << "��������ʽ������q�˳�����" << endl;
		fgets(s, MAXLEN, stdin);//������׺���ʽ
		if (s[0] == 'q')		//������'q'���˳�
			break;
		stk = ToPostfix(s);		//����׺���ʽת��Ϊ��׺���ʽ
		cout << "�ñ��ʽ�ĺ�׺���ʽΪ��";
		PrintStack(stk);		//��ӡ��׺���ʽ����
		Calculate(stk);			//������ʽ��ֵ�����
	}
	MakeEmpty(stk);				//��ջ���
	return 0;
}

Stack CreateStack(void)			//����һ����ջ
{
	Stack S = new node;
	if (S == NULL)
		cerr << "�ڴ�ռ�������" << endl;
	S->next = NULL;
	return S;
}

bool IsEmpty(Stack S)			//�ж�ջ�Ƿ�Ϊ��
{
	return S->next == NULL;
}

void MakeEmpty(Stack S)			//���ջ
{
	if (S == NULL)
		cerr << "��ջ��" << endl;
	else
		while (!IsEmpty(S))
			Pop(S);
}

void Pop(Stack S)				//��ջ
{
	Pointer p = new node;
	if (IsEmpty(S))
		cerr << "��ջ��" << endl;
	else
	{
		p = S->next;
		S->next = p->next;
		delete p;
	}
}

void Pushdata(double x, Stack s)
{
	Pointer p = new node;
	p->flag = true;
	p->Data = x;
	p->next = s->next;
	s->next = p;
}

void Pushchar(char c, Stack s)
{
	Pointer p = new node;
	p->flag = false;
	p->Operator = c;
	p->next = s->next;
	s->next = p;
}

double Topdata(Stack s)
{
	if (!IsEmpty(s))
		return s->next->Data;
}

char Topchar(Stack s)
{
	if (!IsEmpty(s))
		return s->next->Operator;
}

void Calculate(Stack s)				//�����׺���ʽ��ֵ
{
	Stack result = CreateStack();	//���ڴ洢��������ջ
	Pointer p = new node;
	char opt;						//������
	double numa, numb;				//������
	p = s->next;
	while (p != NULL)
	{
		if (p->flag == true)		//��ջ��Ԫ��Ϊdouble�Ͳ���������ֱ�ӽ���ѹ��ջresult��
			Pushdata(p->Data, result);
		else						//��ջ��Ԫ��Ϊchar�Ͳ�����
		{
			opt = p->Operator;
			numb = Topdata(result); //��ջresult�е���ջ��������������
			Pop(result);
			numa = Topdata(result);
			Pop(result);
			switch (opt)			//���ݲ����������жϽ��к������㣬����������ѹ��ջresult��
			{
			case '+':
				Pushdata(numa + numb, result);
				break;
			case '-':
				Pushdata(numa - numb, result);
				break;
			case '*':
				Pushdata(numa * numb, result);
				break;
			case '/':
				Pushdata(numa / numb, result);
				break;
			case '%':
				if (fabs(numa - (int)numa) < 1e-5 && fabs(numb - (int)numb) < 1e-5)
					Pushdata((int)numa % (int)numb, result);
				else
					cout << "С�����ܽ����������㣡" << endl;
				break;
			case '^':
				Pushdata(pow(numa, numb), result);
				break;
			default:
				cout << "�����޷�ʶ��Ĳ�������" << endl;
			}
		}
		p = p->next;
	}
	cout << "�ñ��ʽ��ֵΪ��" << result->next->Data << endl;	//����resultջ��Ԫ�ؾ��Ǳ��ʽ��ֵ���������
}

Stack ToPostfix(char s[])			//��׺���ʽת��Ϊ��׺���ʽ
{
	Stack result = CreateStack();	//�������ڴ洢ת������Ŀ�ջ
	Stack opt = CreateStack();		//�������ڴ洢�������Ŀ�ջ
	int index = 0;					//��������ʶ���ֽ��������
	int cursor = 0;					//�α꣺���ڽ��������ַ���
	int pos;						//�����ж�С��������λ���α�
	bool flg, sgn;					//�����ͱ���flg�������жϵ�ǰ�����������ͣ�trueΪ��������falseΪ������
									//�����ͱ���sgn�������жϲ������ķ��ţ�trueΪ����falseΪ��
	double num;						//double��num�����ڴ洢�������Ĳ�����
	while (index < (int)strlen(s) - 1)	//�����ַ����Ľ���
	{
		num = 0;					//�������ĳ�ʼ��
		flg = false;
		sgn = true;
		if (s[cursor] == '-' && (0 == cursor || JudgeOpt(s[cursor - 1])))	//�жϲ������Ƿ�Ϊ��
		{
			sgn = false;
			cursor++;
		}
		while ('0' <= s[cursor] && s[cursor] <= '9')	//�������������������֣��������num
		{
			flg = true;
			num = num * 10 + s[cursor] - '0';
			cursor++;
		}
		if (s[cursor] == '.')		//������������С�����֣��������num
		{
			pos = cursor;
			cursor++;
			while ('0' <= s[cursor] && s[cursor] <= '9')
			{
				num += ((s[cursor] - '0') * 1.0 / pow(10, cursor - pos));
				cursor++;
			}
		}
		if (flg == true && s[cursor] == '!')	//���������������Ҽ�⵽!��������򽫲�����ת��Ϊ���Ľ׳�
		{
			if (fabs(num - (int)num) < 1e-5)	//�жϲ������Ƿ�Ϊ����
				num = Factorial((int)num);
			cursor++;
		}
		if (sgn == false)			//�����������ű���ʶΪ�����򽫲�����ȡ��
			num = -num;
		if (flg == true)
			Pushdata(num, result);	//���������Ĳ�����ѹ��ջresult
		else if (s[cursor] == ' ')	//�������ո��ַ���ֱ������
			cursor++;
		else						//����ǰ���������ǲ�����
		{
			if (IsEmpty(opt))		//��������ջoptΪ�գ���ֱ�ӽ���ǰλ�ô��Ĳ�����ѹ������
				Pushchar(s[cursor], opt);
			else					//��������ջopt��Ϊ��
			{
				if (s[cursor] == ')')	//������������ʱ����ջopt�еĲ��������������ѹ��resultջ�У�ֱ�������ű�����Ϊֹ
				{
					while (Topchar(opt) != '(')
					{
						Pushchar(Topchar(opt), result);
						Pop(opt);
					}
					Pop(opt);
				}
				else
				{
					while (Compare(Topchar(opt), s[cursor]))	//�Ƚϲ����������ȼ�������optջ�еĲ�������ѹ��resultջ��ֱ�������ȵ�ǰ��������������ȼ��͵Ĳ�����Ϊֹ
					{
						Pushchar(Topchar(opt), result);
						Pop(opt);
					}
					Pushchar(s[cursor], opt);	//���ѹ�뵱ǰ�����������
				}
			}
			cursor++;
		}
		index = cursor;		//�����ֽ����ַ����������Ϊ��ǰ�α�λ��
	}
	while (!IsEmpty(opt))	//��opt��ʣ��Ĳ��������������ѹ��resultջ��
	{
		Pushchar(Topchar(opt), result);
		Pop(opt);
	}
	result = RevStack(result);  //��resultջ�е�Ԫ������
	return result;			//����resultջ��ָ��
}

Stack RevStack(Stack s)		//ջ�����ò���
{
	Stack r = CreateStack();
	Pointer p = s->next;
	while (p != NULL)
	{
		if (p->flag == true)
			Pushdata(p->Data, r);
		else
			Pushchar(p->Operator, r);
		p = p->next;
	}
	return r;
}

void PrintStack(Stack s)	//��ӡջ�е�Ԫ��
{
	Pointer p = new node;
	p = s->next;
	while (p != NULL)
	{
		if (p->flag == true)
			cout << p->Data << ' ';
		else
			cout << p->Operator << ' ';
		p = p->next;
	}
	cout << endl;
}

bool Compare(char a, char b)		//�Ƚϲ����������ȼ�
{
	if (a == '^' && (b == '^' || b == '*' || b == '/' || b == '%' || b == '+' || b == '-'))
		return true;
	else if ((a == '*' || a == '/' || a == '%') && (b == '+' || b == '-'))
		return true;
	else if ((a == '+' || a == '-') && (b == '+' || b == '-'))
		return true;
	else if ((a == '*' || a == '/' || a == '%') && (b == '*' || b == '/' || b == '%'))
		return true;
	else
		return false;
}

bool JudgeOpt(char c)		//�ж��Ƿ�Ϊ�Ϸ�������
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^')
		return true;
	return false;
}

int Factorial(int n)		//�����Ľ׳�����
{
	int result = 1;
	for (int i = 1; i <= n; i++)
	{
		result *= i;
	}
	return result;
}