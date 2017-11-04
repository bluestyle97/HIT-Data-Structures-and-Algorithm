//huffman.cpp -- �����������������б���ѹ��
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#define N 128			//ASCII�ַ��ĸ���
#define MAXLEN 30		//�ļ����Ƶ���󳤶�

using namespace std;

//�������Ͷ���
struct htnode			//�ṹ�壺�����������
{
	char chr;			//�ַ�
	double weight;		//Ȩ��
	int lchild;			//�����
	int rchild;			//�Ҷ���
	int parent;			//˫��
};
typedef htnode huffmantree[2 * N - 1];	//�ṹ�����飺������������
struct codenode			//�ṹ�壺����������Ĵ洢�ṹ
{
	char chr;			//�洢��������ַ�
	char bit[N + 1];	//�ַ�����λ��
};
typedef codenode huffmancode[N];		//�ṹ�����飺����������
int leafcount = 0;		//ȫ�ֱ���leafcount���������������Ҷ���������������г��ֵ��ַ�����ĸ���
int nodecount = 0;		//ȫ�ֱ���nodecount������������������н�����

						//��������
void InitialTree(huffmantree &);					//��������ʼ�����������������н�����Ҷ��Ӻ�˫����Ϊ-1��Ȩ����Ϊ0��
void InitialLeaf(char *, huffmantree &);			//��������ʼ��Ҷ��㣬�������ж�ȡ�ַ���Ϣͳ��Ȩ�أ�����˳����������������
int CreateTree(char *, huffmantree &);				//��������ȡ�����������ɹ��������������ظ�����±�
int FindChar(char, huffmantree);					//�������ӹ�������������Ѱ�Ҹ����ַ����������±꣬��δ�ҵ�����-1
void FindCombineNode(int *, int *, huffmantree);	//�����������й������������Ѱ��Ȩ����С�����������Ϊ�ϲ�����
void CombineTree(int, int, huffmantree &);			//�������������������������Ϊ���������ϲ���һ���½��
void PrintTree(int, huffmantree);					//��������ӡ������������Ҷ�����ַ���Ȩ����Ϣ
void Code(huffmantree, huffmancode &);				//�������Թ��������д洢���ַ����й��������벢�������˳��洢������������
int SearchCode(char, huffmancode);					//�������ڹ���������������Ѱ���ض��ַ��Ĺ��������룬�����ظ��ַ����±�
void Compress(char *, huffmancode);					//���������������ַ����б���ѹ����д��������ļ�
void PrintCode(huffmancode);						//��������ӡ�ַ��Ĺ��������루��ѡ���ӡ�����ַ���ȫ���ַ���
void DecompressScreen(char *, int, huffmantree);	//��������ѹ���������ļ����������Ļ
void DecompressFile(char *, int, huffmantree);		//��������ѹ���������ļ��������һ���µ��ļ�

int main()											//������
{
	cout << " ------------------------------------------ " << endl;
	cout << "|     ��ӭʹ�ù��������ļ�����ѹ��ϵͳ     |" << endl;
	cout << " ------------------------------------------ " << endl;
	huffmantree T;									//T�������������
	huffmancode D;									//D�������������������
	char *filename = new char[MAXLEN];				//filename����������ļ�����
	int root = 0;									//root����������������±�
	char choice = ' ';								//choice�����ڹ���ѡ��
	while (choice != '7')
	{
		cout << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "|        �밴���ּ�ѡ����Ӧ����            |" << endl;
		cout << "|        1.��ȡ�ļ����ɹ�������            |" << endl;
		cout << "|        2.�����������Ҷ�ڵ�����          |" << endl;
		cout << "|        3.����ѹ����д���ļ�              |" << endl;
		cout << "|        4.����ַ��Ĺ�����������        |" << endl;
		cout << "|        5.�����ļ��������Ļ              |" << endl;
		cout << "|        6.�����ļ�������ļ�              |" << endl;
		cout << "|        7.�˳�����                        |" << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "         ����������ѡ��";
		cin >> choice;
		cout << " ------------------------------------------ " << endl;
		switch (choice)
		{
		case '1':		//����1����ȡ�ļ����ɹ�������
			cout << "�������ı��ļ���������������չ������";
			cin >> filename;
			root = CreateTree(filename, T);
			cout << "���������ѳɹ����ɣ�" << endl;
			break;
		case '2':		//����2�������������Ҷ�ڵ�����
			cout << "��������Ҷ��������Ϊ��" << endl;
			PrintTree(root, T);
			break;
		case '3':		//����3������ѹ����д���ļ�
			Code(T, D);
			Compress(filename, D);
			break;
		case '4':		//����4������ַ��Ĺ�����������
			PrintCode(D);
			break;
		case '5':		//����5�������ļ��������Ļ
			DecompressScreen(filename, root, T);
			break;
		case '6':		//����6�������ļ�������ļ�
			DecompressFile(filename, root, T);
			break;
		case '7':		//����7���˳�����
			cout << " ------------------------------------------ " << endl;
			cout << "|    ��лʹ�ù��������ļ�����ѹ��ϵͳ      |" << endl;
			cout << " ------------------------------------------ " << endl;
			break;
		default:		//�����������֣���������
			cout << " ------------------------------------------ " << endl;
			cout << "|       ���������������������룡         |" << endl;
			cout << " ------------------------------------------ " << endl;
		}
	}
	delete[] filename;
	return 0;
}

void InitialTree(huffmantree &T)		//��������ʼ����������
{
	for (int i = 0; i < 2 * N - 1; i++)
	{
		T[i].weight = 0;				//�����н�����Ҷ��Ӻ�˫����Ϊ-1��Ȩ����Ϊ0
		T[i].lchild = -1;
		T[i].rchild = -1;
		T[i].parent = -1;
	}
}

void InitialLeaf(char *filename, huffmantree &T)		//��������ʼ����������Ҷ��㣨����1����������ļ����ƣ�����2������������
{
	char *filename_txt = new char[MAXLEN];		//filename_txt��Ҫ�򿪵��ļ���ȫ��
	strcpy(filename_txt, filename);
	strcat(filename_txt, ".txt");		//��������ļ������������չ����.txt�������ļ�ȫ��
	char ch;							//ch�����ڴ������ж�ȡ�ַ�
	int pos;							//pos������Ѱ���ض��ַ��ڹ��������е�λ��
	ifstream is;
	is.open(filename_txt);				//�򿪴�������ļ�
	if (!is.is_open())					//�����ļ�ʧ��
	{
		cerr << "δ�ܳɹ��򿪸��ļ���" << endl;
		exit(EXIT_FAILURE);
	}
	while (!is.eof())					////�ж��Ƿ񵽴��ļ���β
	{
		is.get(ch);						//���ļ��ж�ȡһ���ַ�
		pos = FindChar(ch, T);			//�ڹ����������������ַ�
		if (pos >= 0)					//�����������ַ�������Ȩ�ؼ�1
			T[pos].weight = T[pos].weight + 1;
		else							//��δ���������ַ������ڵ�ǰ���һ��Ҷ�������λ���½�һ��Ҷ�ڵ�洢���ַ�������Ȩ�س�ʼ��Ϊ1
		{
			T[leafcount].chr = ch;
			T[leafcount].weight = 1;
			leafcount++;				//Ҷ����������1
			nodecount = leafcount;		//��ʼ��Ҷ�������н������ʼ�յ���Ҷ�����
		}
	}
	is.close();							//�ر��ļ�
}

int CreateTree(char *filename, huffmantree &T)		//��������ȡ�ļ����ɹ�������������1����������ļ����ƣ�����2������������
{
	int *a = new int;					//������ָ��a��b�����ڴ洢��ǰȨ����С�����������±�
	int *b = new int;
	int l, r, root;						//l��f�����ڴ洢ָ��a��bָ��������±��Ա���н�� root���������ɵĹ��������ĸ�����±�
	InitialTree(T);						//��ʼ����������
	InitialLeaf(filename, T);			//��ʼ��Ҷ���
	while (nodecount < 2 * leafcount - 1)		//���������=2*Ҷ�������-1ʱ��˵�������������������
	{
		FindCombineNode(a, b, T);		//Ѱ�ҵ�ǰ���н����Ȩ����С���������������±�ֱ����ָ��a��bָ��ĵ�ַ��
		l = *a;
		r = *b;
		CombineTree(l, r, T);			//�Խ����кϲ�������һ���½��
	}
	delete a;							//ɾ��ָ��a��b
	delete b;
	root = nodecount - 1;
	return root;						//���ظ�����±�
}

int FindChar(char c, huffmantree T)		//�������ڹ��������������ض��ַ����������±꣨����1���������ַ�������2������������
{
	for (int i = 0; i < leafcount; i++)
	{
		if (T[i].chr == c)
			return i;
	}
	return -1;							//��δ�ҵ����򷵻�-1
}

void FindCombineNode(int *a, int *b, huffmantree T)		//�������ڵ�ǰ���н��������Ȩ����С������������1��2��ָ�봫���Ա�õ��±꣬����3������������
{
	int mina, minb, tmp;				//mina��Ȩ����С�Ľ����±� minb��Ȩ�ش�С�Ľ����±� temp�����ڽ�������
	for (int j = 0; j < nodecount; j++)					//��mina��ʼ��Ϊ��ǰ�������������е�һ����δ���ϲ����Ľ���±�
		if (T[j].parent == -1)
		{
			mina = j;
			break;
		}
	for (int k = mina + 1; k < nodecount; k++)			//��minb��ʼ��Ϊ��ǰ�������������еڶ�����δ���ϲ����Ľ���±�
		if (T[k].parent == -1)
		{
			minb = k;
			break;
		}
	if (T[mina].weight >= T[minb].weight)		//��mina��Ȩ�ش��ڵ���minb���򽻻����Ա�֤mina����С��minb�Ǵ�С
	{
		tmp = mina;
		mina = minb;
		minb = tmp;
	}
	int i = 0;
	while (i < nodecount)						//�������������������ҵ�Ȩ����С���������
	{
		if (T[i].parent == -1)					//�жϽ���Ƿ��ѱ��ϲ���
		{
			if (T[i].weight <= T[mina].weight)			//����ǰ���Ȩ��С��mina���򽫸ý���±긳��mina
				mina = i;
			else if (T[i].weight <= T[minb].weight)		//��������ǰ���Ȩ��С��minb���򽫸ý���±긳��minb
				minb = i;
			i++;
		}
		else
			i++;
	}
	*a = mina;			//������ɺ�mina��minb����Ȩ����С�����������±꣬����ֱ�洢��ָ��a��bָ��ĵ�ַ
	*b = minb;
}

void CombineTree(int a, int b, huffmantree &T)		//�������ϲ���㣨����1:��2�����ϲ�����������±꣬����3������������
{													//�½ڵ��±�Ϊ��ǰ�����������nodecount
	T[nodecount].weight = T[a].weight + T[b].weight;//�½��Ȩ��Ϊ�������ϲ����Ȩ�صĺ�
	T[nodecount].lchild = a;						//�½��������±�Ϊa
	T[nodecount].rchild = b;						//�½���Ҷ����±�Ϊb
	T[a].parent = nodecount;						//�±�Ϊa��b�Ľ���˫�׽���±�Ϊ�½����±꣬��nodecount
	T[b].parent = nodecount;
	nodecount++;									//�������nodecount����1
}

void PrintTree(int root, huffmantree T)				//��������ӡ��������������Ҷ�����Ϣ������1����������������±꣬����2������������
{
	int i = root;									//��ݹ��������������ͬ������ֻ�е���Ҷ���ʱ�Ŵ�ӡ�ַ���Ȩ����Ϣ
	if (i == -1)
		return;
	if (T[i].lchild == -1 && T[i].rchild == -1)
		cout << T[i].chr << "  " << T[i].weight << endl;
	PrintTree(T[i].lchild, T);
	PrintTree(T[i].rchild, T);
}

void Code(huffmantree T, huffmancode &D)		//���������ӷ����б��벢������������������У�����1����������������2���������������飩
{
	int i, posa, posb;
	for (i = 0; i < leafcount; i++)				//��leafcount��Ҷ����ַ����б���
	{
		posa = i;								//pos��ʼ��Ϊ��ǰҶ����±�
		int len = 0;							//len����ʾ���������볤��
		char hcode[N + 1];						//���飺�洢������������
		D[i].chr = T[i].chr;					//����ǰҶ����ַ������������������
		while (T[posa].parent != -1)			//�ж��Ƿ��ƶ��������
		{
			posb = T[posa].parent;				//��Ҷ��������˫�׽���ƶ�
			if (T[posb].lchild == posa)			//��posa��posb������ӣ������������д��һ��0
				hcode[len] = '0';
			else								//��posa��posb���Ҷ��ӣ������������д��һ��1
				hcode[len] = '1';
			posa = posb;						//��˫�׽���ƶ�
			len++;
		}
		for (int j = 0; j < len; j++)			//��hcode���ô�����������������м��õ���ȷ�Ĺ���������
			D[i].bit[j] = hcode[len - j - 1];
		D[i].bit[len] = '\0';					//������ַ���ʶ�����β
	}
	cout << "������ɣ�" << endl;
}

int SearchCode(char c, huffmancode D)			//�������ڹ��������������дӲ����ض��ַ����룬�������±꣨����1���������ַ�������2���������������飩
{
	for (int i = 0; i < leafcount; i++)
		if (D[i].chr == c)
			return i;
	return -1;
}

void Compress(char *filename, huffmancode D)	//���������ļ�����ѹ����д��������ļ�������1����ѹ���ļ���������2���������������飩
{
	char *filename_txt = new char[MAXLEN];
	strcpy(filename_txt, filename);
	strcat(filename_txt, ".txt");				//�ڴ�ѹ���ļ�������׺��.txt���õ���ѹ���ļ�ȫ��
	char *filename_dat = new char[MAXLEN];
	strcpy(filename_dat, filename);
	strcat(filename_dat, ".dat");				//�ڴ�ѹ���ļ�������׺��.dat���õ���д��Ķ������ļ�ȫ��
	ifstream is;
	ofstream os;
	char ch;				//ch�����ڶ�ȡ�ַ�
	int index;				//index��ĳ�ַ��ڹ��������������е��±�
	int count = 0;			//count�����ڼ�¼��ȡ�Ĺ����������λ��
	unsigned char set;		//�޷����ַ�set������Ϊһ���ֽڣ�8bit��������λ����������
	set &= 0;				//����set��ʼ��Ϊ00000000
	is.open(filename_txt);	//�򿪴�ѹ���ļ�
	if (!is.is_open())
	{
		cerr << "���ı��ļ�ʧ�ܣ�" << endl;
		exit(EXIT_FAILURE);
	}
	os.open(filename_dat, ios::binary);		//�򿪴�д��������ļ�
	if (!os.is_open())
	{
		cerr << "�򿪶������ļ�ʧ�ܣ�" << endl;
		exit(EXIT_FAILURE);
	}
	while (!is.eof())		//�ж��Ƿ��ȡ���ļ���β
	{
		is.get(ch);			//��ȡһ���ַ�
		index = SearchCode(ch, D);
		int pos = 0;		//pos����ȡ������������α�
		while (D[index].bit[pos] != '\0')		//���Ѷ�ȡһ���ַ��Ĺ��������������λ����ѭ����������ȡ��һ���ַ�
		{
			set <<= 1;		//����set����һλ
			count++;		//������count��1
			if (D[index].bit[pos] == '1')		//����ǰ��ȡ���Ĺ���������λΪ1����set���λ��Ϊ1
				set |= 1;
			if (count == 8)	//��������count����8����˵���Ѿ�����8λ
			{
				os.write((char *)&set, sizeof(char));		//����ǰ����set�е�8��λд��������ļ�
				set &= 0;	//���set���Զ�ȡ��һ��8λ
				count = 0;	//��������0
			}
			pos++;			//��ȡ�������������һλ
		}
	}
	set <<= (8 - count);	//��ʣ��λ���油0�չ�8λд��������ļ�
	os.write((char *)&set, sizeof(char));
	cout << "�ļ�ѹ����ɣ��뵽�ļ� " << filename_dat << " �в鿴��" << endl;
	is.close();				//�ر��ļ�
	os.close();
}

void PrintCode(huffmancode D)		//��������ӡ������������Ϣ���������������������飩
{
	char choice;
	cout << " ------------------------------------------ " << endl;
	cout << "|        �밴���ּ�ѡ����Ӧ����            |" << endl;
	cout << "|        1.��ѯ�����ַ�����������          |" << endl;
	cout << "|        2.��ѯȫ���ַ�����������          |" << endl;
	cout << " ------------------------------------------ " << endl;
	cout << "         ����������ѡ��";
	cin >> choice;
	if (choice == '1')		//����1����ӡ�ض��ַ�����������
	{
		char c;
		cout << "�����������ѯ���ַ���";
		cin >> c;
		for (int i = 0; i < leafcount; i++)
		{
			if (D[i].chr == c)
			{
				cout << "�ַ�" << c << "�ı�����Ϊ�� ";
				puts(D[i].bit);
				return;
			}
		}
		cout << "δ���ҵ����ַ���" << endl;
	}
	else if (choice == '2')	//����2����ӡ�����ַ�����������
	{
		cout << "ȫ���ַ��Ĺ���������Ϊ��" << endl;
		for (int i = 0; i < leafcount; i++)
		{
			cout << D[i].chr << "�� ";
			puts(D[i].bit);
		}
	}
	else
		cout << "������������" << endl;
}

void DecompressScreen(char *filename, int root, huffmantree T)		//��������ѹ���������ļ����������Ļ������1������ѹ�Ķ������ļ����ƣ�����2������������
{
	char *filename_dat = new char[MAXLEN];
	strcpy(filename_dat, filename);
	strcat(filename_dat, ".dat");		//�ڴ���ѹ�ļ�������׺��.dat���õ�����ѹ�Ķ������ļ�ȫ��
	int pos = root;						//pos�����ڱ��������������α�
	unsigned char set;					//�޷����ַ�set������Ϊһ���ֽڣ�8bit��������λ����������
	ifstream is;
	is.open(filename_dat, ios::binary);	//�򿪴���ѹ�ļ�
	if (!is.is_open())
	{
		cerr << "��ѹ���ļ�ʧ�ܣ�" << endl;
		exit(EXIT_FAILURE);
	}
	while (!is.eof())					//�ж��Ƿ��ȡ���������ļ���β
	{
		is.read((char *)&set, sizeof(char));	//���ļ��ж�ȡһ���ֽڣ�8λ�������Ʊ����������set��
		for (int i = 0; i < 8; i++)		//���ݶ����Ʊ��������������Ѱ��Ҷ���
		{
			if ((set & 0x80) == 0)		//��set&10000000=00000000����set���λΪ0��������������������ƶ�
				pos = T[pos].lchild;
			else						//��set&10000000=00000001����set���λΪ1���������������Ҷ����ƶ�
				pos = T[pos].rchild;
			set <<= 1;		//set����һλ���ж���һλ
			if (T[pos].lchild == -1 && T[pos].rchild == -1)		//���ƶ���Ҷ����򽫸�Ҷ����е��ַ��������Ļ
			{
				cout << T[pos].chr;
				pos = root;				//pos���³�ʼ��Ϊ����������һ�α���
			}
		}
	}
	is.close();		//�ر��ļ�
}

void DecompressFile(char *filename, int root, huffmantree T)	//����һ����������ͬ��ֻ�ǽ�������������ļ�����ѹ���ļ���dcp.txt����������Ļ��
{
	char *filename_dat = new char[MAXLEN];
	char *filename_txt = new char[MAXLEN];
	strcpy(filename_dat, filename);
	strcat(filename_dat, ".dat");
	strcpy(filename_txt, filename);
	strcat(filename_txt, "dcp.txt");
	int pos = root;
	unsigned char set;
	ifstream is;
	ofstream os;
	is.open(filename_dat, ios::binary);
	if (!is.is_open())
	{
		cerr << "��ѹ���ļ�ʧ�ܣ�" << endl;
		exit(EXIT_FAILURE);
	}
	os.open(filename_txt);
	if (!os.is_open())
	{
		cerr << "�򿪽�ѹ���ļ�ʧ�ܣ�" << endl;
		exit(EXIT_FAILURE);
	}
	while (!is.eof())
	{
		is.read((char *)&set, sizeof(char));
		for (int i = 0; i < 8; i++)
		{
			if ((set & 0x80) == 0)
				pos = T[pos].lchild;
			else
				pos = T[pos].rchild;
			set <<= 1;
			if (T[pos].lchild == -1 && T[pos].rchild == -1)
			{
				os << T[pos].chr;
				pos = root;
			}
		}
	}
	is.close();
	os.close();
	cout << "�ļ���ѹ����ɣ��뵽�ı��ļ� " << filename_txt << " �в鿴��" << endl;
}