###############################################################################
# makefile
###############################################################################

SHELL := /bin/bash
.ONESHELL:

###############################################################################

SRC = $(wildcard *.c *.cc)
EXE = $(basename $(SRC))
ATT = $(EXE:=.att)
DAT = $(EXE:=.dat)
OPT = $(shell [ "$${PWD: -2}" == "3s" ] && echo "-O3" || echo "-Os")
PIE = $(shell grep fedora /proc/version &> /dev/null || echo '-no-pie')
PNG = $(DAT:.dat=.png) $(DAT:.dat=-log.png)
SVG = $(DAT:.dat=.svg) $(DAT:.dat=-log.svg)

PLT =  "set terminal svg enhanced background rgb 'white'; \
		set output '$@'; \
		set key top center horizontal; \
		set grid; \
		set ylabel 'total time (μs)'; \
		set y2label 'cpu cycles'; \
		set xtics rotate; \
		set ytics; \
		set ytics nomirror; \
		set y2tics; \
		set y2tics nomirror; \
		set style fill solid 0.10 border; \
		set boxwidth 0.80; \
		unset logscale y; \
		unset logscale y2; \
		plot '$<' u 5:xtic(1) w boxes axes x1y1 title 'total time', \
		     '$<' u 3:xtic(1) w lp pt 7 axes x1y2 title 'cycles'"

###############################################################################

CXXFLAGS = -march=native $(OPT) $(PIE) -pthread -std=c++2a -Wall

###############################################################################

all: att svg

att: $(ATT)

clean:
	-rm -fv $(ATT) $(DAT) $(EXE) $(PNG) $(SVG) core.* perf.* *~
	-find -maxdepth 2 -mindepth 2 -iname makefile -execdir make -k '$@' \;

exe: $(EXE)

png: $(PNG)

svg: $(SVG)

###############################################################################

%.att: %
	objdump -C -d $< > $@

%.dat: %
	./$< | tee $@

%.data: %
	perf record -B -F max -o $@ -- ./$<

%.perf: %.data
	perf report -i $<

%.png: %.dat makefile
	@gnuplot <<< $(subst svg enhanced background rgb 'white',pngcairo enhanced,$(PLT))

%-log.png: %.dat makefile
	@gnuplot <<< $(subst svg enhanced background rgb 'white',pngcairo enhanced,$(PLT:unset=set))

%.svg: %.dat makefile
	@gnuplot <<< $(PLT)

%-log.svg: %.dat makefile
	@gnuplot <<< $(PLT:unset=set)

###############################################################################

.PHONY: all att clean exe png svg
.PRECIOUS: $(DAT)
.NOEXPORT:

###############################################################################
