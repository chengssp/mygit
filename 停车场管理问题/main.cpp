#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//ͣ����˳��ջ
#define N 2
typedef struct pstack
{
	int flag[N];
	int arrivetime[N];
	int top;
}ParkStack;
//������ջ
ParkStack* Init_pstack(void)
{
	ParkStack *s;
	s=(ParkStack*)malloc(sizeof(ParkStack));
	s->top=-1;
	return s;
}
//��ջ
int Push_pstack(ParkStack *s,int x,int y)
{
	if(s->top==N-1)
		return 0;
	else
	{
		s->top++;
		s->flag[s->top]=x;
		s->arrivetime[s->top]=y;
		return 1;
	}
}
//��ջ
int Pop_pstack(ParkStack *s,int *x,int *y)
{
	if(s->top==-1)
		return 0;
	else
	{
		*x=s->flag[s->top];
		*y=s->arrivetime[s->top];
		s->top--;
		return 1;
	}
}
//���������
#define QNODE struct qnode
QNODE
{
	int flag;
	QNODE *next;
};
typedef struct linkqueue
{
	QNODE *front,*rear;
}LinkQueue;
//�����ն�
LinkQueue* Init_Queue(void)
{
	LinkQueue *q;
	QNODE *p;
	q=(LinkQueue*)malloc(sizeof(LinkQueue));
	p=(QNODE*)malloc(sizeof(QNODE));
	p->next=NULL;
	q->front=q->rear=p;
	return q;
}
//���
void In_Queue(LinkQueue *q,int x)
{
	QNODE *p;
	p=(QNODE*)malloc(sizeof(QNODE));
	p->flag=x;
	p->next=NULL;
	q->rear->next=p;
	q->rear=p;
}
//����
int Out_Queue(LinkQueue *q,int *x)
{
	QNODE *p;
	if(q->front==q->rear)
		return 0;
	else
	{
		p=q->front->next;
		q->front->next=p->next;
		*x=p->flag;
		free(p);
		if(q->front->next==NULL)
			q->rear=q->front;
		return 1;
	}
}


void ComeCar(ParkStack* parkstack,LinkQueue *waitline,int flag,int arrivetime)
{
	if(parkstack->top<N-1)
		Push_pstack(parkstack,flag,arrivetime);
	else
		In_Queue(waitline,flag);
}
void GoCar(ParkStack* parkstack,ParkStack* tempstack,LinkQueue *waitline,int newflag,int gotime)
{
	int flag,arrivetime;
	//���ҳ��Ƿ���ͣ������
	while(parkstack->flag[parkstack->top]!=newflag && parkstack->top>-1)
	{
		Pop_pstack(parkstack,&flag,&arrivetime);
		Push_pstack(tempstack,flag,arrivetime);
	}
	if (parkstack->top == -1)
	{
		printf("���󣡸ó�����ͣ�����ڡ�\n");
		while (tempstack->top != -1)
		{
			Pop_pstack(tempstack, &flag, &arrivetime);
			Push_pstack(parkstack, flag, arrivetime);
		}
	}
	else
	{
		Pop_pstack(parkstack, &flag, &arrivetime);
		printf("�ó�ͣ��ʱ��Ϊ��%d\n", gotime - arrivetime);
		while (tempstack->top != -1)
		{
			Pop_pstack(tempstack, &flag, &arrivetime);
			Push_pstack(parkstack, flag, arrivetime);
		}
		if (waitline->front != waitline->rear)
		{
			Out_Queue(waitline, &flag);
			Push_pstack(parkstack, flag, gotime);
		}
	}
}
void DisplayParkNumber(ParkStack* parkstack)
{
	printf("ͣ�����ڳ���Ϊ��%d\n",(parkstack->top)+1);
}
void DisplayWaitNumber(LinkQueue *waitline)
{
	QNODE *p;
	p=waitline->front->next;
	int n=0;
	while(p!=NULL)
	{
		p=p->next;
		n++;
	}
	printf("�����г���Ϊ��%d\n",n);
}

int main()
{
	time_t rawtime;
	struct tm * timeinfo;

	printf("ʵ�����ƣ�ʵ�����ͣ������������\n");
	printf("ѧ�ţ�031620115\n");
	printf("��������ʫ��\n");
	printf("==================================\n");
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("�������п�ʼ��Current local time and date: %s", asctime(timeinfo));

	//��ʼ������
	ParkStack* parkstack;
	parkstack=Init_pstack();
	ParkStack* tempstack;
	tempstack=Init_pstack();
	LinkQueue *waitline;
	waitline=Init_Queue();
	char command;
	int flag,realtime,lasttime=0;
	
	printf("�������ݸ�ʽ����X 0 0��\n");
	while(1)
	{
		printf(">>");
		scanf("%c %d %d",&command,&flag,&realtime);
		getchar();
		if (realtime < lasttime && (command == 'A' || command == 'D'))
		{
			printf("ʱ��˳�����\n");
			rewind(stdin);
			continue;
		}
		if(command == 'A' || command == 'D')
			lasttime = realtime;
		switch(command)
		{
		case 'A':
			ComeCar(parkstack,waitline,flag,realtime);
			break;
		case 'D':
			GoCar(parkstack,tempstack,waitline,flag,realtime);
			break;
		case 'P':
			DisplayParkNumber(parkstack);
			break;
		case 'W':
			DisplayWaitNumber(waitline);
			break;
		case 'E':
			goto end;
			break;
		default:
			printf("�������\n");
			rewind(stdin);
			break;
		}
	}
	end:
	printf("=======================\n");
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("�������н�����Current local time and date: %s", asctime(timeinfo));

	system("pause");

	return 0;
}