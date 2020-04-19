#include<stdio.h>

static int n;
int i,j,total_time=0;
float avgtat=0,avgwt=0;
int queue[],pr_queue[];
int time=0,front=0,rear=0,q_count=0;

struct data
{
	int at,st,ct,tat,wt,pr;
	char pname[20];
}temp;

main()
{
	printf("enter the no of process");
	scanf("%d",&n);
	struct data aa[n];
	for(i=0;i<n;i++)
	{
		printf("enter the name of process %d\n",i);
		scanf("%s",&aa[i].pname);
		printf("enter the arrival time:\n");
		scanf("%d",&aa[i].at);
		printf("enter the brust time:\n");
		scanf("%d",&aa[i].st);
		printf("enter the priority:\n");
		scanf("%d",&aa[i].pr);
	}
	
	for(i=0;i<n;i++)
	{
		for(j=i;j>=1;j--)
		{
			if(aa[j].at<aa[j-1].at)
			{
				temp=aa[j-1];
				aa[j-1]=aa[j];
				aa[j]=temp;
			}
			else if(aa[j].at==aa[j-1].at)
			{
				if(aa[j].st<aa[j-1].st)
				{
					temp=aa[j-1];
					aa[j-1]=aa[j];
					aa[j]=temp;
				}
			}
		}
	}
	
	total_time+=aa[0].at+aa[0].st;
	for(i=1;i<n;i++)
	{
		if(aa[i].at>total_time)
		total_time=aa[i].at;
		
		total_time+=aa[i].st;
	}
	
	finding(aa);
	getch();
	return 0;
}

void push(int q)
{
	queue[rear++]=q;
}

int pop()
{
	int x;
	x=queue[front++];
	return x;
}

void check(struct data a[])
{
	while(a[j].at<=time&&j<n)
	{
		q_count++;
		push(j++);
	}
}

void finding(struct data a[])
{
	int temp_st[n],temp_pr[n],flag=0,count=0,p_process;
	j=0;
	int tq;
	printf("enter the time quantum\n");
	scanf("%d",&tq);
	for(i=0;i<n;i++)
	{
		temp_st[i]=a[i].st;
	}
	time=a[0].at;
	q_count=1;
	push(j++);
	while(time<=total_time)
	{
		if(flag==1||q_count!=0)
		{
			if(flag==0&&count==0)
			{
				p_process=pop();
				count=0;
				flag=1;
			}
			temp_st[p_process]--;
			if(temp_st[p_process]==0)
			{
				time++;
				count=0;
				a[p_process].ct=time;
				flag=0;
				q_count--;
				check(a);
				continue;
			}
			count++;
			
			if(count==tq)
			{
				count=0;
				time++;
				check(a);
				push(p_process);
				flag=0;
			}
			else
			{
				time++;
				check(a);
			}
		}
		else
		{
			time++;
			check(a);
		}
	}
	display(a);
}

void display(struct data a[])
{
	for(i=0;i<n;i++)
	{
		a[i].tat=a[i].ct-a[i].at;
		a[i].wt=a[i].tat-a[i].st;
	}
	for(i=0;i<n;i++)
	{
		avgtat+=a[i].tat;
		avgwt+=a[i].wt;
	}
	avgtat=avgtat/n;
	avgwt=avgwt/n;
	printf("pname\tat\tbt\tpr\tct\ttat\twt\n");
	for(i=0;i<n;i++)
	{
		printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",a[i].pname,a[i].at,a[i].st,a[i].pr,a[i].ct,a[i].tat,a[i].wt);
	}
	printf("Average Wating Time:%f",avgwt);
	printf("\nAverage Turn Around Time:%f",avgtat);
}
