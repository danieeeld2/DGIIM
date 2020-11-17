.ONESHELL:

ASM = $(filter-out suma_06_CS_s.s, $(wildcard *.s))
ATT = $(EXE:=.att)
DAT = $(EXE:=.data)
EXE = $(basename $(ASM) $(SRC))
PER = $(EXE:=.perf)
PIE = $(shell grep fedora /proc/version &> /dev/null || echo '-no-pie')
SRC = $(filter-out 3a.c suma_03_SC_c.c suma_04_SC_c.c, $(wildcard *.c *.cc))

ASFLAGS  = -g $(PIE) -nostartfiles -Os
CFLAGS   = -g $(PIE) -Os -Wall
CXXFLAGS = $(CFLAGS:-Os=-O3) -march=native

all: $(EXE) $(ATT)

clean:
	-rm -fv $(ATT) $(DAT) $(EXE) $(PER) *.data.old *~
	-find -maxdepth 2 -mindepth 2 -iname makefile -execdir make -k '$@' \;

test: $(sort $(EXE))
	@lpad() { printf "%$$(( 16 - $${#1} ))s$$1"; }
	for i in $^; do
		lpad "$$i: "
		./$$i > /dev/null && echo ok || echo failed
	done

suma_03_SC_s: suma_03_SC_c.c
suma_04_SC_s: suma_04_SC_c.c
suma_06_CS_c: suma_06_CS_s.s
suma_09_Casm: CFLAGS+=-march=native -O3

%.att: %
	objdump -Cd $< > $@

%.data: %
	sudo sh -c 'echo -1 > /proc/sys/kernel/perf_event_paranoid'
	perf record --call-graph dwarf --freq=max -o $@ -- ./$<

%.perf: %.data
	perf report -i $<

.PHONY: all clean
.PRECIOUS: $(DAT)

3: 3a.c 3.s
