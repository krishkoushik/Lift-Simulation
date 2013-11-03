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
	int direction = end>begin?1:-1;
	person * p;
	int i;
	int flag=0;
	if(direction==1)
		for(i=0;i<=floor;++i)
		{
			if(direction*(i-begin)>=0 && direction*(end-i)>0)
			{
				st->num_people-=st->dst[i];
				for(p=qf[i]->head;p!=NULL;p=p->next)
				{
					if(st->num_people<MAX_CAPACITY && direction*(p->floor_dest - end)<=0
							&& p->lift==-1 && p->time==-1)
					{
						st->num_people++;
						p->lift = st->lift_no;
						p->time = st->time;
						st->dst[p->floor_dest]++;
						flag=1;
					}
				}
				if(flag==1 || st->dst[i]>0)
					st->time++;
			}
		}
	else
		for(i=floor;i>=0;--i)
		{
			if(direction*(i-begin)>=0 && direction*(end-i)>0)
			{
				st->num_people-=st->dst[i];
				for(p=qf[i]->head;p!=NULL;p=p->next)
				{
					if(st->num_people<MAX_CAPACITY && direction*(p->floor_dest - end)<=0
							&& p->lift==-1 && p->time==-1)
					{
						st->num_people++;
						p->lift = st->lift_no;
						p->time = st->time;
						st->dst[p->floor_dest]++;
						flag=1;
					}
				}
				if(flag==1 || st->dst[i]>0)
					st->time++;
			}
		}
}

void Pickup(pqueue * fl, State * st)
{
	person * p;
	for(p=fl->head;p!=NULL;p=p->next)
	{
		if(st->num_people<MAX_CAPACITY && p->lift==-1 && p->time==-1)
		{
			st->num_people++;
			p->lift = st->lift_no;
			p->time = st->time;
			st->dst[p->floor_dest]++;

		}
	}
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
			if(direction*(i-begin)>=0)
			{
				st->num_people-=st->dst[i];
				for(p=qf[i]->head;p!=NULL;p=p->next)
				{
					if(st->num_people<MAX_CAPACITY && direction*(p->floor_dest - begin)>0
								&& p->lift==-1 && p->time==-1)
					{
						st->num_people++;
						p->lift = st->lift_no;
						p->time = st->time;
						flag=1;
						st->dst[p->floor_dest]++;
					}
				}
				if(flag==1 || st->dst[i]>0)
					st->time++;
			}
		}
	else
		for(i=floor;i>=0;--i)
		{
			if(direction*(i-begin)>=0)
			{
				st->num_people-=st->dst[i];
				for(p=qf[i]->head;p!=NULL;p=p->next)
				{
					if(st->num_people<MAX_CAPACITY && direction*(p->floor_dest - begin)>0
								&& p->lift==-1 && p->time==-1)
					{
						st->num_people++;
						p->lift = st->lift_no;
						p->time = st->time;
						flag=1;
						st->dst[p->floor_dest]++;
					}
				}
				if(flag==1 || st->dst[i]>0)
						st->time++;
			}
		}
}

void Simulate(pqueue ** qf, pqueue * mq, int num_floors)
{
	State * lift1 = State_new(0, num_floors, 0, 1, 1);
	State * lift2 = State_new(num_floors, num_floors, 0, -1, 2);
	person * p;
	for(p=mq->head;p!=NULL;p=p->mainnext)
	{
		if(lift1->time==lift2->time)
		{
			int a1 = lift1->floor-p->floor_arrival;
			int a2 = lift2->floor-p->floor_arrival;
			if(a1*a1>=a2*a2)
			{
				GoTo(lift1->floor, p->floor_arrival, lift1, qf, num_floors);
				Pickup(qf[p->floor_arrival], lift1); 
				Drop(lift1->floor, p->floor_arrival, lift1, qf, num_floors);
			}
		}
	}
}
