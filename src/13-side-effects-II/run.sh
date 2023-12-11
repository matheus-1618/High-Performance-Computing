g++ -Wall -O3 pi_montecarlo.cpp -fopenmp -o pi_montecarlo

g++ -Wall -O3 pi_montecarlo_parallel_for.cpp -fopenmp -o pi_montecarlo_parallel_for

g++ -Wall -O3 pi_montecarlo_parallel_for2.cpp -fopenmp -o pi_montecarlo_parallel_for2

./pi_montecarlo

./pi_montecarlo_parallel_for

./pi_montecarlo_parallel_for2

