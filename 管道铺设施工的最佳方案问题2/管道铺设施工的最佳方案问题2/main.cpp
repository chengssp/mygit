#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{//边表节点
	char adjvex; //邻接点域
	double value;//距离值
	struct node *next;//指向下一个邻接点的指针域
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
	printf("请输入顶点数和边数(格式为：顶点数,边数)：");
	scanf("%d,%d",&(G->n),&(G->e));
	for (i = 0; i < G->n; i++)
	{
		G->adjlist[i].vertex='A'+i;
		G->adjlist[i].firstedge = NULL;
	}
	printf("请输入边的信息（格式为：A,B,32.8）：\n");
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
	//调试用例
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
	//初始化Gnew为一个无边的图
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
	while ( Gnew.e  < Gnew.n - 1) //当边数没到n-1时
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
	printf("总费用为：%f\n", sum);
}
int main()
{
	time_t rawtime;
	struct tm * timeinfo;

	printf("实验名称：实验三、管道铺设施工最佳方案问题\n");
	printf("学号：031620115\n");
	printf("姓名：成诗鹏\n");
	printf("==================================\n");
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("程序运行开始，Current local time and date: %s", asctime(timeinfo));

	ALGraph G,MST;
	CreateALGraph(&G);
	MST=GetMST(&G);
	printf("最小生成树需要的边为：\n");
	Print(&MST);

	printf("=======================\n");
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("程序运行结束，Current local time and date: %s", asctime(timeinfo));

	system("pause");
	return 0;
}