//
//	@Filename: lzw.cpp
//	@Function: lzw����ѹ��
//	@Author: �����
//	@Create Time: 2016/12/15, 18:59
//	@Copyright (C) 2016 HIT. All rights reserved
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <map>	//��׼ģ����map�����ֵ�
#define N 256	//ASCII�ַ���256��

using namespace std;

//
//��������	InitDictionary
//���ܣ�	��ʼ������ʱ�����ֵ䣬��256��ASCII�ַ���Ϊ������ASCII������Ϊֵ
//������	һ����׼ģ����map<string, int>�Ķ�������ã�����ʼ�����ֵ䣩
//����ֵ��	��
//
void InitDictionary(map<string, int> &);
//
//��������	InitDictionary��+1���أ�
//���ܣ�	��ʼ������ʱ�����ֵ䣬��ASCII������Ϊ������256��ASCII�ַ���Ϊֵ
//������	һ����׼ģ����map<int, string>�Ķ�������ã�����ʼ�����ֵ䣩
//����ֵ��	��
//
void InitDictionary(map<int, string> &);
//
//��������	Compress
//���ܣ�	���ı��ļ�����lzw����ѹ�������ɶ�����ѹ���ļ�
//������	string����ѹ���ļ�����
//����ֵ��	��
//
void Compress(string);
//
//��������	Decompress
//���ܣ�	���������ѹ���ļ������ɽ�ѹ���ı��ļ�
//������	string����ѹ���ļ�����
//����ֵ��	��
//
void Decompress(string);

int main()
{
	cout << " --------------------------------------- " << endl;
	cout << "|     ��ӭʹ��LZW�����ļ�ѹ��ϵͳ��     |" << endl;
	cout << " --------------------------------------- " << endl;

	//
	//���ݶ���
	//filename��	��ѹ���ļ�����������׺��
	//quit��		�˳�����ʱ�������ַ���
	//
	string filename;

	//lzw����ѹ������
	cout << " --------------------------------------- " << endl;
	cout << "|     �������ѹ���ļ���(������չ������";
	cin >> filename;
	cout << " --------------------------------------- " << endl;
	Compress(filename);
	Decompress(filename);
	system("pause");
	return 0;
}
void InitDictionary(map<string, int> &dic)
{
	//��ʼ�������ֵ�
	for (int i = 0; i < N; i++)
	{
		//stream�����ڽ�charת��Ϊstring
		stringstream stream;
		char ch = i;
		stream << ch;
		//�����ֵ�
		dic.insert(pair<string, int>(stream.str(), i));
	}
}
void InitDictionary(map<int, string> &dic)
{
	//��ʼ�������ֵ�
	for (int i = 0; i < N; i++)
	{
		//stream�����ڽ�charת��Ϊstring
		stringstream stream;
		char ch = i;
		stream << ch;
		//�����ֵ�
		dic.insert(pair<int, string>(i, stream.str()));
	}
}
void Compress(string filename)
{
	//
	//���ݶ���
	//dictionary��	�����ֵ�
	//count��		lzw���룬��ʼ��Ϊ256
	//input_char��	��һ�������ַ�
	//prefix��		ǰ׺�ַ�������ʼ��Ϊ���ַ���
	//entry��		ǰ׺�ַ���+��һ�������ַ�
	//filein��		��ѹ���ļ���
	//fileout��		������ѹ���ļ���
	//
	map<string, int> dictionary;
	unsigned int count = N;
	char input_char;
	string prefix = "";
	string input;
	string entry;
	string filein = filename + ".txt";
	string fileout = filename + ".dat";

	//��ʼ�������ֵ�
	InitDictionary(dictionary);

	//�ļ�����������Ĵ򿪼��ɹ��ж�
	ifstream is(filein, ios::in);
	if (!is.is_open())
	{
		cerr << "��ѹ���ļ���ʧ�ܣ�" << endl;
		exit(EXIT_FAILURE);
	}
	ofstream os(fileout, ios::binary);
	if (!os.is_open())
	{
		cerr << "ѹ���ļ�����ʧ�ܣ�" << endl;
		exit(EXIT_FAILURE);
	}

	//lzw�����㷨
	while (!is.eof())
	{
		stringstream stream;
		//����һ���ַ�
		is.get(input_char);
		stream << input_char;
		entry = prefix + stream.str();
		//�ж�ǰ׺+�����ַ��Ƿ��ڱ����ֵ���
		if (dictionary.find(entry) != dictionary.end())	//���ڣ���ǰ׺��Ϊ ԭǰ׺+�����ַ�
			prefix = entry;
		else											//������
		{
			os.write((char *)&dictionary[prefix], sizeof(unsigned int));		//��ǰ׺�ı���д��������ļ�
			dictionary[entry] = count++;							//��ǰ׺+�����ַ������ֵ�
			prefix = stream.str();									//��ǰ׺��Ϊ�����ַ�
		}
	}
	//�ļ�����������Ĺر�
	is.close();
	os.close();
	cout << " --------------------------------------- " << endl;
	cout << "|     �ļ�ѹ����ɣ�                    |" << endl;
	cout << " --------------------------------------- " << endl;
}
void Decompress(string filename)
{
	//
	//���ݶ���
	//dictionary��	�����ֵ�
	//count��		lzw���룬��ʼ��Ϊ256
	//input_code��	��һ���������
	//prefix��		ǰ׺�ַ�������ʼ��Ϊ���ַ���
	//input��		��һ���ַ���
	//entry��		ǰ׺�ַ���+��һ�������ַ������ַ�
	//filein��		����ѹ������ѹ���ļ���
	//filenout��	��ѹ�ļ���
	//
	map<int, string> dictionary;
	unsigned int count = N;
	unsigned int input_code;
	string prefix = " ";
	string input;
	string entry;
	string filein = filename + ".dat";
	string fileout = filename += "dcp.txt";

	//��ʼ�������ֵ�
	InitDictionary(dictionary);

	//�ļ�����������Ĵ򿪼��ɹ��ж�
	ifstream is(filein, ios::binary);
	if (!is.is_open())
	{
		cerr << "����ѹ�ļ���ʧ�ܣ�" << endl;
		exit(EXIT_FAILURE);
	}
	ofstream os(fileout, ios::out);
	if (!os.is_open())
	{
		cerr << "��д���ļ�����ʧ�ܣ�" << endl;
		exit(EXIT_FAILURE);
	}

	//�����һ�����벢����ַ����������
	is.read((char *)&input_code, sizeof(unsigned int));
	prefix = dictionary[input_code];
	os << prefix;

	//lzw�����㷨
	while (!is.eof())
	{
		//������һ������
		is.read((char *)&input_code, sizeof(unsigned int));
		//ȡ����һ���ַ���input
		input = dictionary[input_code];
		//��input��¼�������
		os << input;
		//entry�����ֵ�
		entry = prefix + input[0];
		dictionary[count++] = entry;
		//ǰ׺=input
		prefix = input;
	}
	//�ļ�����������Ĺر�
	is.close();
	os.close();
	cout << " --------------------------------------- " << endl;
	cout << "|     �ļ���ѹ��ɣ�                    |" << endl;
	cout << " --------------------------------------- " << endl;
}
