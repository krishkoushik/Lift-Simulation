#include "PrintLift.h"
#include<conio.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

//This function is for printing out the state of the lift at each instant of time.used for showing the simulation in the terminal.
//VARIABLE EXPLANATION:-
//	fq: array of queues
//	num_floors: total number of floors
//	lift1: lift 1
//	lift2: lift 2
//	tot_time: total time.
void state_print(pqueue ** fq, int num_floors, State * lift1, State * lift2, int tot_time)
{
	int i;
	for(i=0;i<=tot_time;++i)
	{
		int j;
		for(j=0;j<=FLOOR_TIME*num_floors;++j)
		{
			if(j%FLOOR_TIME==0)
				printf("%s%d%s",KCYN,j/FLOOR_TIME,KNRM);
			if(lift1->place_time[i]==j)
			{
				if(i!=0)
				{
					if( j%FLOOR_TIME==0 )
					{
						if(lift1->place_time[i]==lift1->place_time[i+1]
								|| lift1->place_time[i]==lift1->place_time[i-1])
							printf("\t%sS1S%s\t",KRED,KNRM);
						else
							printf("\t%s#1#%s\t",KGRN,KNRM);
					}
					else
						printf("\t%s#1#%s\t",KGRN,KNRM);
				}
				else
				{
						printf("\t%s#1#%s\t",KGRN,KNRM);
				}
			}
			else
			{
				printf("\t    \t");
			}

			if(lift2->place_time[i]==j)
			{
				if(i!=0)
				{
					if( j%FLOOR_TIME==0 )
					{
						if(lift2->place_time[i]==lift2->place_time[i+1]
								|| lift2->place_time[i]==lift2->place_time[i-1])
							printf("\t%sS2S%s\t",KRED,KNRM);
						else
							printf("\t%s#2#%s\t",KGRN,KNRM);
					}
					else
						printf("\t%s#2#%s\t",KGRN,KNRM);
				}
				else
				{
						printf("\t%s#2#%s\t",KGRN,KNRM);
				}
			}
			else
			{
				printf("\t    \t");
			}
				
			person *p;
			if(j%FLOOR_TIME==0)
			for(p=fq[j/FLOOR_TIME]->head;p!=NULL;p=p->next)
			{
				if(p->time_arrival<=i && p->time>=i)
				{
					printf("%d %d   ",p->floor_dest, p->lift);
				}
			}
			printf("\n");
		}
		char ch;
		system("sleep 0.3");
		ch=getch();
		if(ch=='q')
		break;
		if(i==tot_time)
		{
			system("sleep 3");
		}
		system("clear");
	}
	return ;
}
