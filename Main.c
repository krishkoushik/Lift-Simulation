#include<stdio.h>
#include "Lift.h"
#include "curses.h"
int main()
{
	int n,t,floor;
	scanf("%d %d %d",&n,&t,&floor);
	int i,j;
	pqueue * mainq = pqueue_new();
	pqueue ** qfloor = (pqueue **)malloc((floor+1)*sizeof(pqueue *));
	for(i=0;i<=floor;++i)
	{
		qfloor[i] = pqueue_new();
	}
	for(i=0;i<t;++i)
	{
		int num_of_persons;
		scanf("%d",&num_of_persons);
		for(j=0;j<num_of_persons;++j)
		{
			int arr,dst;
			scanf("%d %d",&arr,&dst);
			person * p = person_new(i,arr,dst,NULL,NULL);
			pqueue_push(qfloor[arr],mainq,p);
		}
	}
	//printf("\e[1;1H\e[2J");
	//clear();
	//refresh();
	//pqueue_pop_ele(qfloor[2],mainq,qfloor[2]->head->next);
	for(i=0;i<=floor;++i)
	{
		printf("%d'th floor : \n",i);
		pqueue_print(qfloor[i]);
	}
	mpqueue_print(mainq);
	return 1;
}
