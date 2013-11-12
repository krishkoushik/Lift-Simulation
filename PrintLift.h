#ifndef PRINT_LIFT
#define PRINT_LIFT
#include "Lift.h"
#include "Simulate.h"

//Function prototype for printing out the lift,ie, the state of the system at each instant of time.
void state_print(pqueue ** fq, int num_floors, State * lift1, State * lift2, int tot_time);

#endif
