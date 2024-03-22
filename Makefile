CC=gcc
CFLAGS= -Wall -Wextra -g
DEPS = core/Banker.h core/Saftey.h
OBJ = Simulation.c core/Saftey.c core/Banker.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

BankerAlgorithm: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm BankerAlgorithm