#!/bin/bash

echo "STATIC MONOTONIC CHUNK=1\n"
export OMP_SCHEDULE="monotonic:static,1"
./pmtv-OpenMP 12800

echo "DYNAMIC MONOTONIC CHUNK=1\n"
export OMP_SCHEDULE="monotonic:dynamic,1"
./pmtv-OpenMP 12800

echo "GUIDED MONOTONIC CHUNK=1\n"
export OMP_SCHEDULE="monotonic:guided,1"
./pmtv-OpenMP 12800

echo "STATIC MONOTONIC CHUNK=64\n"
export OMP_SCHEDULE="monotonic:static,64"
./pmtv-OpenMP 12800

echo "DYNAMIC MONOTONIC CHUNK=64\n"
export OMP_SCHEDULE="monotonic:dynamic,64"
./pmtv-OpenMP 12800

echo "GUIDED MONOTONIC CHUNK=64\n"
export OMP_SCHEDULE="monotonic:guided,64"
./pmtv-OpenMP 12800

