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

MAKE_DIR = $(PWD)

CC = gcc

INCLUDE_DIR := $(MAKE_DIR)/include
SRC_DIR := $(MAKE_DIR)/src

IFLAGS = -I$(INCLUDE_DIR) -I$(SRC_DIR)

CFLAGS := -g -std=c99 -O3 -Wall -Wextra -Werror -Wfatal-errors -pedantic
CFLAGS += $(IFLAGS)

LDFLAGS :=
LDLIBS = -lpthread

INCLUDES = $(shell echo *.h)

OBJECTS = network.o layer.o neuron.o models.o

################# Build rules #################

%.o: src/%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDLIBS)

snn: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -f *.o
