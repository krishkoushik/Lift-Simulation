#ifndef SIMULATE_H
#define SIMULATE_H

#define MAX_CAPACITY 8 
#define WAIT_TIME 1
#define FLOOR_TIME 2

#include<stdio.h>
#include<stdlib.h>
#include "Lift.h"

typedef struct State_{
	int lift_no;
	int time;
	int floor;
	int direction; //1 when moving up -1 when moving down and 0 otherwise
	int * dst;     //Represents how many people want to go to each floor
	int num_people;
} State;

State * State_new(int curr_floor, int num_floors, int time, int dir, int lift_num);

void State_delete(State * st);

void GoTo(int begin, int end, State * st, pqueue ** qf, int floor);

void Pickup(int floor, State * st, pqueue ** qf);

void Drop(int begin, int end, State * st, pqueue ** qf, int floor);

void Simulate(pqueue ** qf, pqueue * mq, int num_floors);

float CalculateMeanTime(pqueue * mq);

#endif
