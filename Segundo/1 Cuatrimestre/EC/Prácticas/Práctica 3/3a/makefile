.ONESHELL:

ASM = $(filter-out suma_06_CS_s.s, $(wildcard *.s))
ATT = $(EXE:=.att)
DAT = $(EXE:=.data)
EXE = $(basename $(ASM) $(SRC))
NOM =  3c.c 4c.c 6s.s suma_03_SC_c.c suma_04_SC_c.c
PER = $(EXE:=.perf)
PIE = $(shell grep fedora /proc/version &> /dev/null || echo '-no-pie')
SRC = $(filter-out $(NOM), $(wildcard *.c *.cc))

ASFLAGS  = -g $(PIE) -nostartfiles -Os
CFLAGS   = -g -march=native $(PIE) -Os -Wall
CXXFLAGS = $(CFLAGS:-Os=-O3)

all: $(EXE) $(ATT)

clean:
	-rm -fv $(ATT) $(DAT) $(EXE) $(PER) *.data.old *~
	-find -maxdepth 2 -mindepth 2 -iname makefile -execdir make -k '$@' \;

3: 3c.c 3.s
4: 4c.c 4.s
6: 6.c 6s.s

curiosidad: CXXFLAGS+=-fno-inline

suma_03_SC_s: suma_03_SC_c.c
suma_04_SC_s: suma_04_SC_c.c
suma_06_CS_c: suma_06_CS_s.s
suma_09_Casm: CFLAGS+=-march=native -O3

%.att: %
	objdump -Cd $< > $@

%.data: %
	perf record --freq max -g -o $@ -- ./$<

%.perf: %.data
	perf report -g -i $<

.PHONY: all clean
.PRECIOUS: $(DAT)
