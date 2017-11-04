//stackshare.cpp -- ��ջ����һ�οռ估��ɾ���㷨
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#define N 80

using namespace std;

struct stacknode		//ջ���
{
	char data;			//����
	int next;			//��һ���
};

void ShareStack(stacknode[]);		//���������ļ��ж�ȡ���ݳ�ʼ������ջʹ�乲��һ�δ洢�ռ�
bool IsEmpty(int, stacknode[]);		//�������ж�ջ�Ƿ�Ϊ��
void Pop(int, stacknode[]);			//����������ջ��Ԫ��
void PrintStack(int, stacknode[]);	//��������ӡջ��Ԫ��

int main()
{
	stacknode stk[N];		//ʹ�þ�̬����洢ջ����Ϣ
	char choice = ' ';		//choice��ѡ����
	int number;				//number��ջ�ı�ţ�1,2,3��
	while (choice != '4')
	{
		cout << endl;
		cout << "�밴���ּ�ѡ���ܣ�" << endl;		//��ӡ�˵�
		cout << "1.��ʼ��ջԪ��" << endl;
		cout << "2.����ջ��Ԫ��" << endl;
		cout << "3.��ӡջ��Ԫ��" << endl;
		cout << "4.�˳�����" << endl;
		cin >> choice;
		switch (choice)
		{
		case '1':		//��ʼ��ջ
			ShareStack(stk);
			cout << "ջ��ʼ����ɣ�" << endl;
			break;
		case '2':		//������ѡջ��ջ��Ԫ��
			cout << "���������뵯����ջ���(1,2,3)��";
			cin >> number;
			Pop(number, stk);
			break;
		case '3':		//��ӡջ��Ԫ��
			cout << "�����������ӡ��ջ���(1,2,3)��";
			cin >> number;
			PrintStack(number, stk);
			break;
		case '4':		//�˳�����
			cout << "��л����ʹ�ã��ټ���" << endl;
			break;
		default:
			cout << "��������������������룡" << endl;
		}
	}
	cin.get();
	return 0;
}

void ShareStack(stacknode stk[])
{
	char input;		//input�����ڶ�ȡ�ַ�����
	int top = 3;	//top����ǰ�ѳ�ʼ�������ջ����±�
	for (int i = 0; i < 3; i++)		//��ǰ���������Ա�ֱ���Ϊ����ջ��ջ��Ԫ��
		stk[i].next = 0;
	for (int i = N - 1; i >= 3; i--) //��ʼ���洢�ռ䣬�����һ��Ԫ��Ϊջ����ջ����������
		stk[i].next = i - 1;
	stk[N - 1].next = 0;		//��ջջ��Ԫ�ص���һ������ʼ��Ϊ0
	ifstream is;
	is.open("input.txt");		//���ļ�
	if (!is.is_open())			//���ļ���ʧ��
	{
		cerr << "���ļ�ʧ�ܣ�" << endl;
		exit(EXIT_FAILURE);
	}
	while (!is.eof() && top < N)	//���ļ��ж�ȡջ������
	{
		is.get(input);		//���ļ��ж�ȡһ���ַ�
		stk[top].data = input;		//����ȡ���ַ��洢���洢�ռ���top��㴦
		if ('0' <= input && input <= '9')	//�����ַ������֣�����ѹ��ջ��Ϊ�±�0Ԫ�ص�ջ
		{
			stk[top].next = stk[0].next;
			stk[0].next = top;
		}
		else if ('a' <= input && input <= 'z' || 'A' <= input && input <= 'Z')
		{									//�����ַ�����ĸ������ѹ��ջ��Ϊ�±�1Ԫ�ص�ջ
			stk[top].next = stk[1].next;
			stk[1].next = top;
		}
		else								//�����ַ����������ţ�����ѹ��ջ��Ϊ�±�2Ԫ�ص�ջ
		{
			stk[top].next = stk[2].next;
			stk[2].next = top;
		}
		top++;		//topָ����һ��δ��ʼ�����
	}
	if (top < N - 1)		//���洢�ռ�δ������top��ָ����һ����ʼ��Ϊ0����ʾ�ý�㲻���κ�һ��ջ��
		stk[top].next = 0;
	is.close();		//�ر��ļ�
}

bool IsEmpty(int number, stacknode stk[])
{
	return stk[number].next == 0;		//�жϱ��Ϊnumber��ջ����ջ��Ϊnumber-1��ջ���Ƿ�Ϊ��
}

void Pop(int number, stacknode stk[])	//�������Ϊnumber��ջ��ջ��Ԫ��
{
	int index;							//index���洢ջ��Ԫ�ؽ���±�
	if (IsEmpty(number - 1, stk))		//��ջ�ѿգ��򲻵�ջ
	{
		cout << "��ջ�ѿգ�" << endl;
		return;
	}
	index = stk[number - 1].next;		//�ҵ�ջ��Ԫ��
	stk[number - 1].next = stk[index].next;		//��ջ����
	stk[index].next = stk[N - 1].next;			//��ɾ���ռ����������
	stk[N - 1].next = index;
	cout << "��Ԫ���ѵ�����" << endl;
}

void PrintStack(int number, stacknode stk[])
{
	int pos = number - 1;		//pos��ջ��Ԫ���±�
	int count = 1;
	cout << "ջ��Ԫ�����£�" << endl;
	do
	{
		pos = stk[pos].next;	//��ӡջ������Ԫ��
		if (pos != 0)
			cout << setw(2) << pos << ":" << setw(2) << stk[pos].data;
		if (count % 4 == 0)		//��ӡ��ʽ���±꣺���� ÿ�����4��ջԪ��
			cout << endl;
		else
			cout << "\t";
	} while (pos != 0 && count++);
	cout << endl << "ջ��Ԫ�ش�ӡ��ϣ�" << endl;
}