#include "Simulate.h"

//Function to find the floors the lift will be at for all times
void findfloors(float * arr, int size)
{
	int i;
	int prev,aft;
	for(i=0;i<size;++i)
	{
		if(arr[i]!=-1)
			prev=arr[i];
		else
		{
			int j=i;
			while(arr[j]==-1 && j<size)j++;
			aft=arr[j];
			int temp=j;
			j=i;
			i=temp-1;
			while(arr[j]==-1 && j<size)
			{
				arr[j]=(prev+aft)*(1.0)/2;
				j++;
			}
		}
	}
	return ;
}

//Function to create a new State (Lift's state)
State * State_new(int curr_floor, int num_floors, int time, int dir, int lift_num)
{
	State * st = (State *)malloc(sizeof(State));
	st->floor = curr_floor;
	st->time = time;
	st->dst = (int *)malloc((num_floors+1)*(sizeof(int)));
	int i;
	for(i=0;i<=num_floors;++i)
	{
		st->dst[i]=0;
	}
	for(i=0;i<10000;++i)
	{
		st->place_time[i]=-1;
	}
	st->place_time[0] = curr_floor;
	st->lift_no = lift_num;
	st->direction = dir;
	return st;
}

void State_delete(State * st)
{
	free(st->dst);
	free(st);
}


//Function to make the lift to go to a patrticular floor
// @param begin starting floor of the lift
// @param end destination of the lift
// @param st state of the lift which needs to go to the floor
// @param qf array of queues (one for each floor)
// @param total floor number of floors
// @param reserved amount of lift space to be reserved when reaching end
void GoTo(int begin, int end, State * st, pqueue ** qf, int floor, int reserved)
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
					st->place_time[st->time]=st->floor;
				}
				for(p=qf[i]->head;p!=NULL;p=p->next)
				{
					int ch1 = direction*(p->floor_dest-end);
					int ch2 = direction*(p->floor_dest-i);
					if(st->num_people<MAX_CAPACITY && ch2>0
						&& p->lift==-1 && p->time==-1 && p->time_arrival <= st->time)
					{
						if(ch1<=0 || (st->num_people < MAX_CAPACITY - reserved && reserved>0))
						{
							st->num_people++;
							p->lift = st->lift_no;
							p->time = st->time;
							st->dst[p->floor_dest]++;
							flag=1;
						}
					}
				}
				if(flag==1 || st->dst[i]>0)
				{
					st->time+=WAIT_TIME;
					st->place_time[st->time]=st->floor;
					st->dst[i]=0;
				}
			}
			if(i==end)
			{
				st->floor = i;
				st->time+=FLOOR_TIME;
				st->place_time[st->time]=st->floor;
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
					st->place_time[st->time]=st->floor;
				}
				for(p=qf[i]->head;p!=NULL;p=p->next)
				{
					int ch1 = direction*(p->floor_dest-end);
					int ch2 = direction*(p->floor_dest-i);
					if(st->num_people<MAX_CAPACITY && ch2>0
						&& p->lift==-1 && p->time==-1 && p->time_arrival <= st->time)
					{
						if(ch1<=0 || (st->num_people < MAX_CAPACITY - reserved && reserved>0))
						{
							st->num_people++;
							p->lift = st->lift_no;
							p->time = st->time;
							st->dst[p->floor_dest]++;
							flag=1;
						}
					}
				}
				if(flag==1 || st->dst[i]>0)
				{
					st->time+=WAIT_TIME;
					st->place_time[st->time]=st->floor;
					st->dst[i]=0;
				}
			}
			if(i==end)
			{
				st->floor = i;
				st->time+=FLOOR_TIME;
				st->place_time[st->time]=st->floor;
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
		//Checking if there is space and if the person is not already pickedup
		if(st->num_people<MAX_CAPACITY && p->lift==-1 && p->time==-1)
		{
			if(dir==0)
			{
				if(st->time<p->time_arrival)
				{
					st->time = p->time_arrival;
					st->place_time[st->time] = st->floor;
				}

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
	st->place_time[st->time]=st->floor;
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
				st->place_time[st->time]=st->floor;
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
					st->place_time[st->time]=st->floor;
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
				st->place_time[st->time]=st->floor;
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
					st->place_time[st->time]=st->floor;
					st->dst[i]=0;
				}
			}
		}
	st->dst[end]=0;
	st->num_people=0;
}

int CalculateNumPersons(pqueue * pq)
{
	person * p;
	int flag=0;
	int count=0;
	int prevtime=0;
	for(p=pq->head;p!=NULL;p=p->next)
	{
		if(flag==0)
		{
			if(p->time==-1)
			{
				flag=1;
				count++;
				prevtime=p->time_arrival;
			}
		}
		else
		{
			if(p->time_arrival==prevtime && p->time==-1)
				count++;
		}
	}
	return count;
}
			


//Function to simulate the twin lifts
void Simulate(pqueue ** qf, pqueue * mq, int num_floors)
{
	State * lift1 = State_new(0, num_floors, 0, 1, 1);
	State * lift2 = State_new(num_floors, num_floors, 0, -1, 2);
	person * p;
	for(p=mq->head;p!=NULL;p=p->mainnext)
	{
		if(p->time!=-1)
			continue;

		int reserved = CalculateNumPersons(qf[p->floor_arrival]);
		
		int a1 = lift1->floor-p->floor_arrival;
		int a2 = lift2->floor-p->floor_arrival;
		
		if(a1<0)a1*=-1;
		if(a2<0)a2*=-1;

		a1*=FLOOR_TIME;
		a2*=FLOOR_TIME;

		if(a1+lift1->time<=a2+lift2->time)
		{
			GoTo(lift1->floor, p->floor_arrival, lift1, qf, num_floors, reserved);
			Pickup(p->floor_arrival, lift1, qf); 
			Drop(lift1->floor, p->floor_dest, lift1, qf, num_floors);
		}
		else
		{
			GoTo(lift2->floor, p->floor_arrival, lift2, qf, num_floors, reserved);
			Pickup(p->floor_arrival, lift2, qf); 
			Drop(lift2->floor, p->floor_dest, lift2, qf, num_floors);
		}
			

		

		/*if(lift1->time==lift2->time)
		{
			int a1 = lift1->floor-p->floor_arrival;
			int a2 = lift2->floor-p->floor_arrival;
			if(a1*a1<=a2*a2)
			{
				if((p->floor_dest-p->floor_arrival)*(p->floor_arrival - lift1->floor)<0)
				   reserved*=-1;	
				GoTo(lift1->floor, p->floor_arrival, lift1, qf, num_floors, reserved);
				Pickup(p->floor_arrival, lift1, qf); 
				Drop(lift1->floor, p->floor_dest, lift1, qf, num_floors);
			}
			else
			{
				if((p->floor_dest-p->floor_arrival)*(p->floor_arrival - lift2->floor)<0)
				   reserved*=-1;
				GoTo(lift2->floor, p->floor_arrival, lift2, qf, num_floors, reserved);
				Pickup(p->floor_arrival, lift2, qf); 
				Drop(lift2->floor, p->floor_dest, lift2, qf, num_floors);
			}
		}
		else if(lift1->time<lift2->time)
		{
			if((p->floor_dest-p->floor_arrival)*(p->floor_arrival - lift1->floor)<0)
			   reserved*=-1;
			GoTo(lift1->floor, p->floor_arrival, lift1, qf, num_floors, reserved);
			Pickup(p->floor_arrival, lift1, qf); 
			Drop(lift1->floor, p->floor_dest, lift1, qf, num_floors);
		}
		else
		{
			if((p->floor_dest-p->floor_arrival)*(p->floor_arrival - lift2->floor)<0)
			   reserved*=-1;
			GoTo(lift2->floor, p->floor_arrival, lift2, qf, num_floors, reserved);
			Pickup(p->floor_arrival, lift2, qf); 
			Drop(lift2->floor, p->floor_dest, lift2, qf, num_floors);
		}*/
	printf("Lift 1: %d  %d\n",lift1->time,lift1->floor);
	printf("Lift 2: %d  %d\n",lift2->time,lift2->floor);
	
	}
	lift1->num_people-=lift1->dst[lift1->floor];
	lift2->num_people-=lift2->dst[lift2->floor];
	if(lift1->num_people==0 && lift2->num_people==0)
		printf("\nSuccessfuly simulated!!\n\n");
	int j;

	//////////////////////////////////////////////////
	lift1->place_time[lift1->time+1] = lift1->floor;//
	lift2->place_time[lift2->time+1] = lift2->floor;//
	findfloors(lift1->place_time,lift1->time+1);    //
	findfloors(lift2->place_time,lift2->time+1);    //
													//
	printf("\nLift1 : \n");                         //
	for(j=0;j<=lift1->time;++j)                     //
	{                                               //
		printf("%d  %.1f\n",j,lift1->place_time[j]);//	
	}                                               //
	printf("\nLift2 : \n");                         //
	for(j=0;j<=lift2->time;++j)                     //
	{                                               //
		printf("%d  %.1f\n",j,lift2->place_time[j]);//	
	}                                               //
	//////////////////////////////////////////////////
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
