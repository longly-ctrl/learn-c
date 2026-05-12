CFLAGS=-Wall -g

all: ex19

ex19: object.o

test:ex19
	@echo "look around"
	@printf "l\n" | ./ex19	
clean:
	rm -f ex19 object.o
