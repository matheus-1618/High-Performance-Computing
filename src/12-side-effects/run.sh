g++ -Wall -fopenmp  -O3 pi_recursivo.cpp -o pi_recursivo
g++ -Wall -fopenmp  -O3 pi_recursivo_paralell_for.cpp -o pi_recursivo_parallel_for
g++ -Wall -fopenmp  -O3 pi_recursivo_tasks.cpp -o pi_recursivo_tasks

./pi_recursivo

./pi_recursivo_parallel_for

./pi_recursivo_tasks