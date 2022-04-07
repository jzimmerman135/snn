# Makefile for Spike Timing Learning Dependent Learning
# Simulated Analogue Spiking Neural Network
#
# a.k.a. STDPSASNN or ZimNET
#
# This included information to build the network and to create
# data to run the network with
#
#
# Created: April 6, 2022 by Jacob Zimmerman


################ Variables ###################

CC = gcc

IFLAGS = -I./include

CFLAGS = -g -std=gnu99 -O3 -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)

LDFLAGS = -g -L./src

LDLIBS = 

INCLUDES = $(shell echo *.h)

################# Build rules #################

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

snn: network.o layer.o neuron.o models.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -f *.o
