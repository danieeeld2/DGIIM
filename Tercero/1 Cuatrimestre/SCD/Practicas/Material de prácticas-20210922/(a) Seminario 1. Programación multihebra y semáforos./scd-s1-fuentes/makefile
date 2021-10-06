### usar con 'make x01', 'make x02' ..... 'make x12', o 'make xs13'

.SUFFIXES:
.PRECIOUS: ejemplo%_exe ejemplo%s_exe

isdarwin   := $(filter Darwin,$(shell uname -s))
compilador := $(if $(isdarwin), clang++, g++)
flags      := -std=c++11 -pthread -O3

x%: ejemplo%_exe
	./$<

ejemplo%_exe: ejemplo%.cpp
	$(compilador) $(flags)  -o $@ $<

xs%: ejemplo%s_exe
	./$<

ejemplo%s_exe: ejemplo%-s.cpp
		$(compilador) $(flags)  -o $@ $< scd.cpp

clean:
	rm -f *_exe
