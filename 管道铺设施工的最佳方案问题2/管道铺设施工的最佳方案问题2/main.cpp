#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{//�߱�ڵ�
	char adjvex; //�ڽӵ���
	double value;//����ֵ
	struct node *next;//ָ����һ���ڽӵ��ָ����
}EdgeNode;
typedef struct vnode
{
	char vertex;
	EdgeNode *firstedge;
}VertexNode;
typedef VertexNode AdjList[26];
typedef struct
{
	AdjList adjlist;
	int n,e;
}ALGraph;

void CreateALGraph(ALGraph *G)
{
	int i,j,k;
	char a, b;
	double length;
	EdgeNode *s;
	printf("�����붥�����ͱ���(��ʽΪ��������,����)��");
	scanf("%d,%d",&(G->n),&(G->e));
	for (i = 0; i < G->n; i++)
	{
		G->adjlist[i].vertex='A'+i;
		G->adjlist[i].firstedge = NULL;
	}
	printf("������ߵ���Ϣ����ʽΪ��A,B,32.8����\n");
	for (k = 0; k < G->e; k++)
	{
		scanf("\n%c,%c,%lf", &a, &b, &length);
		i = a - 'A';
		s = (EdgeNode*)malloc(sizeof(EdgeNode));
		s->adjvex = b;
		s->value = length;
		s->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = s;
	}
	//��������
	//G->n = 9;
	//G->e = 15;
	//for (i = 0; i < G->n; i++)
	//{
	//	G->adjlist[i].vertex='A'+i;
	//	G->adjlist[i].firstedge = NULL;
	//}
	//char v1[15] =    { 'A', 'A', 'A',  'A', 'B','C', 'C','C', 'D', 'D', 'E', 'E', 'F', 'G', 'H' };
	//char v2[15] =    { 'B', 'C', 'H',  'I', 'C','D', 'E','G', 'E', 'F', 'F', 'G', 'I', 'H', 'I' };
	//double len[15] = { 32.8,44.6,12.1,18.2,5.9,21.3,41.1,56.4,67.3,98.7,85.6,10.5,79.2,52.5,8.7 };
	//for (i = 0; i < G->e; i++)
	//{
	//	s = (EdgeNode*)malloc(sizeof(EdgeNode));
	//	s->adjvex = v2[i];
	//	s->value = len[i];
	//	s->next = G->adjlist[v1[i]-'A'].firstedge;
	//	G->adjlist[v1[i]-'A'].firstedge = s;
	//}
}

int IsInVnew(char *Vnew,int n, char vertex)
{
	int r=0;
	for (int i = 0; i<n; i++)
	{
		if (*(Vnew + i) == vertex)
		{
			r = 1;
			break;
		}
	}
	return r;
}

EdgeNode GetMinEdge(ALGraph *p, char *Vnew, char *x,char *y)
{
	int i;
	EdgeNode t;
	EdgeNode *s=NULL;
	double min = 1e20;
	for(i=0;i<p->n;i++)
		if (IsInVnew(Vnew, p->n, p->adjlist[i].vertex))
		{
			s = p->adjlist[i].firstedge;
			while (s != NULL)
			{
				if (!IsInVnew(Vnew, p->n, s->adjvex))
					if (s->value < min)
					{
						min = s->value;
						*x = p->adjlist[i].vertex;
						*y = s->adjvex;
						t = *s;
					}
				s = s->next;
			}
		}
		else
		{
			s = p->adjlist[i].firstedge;
			while (s != NULL)
			{
				if (IsInVnew(Vnew, p->n, s->adjvex))
					if (s->value < min)
					{
						min = s->value;
						*x = p->adjlist[i].vertex;
						*y = s->adjvex;
						t = *s;
					}
				s = s->next;
			}
		}
	return t;
}

ALGraph GetMST(ALGraph *p)
{
	int i, j;
	char x, y;
	EdgeNode t;
	EdgeNode *s;
	ALGraph Gnew;
	//��ʼ��GnewΪһ���ޱߵ�ͼ
	Gnew.e = 0;
	Gnew.n = p->n;
	for(i = 0; i < p->n; i++)
	{
		Gnew.adjlist[i].vertex = 'A'+i;
		Gnew.adjlist[i].firstedge = NULL;
	}
	
	char *Vnew = (char*)malloc((p->n) * sizeof(char));
	for (i = 0; i < p->n; i++)
		*(Vnew + i) = NULL;
	*Vnew = 'A';
	while ( Gnew.e  < Gnew.n - 1) //������û��n-1ʱ
	{
		t=GetMinEdge(p, Vnew, &x, &y);
		Gnew.e++;
		if (IsInVnew(Vnew, p->n, x))
			*(Vnew + Gnew.e) = y;
		else
			*(Vnew + Gnew.e) = x;
		s = (EdgeNode*)malloc(sizeof(EdgeNode));
		s->adjvex = y;
		s->value = t.value;
		s->next = Gnew.adjlist[x-'A'].firstedge;
		Gnew.adjlist[x-'A'].firstedge = s;
	}

	return Gnew;
}
void Print(ALGraph *p)
{
	int i;
	double sum = 0.0;
	EdgeNode *s;
	for (i = 0; i < p->n; i++)
	{
		s = p->adjlist[i].firstedge;
		while (s != NULL)
		{
			printf("(%c,%c)\n", p->adjlist[i].vertex, s->adjvex);
			sum += s->value;
			s = s->next;
		}
	}
	printf("�ܷ���Ϊ��%f\n", sum);
}
int main()
{
	time_t rawtime;
	struct tm * timeinfo;

	printf("ʵ�����ƣ�ʵ�������ܵ�����ʩ����ѷ�������\n");
	printf("ѧ�ţ�031620115\n");
	printf("��������ʫ��\n");
	printf("==================================\n");
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("�������п�ʼ��Current local time and date: %s", asctime(timeinfo));

	ALGraph G,MST;
	CreateALGraph(&G);
	MST=GetMST(&G);
	printf("��С��������Ҫ�ı�Ϊ��\n");
	Print(&MST);

	printf("=======================\n");
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("�������н�����Current local time and date: %s", asctime(timeinfo));

	system("pause");
	return 0;
}