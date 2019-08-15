#include <stdio.h>
#include<stdlib.h>
#include<time.h>
//��ʽ�洢�ṹ��
#define SLNODE struct node1
SLNODE{
	int number;
	int password;
	int isin;
	SLNODE *next;
};
//˳��洢�ṹ��
#define SNODE struct node2
SNODE{
	int number;
	int password;
	int isin;
};
//����ѭ������
SLNODE* create(SLNODE *head,int n)
{
	SLNODE *p,*s;
	int i=1;
	int x;
	head=(SLNODE*)malloc(sizeof(SLNODE));
	head->next=NULL;
	p=head;
	printf("����������ÿ���˵����룺\n");
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
//��ʽ���
void Josephus_solve(SLNODE* head,int n,int m)
{
	SLNODE *p,*q;
	int count=0;
	int i;
	p=head;
	printf("��ʽ�������\n");
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
//˳�����
void Josephus_solve2(SNODE * rawdata,int n,int m)
{
	int count=0;
	int i,j=-1;
	printf("˳���������\n");
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

	printf("ʵ�����ƣ�ʵ��һ��Լɪ��˹�������\n");
	printf("ѧ�ţ�031620115\n");
	printf("��������ʫ��\n");
	printf("=======================\n");
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	printf ("�������п�ʼ��Current local time and date: %s", asctime(timeinfo));

	int n;
	printf("����������n(n>0)��");
	scanf("%d",&n);
	SLNODE *head=NULL;
	head=create(head,n);
	int m;
	do{
		printf("������m�ĳ�ֵ��");
		scanf("%d",&m);
	}while(m<=0);
	//��ʽ�洢���
	Josephus_solve(head,n,m);

	//˳��洢���
	//ת������
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
	//���
	Josephus_solve2(rawdata,n,m);
	//�ͷſռ�
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
	printf ("�������н�����Current local time and date: %s", asctime(timeinfo));


	system("pause");
	return 0;
}