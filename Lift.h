#ifndef LIFT_H
#define LIFT_H

#include<stdio.h>
#include<stdlib.h>

#define FLOOR_TIME 2

//delaration of person info data struct
typedef struct person_info
{
	int time_arrival;
	int floor_arrival;
	int floor_dest;
	struct person_info* mainnext;
	struct person_info* next;
	int lift;
	int time;
}person;

//declaration of a priority queue
typedef struct pqueue_ 
{
	person* head;
	person* tail;
}pqueue;

pqueue * pqueue_update(pqueue * pq, int t);

person * person_new(int time_arrival, int floor_arrival,
	   	int floor_dest, person* next, person * mainnext);

pqueue * pqueue_new();

int pqueue_push(pqueue * q, pqueue * mq, person * p);

person * person_get(pqueue * q);

int pqueue_pop_ele(pqueue * q, pqueue * mq, person * p);

void pqueue_print(pqueue * q);

void mpqueue_print(pqueue * q);


#endif
