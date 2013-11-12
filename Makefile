all : lift_simulator

lift_simulator : Main.o Lift.o Simulate.o PrintLift.o
	gcc Main.o Lift.o Simulate.o PrintLift.o -o lift_simulator

Main.o : Main.c Lift.h Simulate.h
	gcc -o Main.o -c Main.c 

Lift.o : Lift.c Lift.h
	gcc -c Lift.c -o Lift.o

Simulate.o : Simulate.c Simulate.h Lift.h PrintLift.h
	gcc -c Simulate.c -o Simulate.o

PrintLift.o : PrintLift.c PrintLift.h Lift.h Simulate.h
	gcc -c PrintLift.c -o PrintLift.o

clean : 
	rm -f Main.o Lift.o Simulate.o lift_simulator
