#include <stdio.h>
#include<stdlib.h>
#include<time.h>
//链式存储结构体
#define SLNODE struct node1
SLNODE{
	int number;
	int password;
	int isin;
	SLNODE *next;
};
//顺序存储结构体
#define SNODE struct node2
SNODE{
	int number;
	int password;
	int isin;
};
//创建循环链表
SLNODE* create(SLNODE *head,int n)
{
	SLNODE *p,*s;
	int i=1;
	int x;
	head=(SLNODE*)malloc(sizeof(SLNODE));
	head->next=NULL;
	p=head;
	printf("请依次输入每个人的密码：\n");
	for(i=1;i<=n;i++)
	{
		scanf("%d",&x);
		s=(SLNODE*)malloc(sizeof(SLNODE));
		s->number=i;
		s->password=x;
		s->isin=1;
		if(head->next==NULL)
			head->next=s;
		else
			p->next=s;
		p=s;
	}
	p->next=head->next;
	return head;
}
//链式求解
void Josephus_solve(SLNODE* head,int n,int m)
{
	SLNODE *p,*q;
	int count=0;
	int i;
	p=head;
	printf("链式求解结果：\n");
	while(count<n)
	{
		i=0;
		while(i<m)
		{
			p=p->next;
			if(p->isin==1)
				i++;
		}
		printf("%d ",p->number);
		p->isin=0;
		m=p->password;
		count++;
	}
	printf("\n");
}
//顺序求解
void Josephus_solve2(SNODE * rawdata,int n,int m)
{
	int count=0;
	int i,j=-1;
	printf("顺序求解结果：\n");
	while(count<n)
	{
		i=0;
		while(i<m)
		{
			j=(j+1)%n;
			if(rawdata[j].isin==1)
				i++;
		}
		printf("%d ",rawdata[j].number);
		rawdata[j].isin=0;
		m=rawdata[j].password;
		count++;
	}
	printf("\n");
}
int main()
{
	time_t rawtime;
	struct tm * timeinfo;

	printf("实验名称：实验一、约瑟夫斯问题求解\n");
	printf("学号：031620115\n");
	printf("姓名：成诗鹏\n");
	printf("=======================\n");
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	printf ("程序运行开始，Current local time and date: %s", asctime(timeinfo));

	int n;
	printf("请输入人数n(n>0)：");
	scanf("%d",&n);
	SLNODE *head=NULL;
	head=create(head,n);
	int m;
	do{
		printf("请输入m的初值：");
		scanf("%d",&m);
	}while(m<=0);
	//链式存储求解
	Josephus_solve(head,n,m);

	//顺序存储求解
	//转存数据
	SNODE *rawdata = (SNODE*)malloc(n * sizeof(SNODE));
	SLNODE *p=head;
	p=p->next;
	int i=0;
	do
	{
		rawdata[i].isin=1;
		rawdata[i].number=p->number;
		rawdata[i].password=p->password;
		i++;
		p=p->next;
	}while(p!=head->next);
	//求解
	Josephus_solve2(rawdata,n,m);
	//释放空间
	SLNODE *q = head->next;
	do
	{
		p = head;
		head = head->next;
		free(p);
	}while (head != q);
	free(rawdata);
	printf("=======================\n");
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	printf ("程序运行结束，Current local time and date: %s", asctime(timeinfo));


	system("pause");
	return 0;
}