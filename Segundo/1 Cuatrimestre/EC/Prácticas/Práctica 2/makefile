SHELL = bash
.ONESHELL:

ASM = $(wildcard *.s)
ATT = $(EXE:=.att)
SRC = $(wildcard *.cc)
EXE = $(basename  $(ASM) $(SRC))

ASFLAGS = -g -no-pie -nostartfiles
CFLAGS = -g -no-pie -Os -Wall
CXXFLAGS = $(CFLAGS)

all: $(ATT)

clean:
	-rm -fv $(ATT) $(EXE) core.* *~

test: $(EXE)
	@for i in {,un}signed{32,64}; do
		echo "#############################################################"
		echo "$$i"
		echo "#############################################################"
		./$$i
	done

%.att: %
	objdump -Cd $< > $@

.PHONY: all clean test

