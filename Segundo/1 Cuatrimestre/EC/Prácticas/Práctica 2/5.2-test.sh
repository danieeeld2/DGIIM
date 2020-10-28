#!/bin/bash

for i in $(seq 1 9); do
	rm unsigned
	gcc -x assembler-with-cpp -D TEST=$i -no-pie -nostartfiles 5.2-ConTest.s -o unsigned
	printf "__TEST%02d__%35s\n" $i "" | tr " " "-" ; ./unsigned
done
