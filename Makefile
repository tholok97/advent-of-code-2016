# Makefile for all days
# NOTE: I'm still learning gnu make, so this stuff is probably not optimal. 
# (jeg jørs på det)

CC=g++
CFLAGS= -w -std=c++14 -fpermissive
INCLUDE= -Iinclude/

DAYCPPS=$(sort $(wildcard src/day*.cpp))
DAYEXES=$(patsubst src/day%.cpp,bin/day%.out,$(DAYCPPS))
DAYNUMS=$(patsubst src/day%.cpp,%,$(DAYCPPS))

$(info $(DAYCPPS))
$(info $(DAYEXES))
$(info $(DAYNUMS))

all: $(DAYEXES)

%: bin/%.out
	$(info ############################################## RUNNING $<)
	$<

bin/day%.out: src/day%.cpp
	$(info ############################################## BUILDING $@)
	$(CC) $(CFLAGS) $(INCLUDE) $(wildcard $<) -o $@

clean:
	rm -f $(DAYEXES)

.PHONY: clean
.SECONDARY:
