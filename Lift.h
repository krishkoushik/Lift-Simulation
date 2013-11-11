#ifndef LIFT_H
#define LIFT_H

#include<stdio.h>
#include<stdlib.h>


//delaration of person info data struct
typedef struct person_info
{
	int time_arrival;
	int floor_arrival;
	int floor_dest;
	struct person_info* mainnext;
	struct person_info* next;
	int lift;//The lift number by which he is picked up
	int time;//The time of picking up
}person;

//declaration of a queue
typedef struct pqueue_ 
{
	person* head;
	person* tail;
}pqueue;

person * person_new(int time_arrival, int floor_arrival,
	   	int floor_dest, person* next, person * mainnext);

pqueue * pqueue_new();

/*
 * pushing an element into the queues mq and q
 */
int pqueue_push(pqueue * q, pqueue * mq, person * p);

int pqueue_pop_ele(pqueue * q, pqueue * mq, person * p);

void pqueue_print(pqueue * q);

void mpqueue_print(pqueue * q);


#endif
