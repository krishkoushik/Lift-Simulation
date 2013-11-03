all : lift_simulator

lift_simulator : Main.o Lift.o Simulate.o
	gcc Main.o Lift.o -o lift_simulator -lncurses


Main.o : Main.c Lift.h
	gcc -o Main.o -c Main.c 
Lift.o : Lift.c Lift.h
	gcc -c Lift.c -o Lift.o

Simulate.o : Simulate.c Simulate.h
	gcc -c Simulate.c -o Simulate.o

clean : 
	rm -f Main.o Lift.o