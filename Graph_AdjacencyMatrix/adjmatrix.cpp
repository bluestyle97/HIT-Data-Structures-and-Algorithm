//@Filename:	adjmatrix.cpp
//@Description:	Adjacency matrix representation of graph and its search
//@Author:		Xu Jiale
//@Create Time:	2016/12/22, 16:49
//Copyright (C) 2016 HIT. All rights reserved
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

//Struct:		MTGraph
//Description:	Define a graph represented by an adjacency matrix
//Members:		vexlist: the list of vertexes
//				edge: the adjacency matrix
//				vertexnum: the amount of vertexes
//				edgenum:the amount of edges
typedef struct
{
	char *vexlist;
	int **edge;
	int vertexnum;
	int edgenum;
} MTGraph;

//array:		Judge whether the current vertex has been visited
bool * visited;

//Function:		CreateMTGraph
//Description:	Create a new graph
//Arguments:	MTGraph *: the pointer of a graph
//Return:		void
void CreateMTGraph(MTGraph *);
//Funtion:		InitVisited
//Description:	Initialize the array "visited"
//Arguments:	MTGraph *; the pointer of a graph
//Return:		void
void InitVisited(MTGraph *);
//Function:		DFSGraph1
//Description:	Depth-first search of the graph(recursive)
//Arguments:	MTGraph *: the pointer of a graph
//				int: the original vertex of search
//Return:		void
void DFSGraph1(MTGraph *, int);
//Function:		DFSGraph2
//Description:	Depth-first search of the graph(non-recursive)
//Arguments:	MTGraph *: the pointer of a graph
//				int: the original vertex of search
//Return:		void
void DFSGraph2(MTGraph *, int);
//Function:		BFSGraph
//Description:	Breadth-first search of the graph(non-recursive)
//Arguments:	MTGraph *: the pointer of a graph
//				int: the original vertex of search
//Return:		void
void BFSGraph(MTGraph *, int);

int main()
{
	cout << " ---------------------------------------- " << endl;
	cout << "|       ��ӭʹ��ͼ������ϵͳ��           |" << endl;
	cout << " ---------------------------------------- " << endl;
	MTGraph *G = new MTGraph;
	char choice = ' ';
	while (choice != '5')
	{
		cout << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "|       �밴���ּ�ѡ����Ӧ���ܣ�           |" << endl;
		cout << "|       1.��ʼ��ͼ��ʹ����������ǰ��ѡ��   |" << endl;
		cout << "|       2.��������������ݹ飩             |" << endl;
		cout << "|       3.��������������ǵݹ飩           |" << endl;
		cout << "|       4.�����������                     |" << endl;
		cout << "|       5.�˳�����                         |" << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "        ����������ѡ��";
		cin >> choice;
		cout << " ------------------------------------------ " << endl;
		switch (choice)
		{
		case '1':
			CreateMTGraph(G);
			break;
		case '2':
			InitVisited(G);
			DFSGraph1(G, 0);
			break;
		case '3':
			InitVisited(G);
			DFSGraph2(G, 0);
			break;
		case '4':
			InitVisited(G);
			BFSGraph(G, 0);
			break;
		case '5':
			cout << " ------------------------------------------ " << endl;
			cout << "|       ��лʹ��ͼ������ϵͳ               |" << endl;
			cout << " ------------------------------------------ " << endl;
			break;
		default:
			cout << " ------------------------------------------ " << endl;
			cout << "|       ���������������������룡         |" << endl;
			cout << " ------------------------------------------ " << endl;
		}
	}
	system("pause");
	return 0;
}
void CreateMTGraph(MTGraph *G)
{
	int i, j, w;
	cout << "�����붥������";
	cin >> G->vertexnum;
	cout << "�����������";
	cin >> G->edgenum;
	G->vexlist = new char[G->vertexnum];
	G->edge = new int*[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
		G->edge[i] = new int[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
		for (int j = 0; j < G->vertexnum; j++)
			G->edge[i][j] = 0;
	cout << "�������������Ϣ��";
	for (int i = 0; i < G->vertexnum; i++)
		cin >> G->vexlist[i];
	cout << "�����������Ϣ����� �յ� Ȩ�أ���" << endl;
	for (int k = 0; k < G->edgenum; k++)
	{
		cin >> i >> j >> w;
		G->edge[i][j] = w;
		G->edge[j][i] = w;
	}
}
void InitVisited(MTGraph *G)
{
	visited = new bool[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
		visited[i] = false;
}
void DFSGraph1(MTGraph *G, int i)
{
	cout << G->vexlist[i];
	visited[i] = true;
	for (int j = 0; j < G->vertexnum; j++)
		if (G->edge[i][j] > 0 && !visited[j])
			DFSGraph1(G, j);
}
void DFSGraph2(MTGraph *G, int i)
{
	int k;
	stack <int> S;
	visited[i] = true;
	S.push(i);
	while (!S.empty())
	{
		k = S.top();
		S.pop();
		cout << G->vexlist[k];
		for (int j = 0; j < G->vertexnum; j++)
			if (G->edge[k][j] > 0 && !visited[j])
			{
				visited[j] = true;
				S.push(j);
			}
	}
}
void BFSGraph(MTGraph *G, int i)
{
	int k;
	queue <int> Q;
	visited[i] = true;
	Q.push(i);
	while (!Q.empty())
	{
		k = Q.front();
		Q.pop();
		cout << G->vexlist[k];
		for (int j = 0; j < G->vertexnum; j++)
			if (G->edge[k][j] > 0 && !visited[j])
			{
				visited[j] = true;
				Q.push(j);
			}
	}
}