#include "Simulate.h"

State * State_new(int curr_floor, int num_floors, int time, int dir, int lift_num)
{
	State * st = (State *)malloc(sizeof(State));
	st->floor = curr_floor;
	st->time = time;
	st->dst = (int *)malloc(num_floors*(sizeof(int)));
	st->lift_no = lift_num;
	st->direction = dir;
	return st;
}

void State_delete(State * st)
{
	free(st->dst);
	free(st);
}

void GoTo(int begin, int end, State * st, pqueue ** qf, int floor)
{
	if(begin==end)
		return; 
	int direction = end>begin?1:-1;
	person * p;
	int i;
	int flag=0;
	if(direction==1)
		for(i=0;i<=floor;++i)
		{
			flag=0;
			if(direction*(i-begin)>=0 && direction*(end-i)>0)
			{
				st->floor = i;
				st->num_people-=st->dst[i];
				if(i-begin!=0)
				{
					st->time+=FLOOR_TIME;
				}
				for(p=qf[i]->head;p!=NULL;p=p->next)
				{
					int ch1 = direction*(p->floor_dest-end);
					int ch2 = direction*(p->floor_dest-i);
					if(st->num_people<MAX_CAPACITY && ch1<=0 && ch2>0
							&& p->lift==-1 && p->time==-1 && p->time_arrival <= st->time)
					{
						st->num_people++;
						p->lift = st->lift_no;
						p->time = st->time;
						st->dst[p->floor_dest]++;
						flag=1;
					}
				}
				if(flag==1 || st->dst[i]>0)
				{
					st->time+=WAIT_TIME;
					st->dst[i]=0;
				}
			}
			if(i==end)
			{
				st->floor = i;
				st->time+=FLOOR_TIME;
				return ;
			}
		}
	else
		for(i=floor;i>=0;--i)
		{
			flag=0;
			if(direction*(i-begin)>=0 && direction*(end-i)>0)
			{
				st->floor = i;
				st->num_people-=st->dst[i];
				if(i-begin!=0)
				{
					st->time+=FLOOR_TIME;
				}
				for(p=qf[i]->head;p!=NULL;p=p->next)
				{
					int ch1 = direction*(p->floor_dest-end);
					int ch2 = direction*(p->floor_dest-i);
					if(st->num_people<MAX_CAPACITY && ch1<=0 && ch2>0
							&& p->lift==-1 && p->time==-1 && p->time_arrival <= st->time)
					{
						st->num_people++;
						p->lift = st->lift_no;
						p->time = st->time;
						st->dst[p->floor_dest]++;
						flag=1;
					}
				}
				if(flag==1 || st->dst[i]>0)
				{
					st->time+=WAIT_TIME;
					st->dst[i]=0;
				}
			}
			if(i==end)
			{
				st->floor = i;
				st->time+=FLOOR_TIME;
				return ;
			}
		}
}

void Pickup(int floor, State * st, pqueue ** qf)
{
	person * p;
	pqueue * fl = qf[floor];
	st->num_people-=st->dst[floor];
	st->dst[floor]=0;
	int dir=0;
	for(p=fl->head;p!=NULL;p=p->next)
	{
		if(st->time<p->time_arrival)
			st->time = p->time_arrival;
		if(st->num_people<MAX_CAPACITY && p->lift==-1 && p->time==-1)
		{
			if(dir==0)
			{
				if(p->floor_dest>floor)
					dir=1;
				else
					dir=-1;
			}
			else
			{
				if(dir*(p->floor_dest-floor)<=0)
				{
					continue;
				}
			}
			st->num_people++;
			p->lift = st->lift_no;
			p->time = st->time;
			st->dst[p->floor_dest]++;
		}
	}
	st->time+=WAIT_TIME;
}

void Drop(int begin, int end, State * st, pqueue ** qf, int floor)
{
	int direction = end>begin?1:-1;
	person * p;
	int i;
	int flag=0;
	if(direction==1)
		for(i=0;i<=floor;++i)
		{
			flag=0;
			if(direction*(i-begin)>0)
			{
				st->floor = i;
				st->num_people-=st->dst[i];
				st->time+=FLOOR_TIME;
				if(st->num_people==0)
				{
					st->num_people+=st->dst[i];
					return ;
				}
				for(p=qf[i]->head;p!=NULL;p=p->next)
				{
					int ch1 = direction*(p->floor_dest-end);
					int ch2 = direction*(p->floor_dest-i);
					if(st->num_people<MAX_CAPACITY && ch2>0
							&& p->lift==-1 && p->time==-1 && p->time_arrival <= st->time)
					{
						st->num_people++;
						p->lift = st->lift_no;
						p->time = st->time;
						flag=1;
						st->dst[p->floor_dest]++;
					}
				}
				if(flag==1 || st->dst[i]>0)
				{
					st->time+=WAIT_TIME;
					st->dst[i]=0;
				}
			}
		}
	else
		for(i=floor;i>=0;--i)
		{
			flag=0;
			if(direction*(i-begin)>0)
			{
				st->floor = i;
				st->num_people-=st->dst[i];
				st->time+=FLOOR_TIME;
				if(st->num_people==0)
				{
					st->num_people+=st->dst[i];
					return ;
				}
				for(p=qf[i]->head;p!=NULL;p=p->next)
				{
					int ch1 = direction*(p->floor_dest-end);
					int ch2 = direction*(p->floor_dest-i);
					if(st->num_people<MAX_CAPACITY && ch2>0
							&& p->lift==-1 && p->time==-1 && p->time_arrival <= st->time)
					{
						st->num_people++;
						p->lift = st->lift_no;
						p->time = st->time;
						flag=1;
						st->dst[p->floor_dest]++;
					}
				}
				if(flag==1 || st->dst[i]>0)
				{
					st->time+=WAIT_TIME;
					st->dst[i]=0;
				}
			}
		}
	st->dst[end]=0;
	st->num_people=0;
}

void Simulate(pqueue ** qf, pqueue * mq, int num_floors)
{
	State * lift1 = State_new(0, num_floors, 0, 1, 1);
	State * lift2 = State_new(num_floors, num_floors, 0, -1, 2);
	person * p;
	for(p=mq->head;p!=NULL;p=p->mainnext)
	{
		if(p->time!=-1)
			continue;


		if(lift1->time==lift2->time)
		{
			int a1 = lift1->floor-p->floor_arrival;
			int a2 = lift2->floor-p->floor_arrival;
			if(a1*a1<=a2*a2)
			{
				GoTo(lift1->floor, p->floor_arrival, lift1, qf, num_floors);
				Pickup(p->floor_arrival, lift1, qf); 
				Drop(lift1->floor, p->floor_dest, lift1, qf, num_floors);
			}
			else
			{
				GoTo(lift2->floor, p->floor_arrival, lift2, qf, num_floors);
				Pickup(p->floor_arrival, lift2, qf); 
				Drop(lift2->floor, p->floor_dest, lift2, qf, num_floors);
			}
		}
		else if(lift1->time<lift2->time)
		{
			GoTo(lift1->floor, p->floor_arrival, lift1, qf, num_floors);
			Pickup(p->floor_arrival, lift1, qf); 
			Drop(lift1->floor, p->floor_dest, lift1, qf, num_floors);
		}
		else
		{
			GoTo(lift2->floor, p->floor_arrival, lift2, qf, num_floors);
			Pickup(p->floor_arrival, lift2, qf); 
			Drop(lift2->floor, p->floor_dest, lift2, qf, num_floors);
		}
	printf("Lift 1: %d  %d\n",lift1->time,lift1->floor);
	printf("Lift 2: %d  %d\n",lift2->time,lift2->floor);
	
	}
}

float CalculateMeanTime(pqueue * mq)
{
	long long int sum=0;
	int num_of_people=0;
	person * p;
	for(p=mq->head;p!=NULL;p=p->mainnext)
	{
		sum+=(p->time - p->time_arrival);
		num_of_people++;
	}
	if(num_of_people==0)
		return 0;
	else
		return sum*1.0/num_of_people;
}
