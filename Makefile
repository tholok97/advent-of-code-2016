# Makefile for all days
# NOTE: I'm still learning gnu make, so this stuff is probably not optimal. 
# (jeg jørs på det)

CC=g++
CFLAGS= -w -std=c++14 -fpermissive
INCLUDE= -Iinclude/

DAYCPPS=$(sort $(wildcard src/aoc*.cpp))
DAYEXES=$(patsubst src/aoc%.cpp,bin/aoc%.out,$(DAYCPPS))
DAYNUMS=$(patsubst src/aoc%.cpp,%,$(DAYCPPS))

all: $(DAYEXES)

%: bin/aoc%.out
	$(info ############################################## RUNNING $<)
	$<

bin/aoc%.out: src/aoc%.cpp
	$(info ############################################## BUILDING $@)
	$(CC) $(CFLAGS) $(INCLUDE) $(wildcard $<) -o $@

clean:
	rm -f $(DAYEXES)

.PHONY: clean
.SECONDARY:
