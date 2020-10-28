#!/bin/bash

for i in $(seq 1 19); do
	rm suma
	gcc -x assembler-with-cpp -D TEST=$i -no-pie -nostartfiles 5.3-ConTest.s -o suma
	printf "__TEST%02d__%35s\n" $i "" | tr " " "-" ; ./suma
done
