SHELL := /bin/bash
.ONESHELL:

ATT = $(EXE:=.att)
EXE = $(basename $(SRC))
SRC = $(wildcard *.c *.cc)

CFLAGS = -fno-guess-branch-probability -no-pie -Og -Wall
#CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS) -std=c++14

all: att

att: $(ATT)

clean:
	-rm -fv $(ATT) $(EXE) *~

exe: $(EXE)

gdb:
	@if ! grep 'set auto-load safe-path /' ~/.gdbinit; then
		echo 'set auto-load safe-path /' >> ~/.gdbinit
	fi > /dev/null
	if ! grep 'set print asm-demangle' ~/.gdbinit; then
		echo 'set print asm-demangle' >> ~/.gdbinit
	fi
%.att: %
	objdump -Cd $< > $@

hebras: CXXFLAGS+=-pthread

.PHONY: all att clean exe gdb

