###############################################################################
# makefile
###############################################################################

SHELL = bash
.ONESHELL:

EXE = $(basename $(SRC))
LOG = $(shell echo 1{0,1}.log)
SRC = $(wildcard *.c *.cc)
SVG = $(shell echo 1{0,1}{,l}.svg)

CFLAGS = -fopenmp -O3 -Wall
CXXFLAGS = $(CFLAGS)

N = 10000000
R = 25

PLOT = set terminal svg enhanced; \
	   set output '$@'; \
	   set key autotitle columnheader top left noenhanced; \
	   set grid; \
	   set xlabel 'n'; \
	   set ylabel 'time (ms)'; \
	   set logscale x 2; \
	   set xtics rotate; \
	   set xtics (1, 2, 4, 8, 16, 32, 64, 128, 256, 512, '1k' 1024, '2k' 2048, '4k' 4096, '8k' 8192, '16k' 16384, '32k' 32768, '64k' 65526, '128k' 131072, '256k' 262144, '512k' 524288, '1M' 1048576, '2M' 2097152, '4M' 4194304, '8M' 8388608, '16M' 16777216, '32M' 33554432, '64M' 67108864); \
	    plot '$<' u 1:2 w lp lc -1 ps 0.75 pt 5 t 'suma', \
	         '$<' u 1:3 w lp lc  1 ps 0.75 pt 7 t 'for', \
	         '$<' u 1:4 w lp lc  2 ps 0.75 pt 9 t 'sections';

PLOT2 = set terminal svg enhanced; \
	    set output '$@'; \
	    set key autotitle columnheader top left noenhanced; \
	    set grid; \
	    set xlabel 'n'; \
	    set ylabel 'time (s)'; \
	    set logscale x 2; \
	    set xtics rotate; \
	    set xtics (1, 2, 4, 8, 16, 32, 64, 128, 256, 512, '1k' 1024, '2k' 2048, '4k' 4096, '8k' 8192, '16k' 16384, '32k' 32768, '64k' 65526, '128k' 131072, '256k' 262144, '512k' 524288, '1M' 1048576, '2M' 2097152, '4M' 4194304, '8M' 8388608, '16M' 16777216, '32M' 33554432, '64M' 67108864); \
	     plot '$<' u 1:2 w lp ps 0.75 pt 1 t 'sec:elapsed', \
	          '$<' u 1:3 w lp ps 0.75 pt 2 t 'sec:user', \
	          '$<' u 1:4 w lp ps 0.75 pt 3 t 'sec:system', \
	          '$<' u 1:(column(3)+column(4)) w lp ps 0.75 pt 4 t 'sec:total', \
	          '$<' u 1:5 w lp ps 0.75 pt 5 t 'par:elapsed', \
	          '$<' u 1:6 w lp ps 0.75 pt 6 t 'par:user', \
	          '$<' u 1:7 w lp ps 0.75 pt 7 t 'par:system', \
	          '$<' u 1:(column(6)+column(7)) w lp ps 0.75 pt 6 t 'par:total';
###############################################################################

default: $(EXE)

all: $(SVG)

clean:
	-rm -fv $(EXE) $(LOG) $(SVG) core.* *~

comp: 7 8 suma
	@echo "#############################################"
	echo "# medición instrumentalizada                #"
	echo "#############################################"
	for i in $^; do
		echo -e "$$i:\t $$(./$$i $(N))ms"
	done
	echo "#############################################"
	echo "# medición con time...                      #"
	echo "#############################################"
	for i in $^; do
		echo -en "$$i:\t"
		/usr/bin/time -f "elapsed: %e user: %U system: %S" -- ./$$i $(N) > /dev/null
	done
	echo "#############################################"
	echo "# medición con perf stat -r $(R)...           #"
	echo "#############################################"
	for i in $^; do
		echo -en "$$i:\t"
		perf stat -r $(R) -- ./$$i $(N) |& grep 'task-clock' | tr -s ' '
	done

###############################################################################

10:
	@lpad() { printf "%*s" 10 "$$1"; }
	lprint() { lpad "$$1"; shift; (( $$# > 0 )) && lprint "$$@" || echo; }
	lprint n suma for sections
	printf "%40s\n" | tr ' ' '-'
	make -s 10.log

10.log: 7 8 suma
	@lpad() { printf "%*s" 10 "$$1"; }
	lpadf() { printf "%*s" 10 "$$(printf "%.3f" $${1/./,})"; }
	lprint() { lpadf "$$1"; shift; (( $$# > 0 )) && lprint "$$@" || echo; }
	for (( i=16384; i<134217728; i*=2 )); do
		lpad $$i
		lprint $$(./suma $$i) $$(./7 $$i) $$(./8 $$i)
	done | tee $@

10.svg: 10.log
	@gnuplot <<< "$(PLOT)"

10l.svg: 10.log
	@gnuplot <<< "set logscale y 10; $(PLOT)"

###############################################################################

11:
	@lpad() { printf "%*s" 9 "$$1"; }
	lprint() { lpad "$$1"; shift; (( $$# > 0 )) && lprint "$$@" || echo; }
	lprint '' '<------' '-- sec --' '-------->' '<------' '-- par --' '-------->'
	lprint n elapsed user system elapsed user system
	printf "%63s\n" | tr ' ' '-'
	make -s 11.log

11.log: suma 7
	@lpad() { printf "%*s" 9 "$$1"; }
	lprint() { lpad "$$1"; shift; (( $$# > 0 )) && lprint "$$@" || echo; }
	for (( i=16384; i<134217728; i*=2 )); do
		s=( $$(/usr/bin/time -f '%e %U %S' -- ./suma $$i 2>&1 > /dev/null) )
		p=( $$(/usr/bin/time -f '%e %U %S' -- ./7 $$i 2>&1 > /dev/null) )
		lprint $$i $${s[@]} $${p[@]}
	done | tee $@

11.svg: 11.log
	@gnuplot <<< "$(PLOT2)"

11l.svg: 11.log
	@gnuplot <<< "set logscale y 10; $(PLOT2)"

###############################################################################

.PHONY: 10 11 all clean comp default
.NOEXPORT:

###############################################################################
