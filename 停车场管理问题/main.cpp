#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//停车场顺序栈
#define N 2
typedef struct pstack
{
	int flag[N];
	int arrivetime[N];
	int top;
}ParkStack;
//创建空栈
ParkStack* Init_pstack(void)
{
	ParkStack *s;
	s=(ParkStack*)malloc(sizeof(ParkStack));
	s->top=-1;
	return s;
}
//入栈
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
//出栈
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
//便道链队列
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
//创建空队
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
//入队
void In_Queue(LinkQueue *q,int x)
{
	QNODE *p;
	p=(QNODE*)malloc(sizeof(QNODE));
	p->flag=x;
	p->next=NULL;
	q->rear->next=p;
	q->rear=p;
}
//出队
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
	//查找车是否在停车场中
	while(parkstack->flag[parkstack->top]!=newflag && parkstack->top>-1)
	{
		Pop_pstack(parkstack,&flag,&arrivetime);
		Push_pstack(tempstack,flag,arrivetime);
	}
	if (parkstack->top == -1)
	{
		printf("错误！该车不在停车场内。\n");
		while (tempstack->top != -1)
		{
			Pop_pstack(tempstack, &flag, &arrivetime);
			Push_pstack(parkstack, flag, arrivetime);
		}
	}
	else
	{
		Pop_pstack(parkstack, &flag, &arrivetime);
		printf("该车停车时间为：%d\n", gotime - arrivetime);
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
	printf("停车场内车数为：%d\n",(parkstack->top)+1);
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
	printf("队列中车数为：%d\n",n);
}

int main()
{
	time_t rawtime;
	struct tm * timeinfo;

	printf("实验名称：实验二、停车场管理问题\n");
	printf("学号：031620115\n");
	printf("姓名：成诗鹏\n");
	printf("==================================\n");
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("程序运行开始，Current local time and date: %s", asctime(timeinfo));

	//初始化数据
	ParkStack* parkstack;
	parkstack=Init_pstack();
	ParkStack* tempstack;
	tempstack=Init_pstack();
	LinkQueue *waitline;
	waitline=Init_Queue();
	char command;
	int flag,realtime,lasttime=0;
	
	printf("输入数据格式：“X 0 0”\n");
	while(1)
	{
		printf(">>");
		scanf("%c %d %d",&command,&flag,&realtime);
		getchar();
		if (realtime < lasttime && (command == 'A' || command == 'D'))
		{
			printf("时间顺序错误！\n");
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
			printf("命令错误！\n");
			rewind(stdin);
			break;
		}
	}
	end:
	printf("=======================\n");
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("程序运行结束，Current local time and date: %s", asctime(timeinfo));

	system("pause");

	return 0;
}