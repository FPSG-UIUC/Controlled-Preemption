TARGETS=build

all: $(TARGETS)

constant_length_victim.o: generate_constant_length_victim.py
	python generate_constant_length_victim.py
	gcc -g -c constant_length_victim.c -o constant_length_victim.o 

build: constant_length_victim.o attack_nanosleep.c
	gcc constant_length_victim.o -o constant_length_victim
	gcc attack_nanosleep.c -o attack_nanosleep
	gcc attack_posix_timer.c -o attack_posix_timer

clean:
	rm constant_length_victim attack_nanosleep attack_posix_timer
	rm -f *.o


