#!/bin/bash
#SBATCH -n 5

mpirun --allow-run-as-root -np 5 ./broadcast
