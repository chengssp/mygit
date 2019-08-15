#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 30000

//直接插入排序
void InsertSort(int R[],int n,int *CompareNum,int *MoveNum)
{
	int i,j;
	for(i=2;i<=n;i++)
	{
		R[0]=R[i];
		(*MoveNum)++;
		j=i-1;
		while(R[0]<R[j] && ++(*CompareNum))
		{
			R[j+1]=R[j];
			(*MoveNum)++;
			j--;
		}
		R[j+1]=R[0];
		(*MoveNum)++;
	}
}
//简单选择排序
void SelectSort(int R[],int n,int *CompareNum,int *MoveNum)
{
	int i,j,k;
	for(i=1;i<n;i++)
	{
		k=i;
		for(j=i+1;j<=n;j++)
			if(R[j]<R[k] && ++(*CompareNum))
				k=j;
		if(k!=i)
		{	
			R[0]=R[k];
			R[k]=R[i];
			R[i]=R[0];
			*MoveNum+=3;
		}
	}
}
//冒泡排序
void BubbleSort(int R[],int n,int *CompareNum,int *MoveNum)
{
	int i,j,flag=0;
	for(i=1;(i<n && flag==0);i++)
	{
		flag=1;
		for(j=1;j<=n-i;j++)
			if(R[j+1]<R[j] && ++(*CompareNum))
			{
				flag=0;
				R[0]=R[j];
				R[j]=R[j+1];
				R[j+1]=R[0];
				*MoveNum+=3;
			}
	}
}
//快速排序
void QuickSort(int R[],int low,int high,int *CompareNum,int *MoveNum)
{
	int i,j;
	i=low;
	j=high;
	R[0]=R[i];
	while(i<j)
	{
		while((R[j]>=R[0])&&(j>i) && ++(*CompareNum))
			j--;
		if(j>i)
		{
			R[i]=R[j];
			(*MoveNum)++;
			i++;
		}
		while((R[i]<=R[0])&&(j>i) && ++(*CompareNum))
			i++;
		if(j>i)
		{
			R[j]=R[i];
			(*MoveNum)++;
			j--;
		}
	}
	R[i]=R[0];
	(*MoveNum)++;
	if(low<i)
		QuickSort(R,low,i-1,CompareNum,MoveNum);
	if(i<high)
		QuickSort(R,j+1,high,CompareNum,MoveNum);
}
//希尔排序
void ShellInsert(int R[],int m,int n,int *CompareNum,int *MoveNum)
{
	int j,temp;
	for(int i=m;i<n;i++)
	{
		temp=R[i];
		(*MoveNum)++;
		j=i;
		while(j>=m && temp<R[j-m] && ++(*CompareNum))
		{
			R[j]=R[j-m];
			(*MoveNum)++;
			j-=m;
		}
		R[j]=temp;
		(*MoveNum)++;
	}
}
void ShellSort(int R[],int n,int *CompareNum,int *MoveNum)
{
	int m;
	m=n/2;
	while(m>=1)
	{
		ShellInsert(R,m,n,CompareNum,MoveNum);
		m=(m==2?1:(m/2));
	}
}
//归并排序
void Merge(int R[],int D[],int L,int m,int h,int *CompareNum,int *MoveNum)
{
	int i,j,k;
	int n1,n2;
	i=L;
	j=m+1;
	k=L;
	while(i<=m && j<=h)
		if(R[i]<=R[j] && ++(*CompareNum))
		{
			D[k]=R[i];
			(*MoveNum)++;
			i++;k++;
		}
		else
		{
			D[k]=R[j];
			(*MoveNum)++;
			j++;k++;
		}
		if(i<=m)
			for(n1=k,n2=i;n1<=h && n2<=m;n1++,n2++)
			{
				D[n1]=R[n2];
				(*MoveNum)++;
			}
		else
			for(n1=k,n2=j;n1<=h && n2<=h;n1++,n2++)
			{	
				D[n1]=R[n2];
				(*MoveNum)++;
			}
}
void MSort(int SR[],int DR[],int s,int t,int *CompareNum,int *MoveNum)
{
	int k;
	if(s<t)
	{
		k=(s+t)/2;
		MSort(SR,DR,s,k,CompareNum,MoveNum);
		MSort(SR,DR,k+1,t,CompareNum,MoveNum);
		Merge(DR,SR,s,k,t,CompareNum,MoveNum);
	}
	for(k=s;k<=t;k++)
	{	
		DR[k]=SR[k];
		(*MoveNum)++;
	}
}

int main()
{
	time_t rawtime;
	struct tm * timeinfo;

	printf("实验名称：实验四、内部排序算法的实现与比较\n");
	printf("学号：031620115\n");
	printf("姓名：成诗鹏\n");
	printf("=======================\n");
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	printf ("程序运行开始，Current local time and date: %s", asctime(timeinfo));

	int OutputData[3][6]={0};
	for(int i=0;i<6;i++)
		OutputData[0][i]=i+1;
	//产生原始数据
	int rawdata[N+1]={0};
	int i,j;
	for(i=1;i<=N;i++)
		rawdata[i]=rand();
	int data[N+1];
	//排序数据
	for(i=0;i<N;i++)
		data[i]=rawdata[i];
	InsertSort(data,N,&OutputData[1][0],&OutputData[2][0]);

	for(i=0;i<N;i++)
		data[i]=rawdata[i];
	SelectSort(data,N,&OutputData[1][1],&OutputData[2][1]);

	for(i=0;i<N;i++)
		data[i]=rawdata[i];
	BubbleSort(data,N,&OutputData[1][2],&OutputData[2][2]);

	for(i=0;i<N;i++)
		data[i]=rawdata[i];
	QuickSort(data,1,N,&OutputData[1][3],&OutputData[2][3]);

	for(i=0;i<N;i++)
		data[i]=rawdata[i];
	ShellSort(data,N,&OutputData[1][4],&OutputData[2][4]);

	for(i=0;i<N;i++)
		data[i]=rawdata[i];
	int tempdata[N+1];
	MSort(data,tempdata,1,N,&OutputData[1][5],&OutputData[2][5]);
	//按比较次数排序
	int temp[3];
	for(i=1;i<6;i++)
	{
		temp[0]=OutputData[0][i];
		temp[1]=OutputData[1][i];
		temp[2]=OutputData[2][i];
		j=i-1;
		while(temp[1]<OutputData[1][j] && j>=0)
		{
			OutputData[0][j+1]=OutputData[0][j];
			OutputData[1][j+1]=OutputData[1][j];
			OutputData[2][j+1]=OutputData[2][j];
			j--;
		}
		OutputData[0][j+1]=temp[0];
		OutputData[1][j+1]=temp[1];
		OutputData[2][j+1]=temp[2];
	}
	printf("排序算法代号：\n1.直接插入排序2.简单选择排序3.冒泡排序4.快速排序5.希尔排序6.归并排序\n\n");
	printf("排序算法");
	for(i=0;i<6;i++)
		printf("%10d",OutputData[0][i]);
	printf("\n");
	printf("比较次数");
	for(i=0;i<6;i++)
		printf("%10d",OutputData[1][i]);
	printf("\n");
	//按移动次数排序
	for(i=1;i<6;i++)
	{
		temp[0]=OutputData[0][i];
		temp[1]=OutputData[1][i];
		temp[2]=OutputData[2][i];
		j=i-1;
		while(temp[2]<OutputData[2][j] && j>=0)
		{
			OutputData[0][j+1]=OutputData[0][j];
			OutputData[1][j+1]=OutputData[1][j];
			OutputData[2][j+1]=OutputData[2][j];
			j--;
		}
		OutputData[0][j+1]=temp[0];
		OutputData[1][j+1]=temp[1];
		OutputData[2][j+1]=temp[2];
	}
	printf("排序算法");
	for(i=0;i<6;i++)
		printf("%10d",OutputData[0][i]);
	printf("\n");
	printf("移动次数");
	for(i=0;i<6;i++)
		printf("%10d",OutputData[2][i]);
	printf("\n");

	printf("=======================\n");
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	printf ("程序运行结束，Current local time and date: %s", asctime(timeinfo));
	system("pause");
	return 0;
}