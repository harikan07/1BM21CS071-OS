#include<stdio.h>
void main()
{
	int n,pid[10],burst[10],WT[10],TA[10],i;
	float avgWT=0,avgTA=0;
	printf("Enter the number of processors\n");
	scanf("%d",&n);
	printf("Enter the process id and burst time\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&pid[i]);
		scanf("%d",&burst[i]);
	}
	
	printf("\nAccording to First come first serve schedule");
	for(i=0;i<n;i++)
	{
		printf("\nprocess id %d",pid[i]);
		printf("\nburst time %d \n",burst[i]);
	}	
		
		
	WT[0]=0;
	for(i=1;i<n;i++)
	{
		WT[i]=(WT[i-1]+burst[i-1]);
	}
	
	for(i=0;i<n;i++)
	{
	  TA[i]=WT[i]+burst[i];
	}
	
	for(i=0;i<n;i++)
	{
		avgWT+=WT[i];
        avgTA+=TA[i];
	}
	avgWT=avgWT/n;
	avgTA=avgTA/n;
	
	printf("\nThe Average waiting time is %f",avgWT);
	printf("\nThe Average turn around time is %f",avgTA);

}
