#!/bin/bash
#SBATCH --ntasks=1

# Script para atcgrid

vec=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 32)
for i in "${vec[@]}"; do
		export OMP_NUM_THREADS=$i
		echo "$i 7k"
		./pmv 7000
		echo "$i 50k"
		./pmv 50000
done
