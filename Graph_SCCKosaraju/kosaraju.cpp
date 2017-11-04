//kosaraju.cpp -- Ѱ������ͼ��ǿ��ͨ����
#include <iostream>
#include <stack>

using namespace std;

typedef struct node		//�߽��
{
	int adjvex;			//�յ����
	node *next;			//��һ���
} EdgeNode;
typedef struct			//������
{
	char data;			//��������
	EdgeNode *firstedge;//��
} VertexNode;
typedef struct			//ͼ���ڽӱ��ʾ
{
	VertexNode *vexlist;//�����б�
	int vertexnum;		//������
	int edgenum;		//����
} AdjGraph;

bool *visited;			//����visited����ʶ����Ƿ񱻷���
stack<int> order;		//ջorder����¼ÿ�����ķ������ʱ��

void CreateAdjGraph(AdjGraph *, AdjGraph *);//����������һ������ͼG��ͬʱ�õ�������߷����ͼGrev
void InitVisited(AdjGraph *);				//��������ʼ��visited����
void FillOrder(AdjGraph *, int);			//������������ͼ������������������õ������ķ�������order
void DFSGraph(AdjGraph *, int);				//������������ͼ������������������õ���ǿ��ͨ������������
void PrintSC(AdjGraph *, AdjGraph *);		//�������ж�����ͼ�Ƿ�Ϊǿ��ͨͼ���������������ǿ��ͨ������������

int main()
{
	AdjGraph *G = new AdjGraph;
	AdjGraph *Grev = new AdjGraph;
	CreateAdjGraph(G, Grev);
	PrintSC(G, Grev);
	cin.get();
	cin.get();
	return 0;
}
void CreateAdjGraph(AdjGraph * G, AdjGraph *Grev)
{
	int head, tail;							//�����ţ��յ����
	cout << "�����붥������";
	cin >> G->vertexnum;
	Grev->vertexnum = G->vertexnum;
	cout << "�����������";
	cin >> G->edgenum;
	Grev->edgenum = G->edgenum;
	G->vexlist = new VertexNode[G->vertexnum];
	Grev->vexlist = new VertexNode[Grev->vertexnum];
	cout << "�������������Ϣ��";
	for (int i = 0; i < G->vertexnum; i++)	//�����������ݣ����ƣ�
	{
		cin >> G->vexlist[i].data;
		Grev->vexlist[i].data = G->vexlist[i].data;
		G->vexlist[i].firstedge = NULL;
		Grev->vexlist[i].firstedge = NULL;
	}
	cout << "�����������Ϣ����� �յ㣩��" << endl;
	for (int i = 0; i < G->edgenum; i++)
	{
		cin >> head >> tail;
		EdgeNode *p = new EdgeNode;		//ͬʱ��ʼ��G������ת��ͼGrev���ڽӱ�
		p->adjvex = tail;
		p->next = G->vexlist[head].firstedge;
		G->vexlist[head].firstedge = p;
		EdgeNode *q = new EdgeNode;
		q->adjvex = head;
		q->next = Grev->vexlist[tail].firstedge;
		Grev->vexlist[tail].firstedge = q;
	}
}
void InitVisited(AdjGraph *G)	//Ϊvisited�������ռ䲢����������Ԫ�س�ʼ��Ϊfalse
{
	visited = new bool[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
		visited[i] = false;
}
void FillOrder(AdjGraph *G, int i)	//�ӽ��i��ʼ�������������
{
	EdgeNode *p;
	visited[i] = true;
	p = G->vexlist[i].firstedge;
	while (p != NULL)
	{
		if (!visited[p->adjvex])
			FillOrder(G, p->adjvex);
		p = p->next;
	}
	order.push(i);	//ÿ����������ɺ󣨻��ݷ���ʱ������ѹ��ջorder��
}
void DFSGraph(AdjGraph *G, int i)	//�ӽ��i��ʼ�������������
{
	EdgeNode *p;
	visited[i] = true;
	cout << G->vexlist[i].data << " ";	//����������
	p = G->vexlist[i].firstedge;
	while (p != NULL)
	{
		if (!visited[p->adjvex])
			DFSGraph(G, p->adjvex);
		p = p->next;
	}
}
void PrintSC(AdjGraph *G, AdjGraph *Grev)
{
	int count = 0;		//count�����ڼ�¼��������������еĴ�������count>1��˵��һ���������ܱ������н�㣬������ͼ��ǿ��ͨ
	InitVisited(G);		//��ʼ��visited����
	for (int i = 0; i < G->vertexnum; i++)		//�ӽ��0��ʼ��ԭͼ������������������õ�����������
		if (!visited[i])
			FillOrder(G, i);
	cout << "����ͼ�и�ǿ��ͨ�����еĶ������£�" << endl;
	for (int i = 0; i < G->vertexnum; i++)		//���³�ʼ��visited����׼�����еڶ��������������
		visited[i] = false;
	while (!order.empty())		//��ջorderջ����㿪ʼ������ֱ��ջΪ��
	{
		int k = order.top();
		order.pop();
		if (!visited[k])		//��ӡ��ǿ��ͨ���������Ķ�������
		{
			DFSGraph(Grev, k);
			cout << endl;
		}
	}
}
