CC=gcc
CFLAGS= -Wall -Wextra 
DEPS = Banker.h Saftey.h
OBJ = Simulation.c Saftey.c Banker.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

BankerAlgorithm: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm BankerAlgorithm