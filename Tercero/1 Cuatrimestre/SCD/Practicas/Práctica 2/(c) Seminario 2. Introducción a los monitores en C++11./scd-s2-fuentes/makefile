.SUFFIXES:
.PHONY: x1, x2, clean

compilador:=g++
opcionesc:= -std=c++11 -pthread -Wfatal-errors

x1: monitor_em_exe
	./$<

x2: barrera1_sc_exe
	./$<

x3: barrera2_sc_exe
	./$<

x4: barrera2_su_exe
	./$<

x5: prodcons1_sc_exe
	./$<

x6: prodcons2_sc_exe
	./$<

x7: prodcons2_su_exe
	./$<

monitor_em_exe: monitor_em.cpp scd.h
	$(compilador) $(opcionesc)  -o $@ $<

barrera1_sc_exe: barrera1_sc.cpp scd.h
	$(compilador) $(opcionesc)  -o $@ $<

barrera2_sc_exe: barrera2_sc.cpp scd.h
	$(compilador) $(opcionesc)  -o $@ $<

barrera2_su_exe: barrera2_su.cpp scd.cpp scd.h
	$(compilador) $(opcionesc)  -o $@ $< scd.cpp

prodcons1_sc_exe: prodcons1_sc.cpp scd.h
	$(compilador) $(opcionesc)  -o $@ $<

prodcons2_sc_exe: prodcons2_sc.cpp scd.h
	$(compilador) $(opcionesc)  -o $@ $<

prodcons2_su_exe: prodcons2_su.cpp scd.cpp scd.h
	$(compilador) $(opcionesc)  -o $@ $<  scd.cpp

clean:
	rm -f *_exe
