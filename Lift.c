/*
 * Lift.c : To define the basic queue and person operations
 * Last Modified : Sun, 10 Nov 2013 14:07:29
 */

#include "Lift.h"

//function for creating a new persons info.using a data struct called person.
//VARIABLE EXPLANATION:-
//	time_arrival:at what time he comes
//	floor_arrival:at what floor he comes
//	floor_dest:at what floor he wants to go
//	next:
//	mainn:
person* person_new(int time_arrival,int floor_arrival,
		int floor_dest,person * next, person * mainn)
{
	person* newp = (person*)malloc(sizeof(person));
	newp->time_arrival=time_arrival;
	newp->floor_arrival=floor_arrival;
	newp->floor_dest=floor_dest;
	newp->next=next;
	newp->mainnext=mainn;
	newp->lift=-1;
	newp->time=-1;
	return newp;
}


//creating a priority queue.This is the basic creation function for the priority queue, with two pointers,one for the head and one for the tail.
pqueue* pqueue_new()
{	
	pqueue* first=(pqueue*)malloc(sizeof(pqueue));
	first->head=NULL;
	first->tail=NULL;
	return first;	
}


//Add a new element at the start of the pqueue.ie, push the information of the person next in line.
//VARIABLE EXPLANATION:-
//	q:
//	mq:
//	per:
int pqueue_push(pqueue * q, pqueue * mq,  person * per)
{
	//Checking in q
	if(q->head==NULL && q->tail==NULL)
	{
		q->head=per;
		q->tail=per;
	}
	else
	{
		person* temp;
		temp=q->tail;
		temp->next=per;
		q->tail=temp->next;
	}
	//Checking in mq	
	if(mq->head==NULL && mq->tail==NULL)
	{
		mq->head=per;
		mq->tail=per;
	}
	else
	{	
		person* temp;
		temp=mq->tail;
		temp->mainnext=per;
		mq->tail=temp->mainnext;
	}	
	return 1;
}


//function to pop out the first person in the pqueue.This function pops a person from both mq and q.
//we have mq aas the main queue and the q as the queue for each floor.
//VARIABLE EXPLANATION:-
//	q:
//	mq:
//	p:
int pqueue_pop_ele(pqueue * q, pqueue * mq, person * p )
{
	if(p==NULL)
		return 0;
	//For popping from q
	if(q->head==NULL)
	{
		return 0;
	}
	else
	{
		person* temp = q->head;
		if(temp == p)
		{
			if(q->head==q->tail)
				q->tail = p->next;
			q->head = p->next;
		}
		else
		{
			for(;temp!=NULL;temp=temp->next)
			{
				if(temp->next==p)
				{
					temp->next=p->next;
					break;
				}
			}
		}
	}
	//For popping from mq
	if(mq->head==NULL)
	{
		return 0;	
	}
	else
	{
		person* temp = mq->head;
		if(temp == p)
		{
			if(mq->head==mq->tail)
				mq->tail = p->mainnext;
			mq->head = p->mainnext;
		}
		else
		{
			for(;temp!=NULL;temp=temp->mainnext)
			{
				if(temp->mainnext==p)
				{
					temp->mainnext=p->mainnext;
					break;
				}
			}
		}
	}
	free(p);
	return 1;
}


//function for printing out the pqueue.this function prints out the entire queue in its order
//VARIABLE EXPLANATION:-
//	q:
void pqueue_print( pqueue* q )
{
	person* temp = q->head;
	while(temp!=NULL)
	{
		printf("time : %d  pick : %d  lift : %d\t",temp->time_arrival,temp->time,temp->lift);
		printf("arri : %d\t",temp->floor_arrival);
		printf("dest : %d\n",temp->floor_dest);
		temp=temp->next;
	}
	printf("\n");
}

//function for printing out the main pqueue.this function prints out the entire main queue in its order.
//VARIABLE EXPLANATION:-
//	q:
void mpqueue_print( pqueue* q )
{
	person* temp = q->head;
	while(temp!=NULL)
	{
		printf("time : %d  pick : %d  lift : %d\t",temp->time_arrival,temp->time,temp->lift);
		printf("arri : %d\t",temp->floor_arrival);
		printf("dest : %d\n",temp->floor_dest);
		temp=temp->mainnext;
	}
	printf("\n");
}



