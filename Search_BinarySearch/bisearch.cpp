//@Filename: bisearch.cpp
//@Function: binary search
//@Author: Xu Jiale
//@Create Time: 2016/12/19, 19:14
//Copyright (C) 2016 HIT. All rights reserved.

#include <iostream>
#define MAXSIZE 100

using namespace std;

struct records
{
	int key;
};
void Sort(records[], int);
int BinarySearch(records[], int, int);

int main()
{
	records array[MAXSIZE];
	int count = 0;
	int inputnumber, searchkey, position;
	cout << "����������Ԫ�أ�";
	while (cin >> inputnumber && count < MAXSIZE)
		array[count++].key = inputnumber;
	Sort(array, count);
	cout << "������Ҫ���ҵ�ֵ��";
	cin.clear();
	cin >> searchkey;
	position = BinarySearch(array, searchkey, count);
	if (position != -1)
		cout << "���ҳɹ�����Ԫ�ص��±�Ϊ" << position << endl;
	else
		cout << "����ʧ�ܣ�" << endl;
	system("pause");
	return 0;
}

void Sort(records arr[], int arrsize)
{
	int temp;
	for (int i = 0; i < arrsize - 1; i++)
		for (int j = i + 1; j < arrsize; j++)
			if (arr[i].key > arr[j].key)
			{
				temp = arr[i].key;
				arr[i].key = arr[j].key;
				arr[j].key = temp;
			}
}
int BinarySearch(records arr[], int key, int arrsize)
{
	int low, up, mid;
	low = 0;
	up = arrsize - 1;
	while (low <= up)
	{
		mid = (low + up) / 2;
		if (arr[mid].key == key)
			return mid;
		else if (arr[mid].key > key)
			up = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}