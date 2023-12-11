#include <omp.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
static long num_steps = 1024l*1024*1024*2;

#define MIN_BLK  1024*1024*256


double pi_r(long Nstart, long Nfinish, double step) {
    long i,iblk;
    double a,b;
    if (Nfinish-Nstart < MIN_BLK){
        double sum = 0;
        for (i = Nstart; i < Nfinish; i++){
            double x = (i+0.5)*step;
            sum += 4.0/(1.0+x*x); 
        }
        return sum;
    } else {
        iblk = Nfinish-Nstart;
        #pragma omp task  shared(a)
        a = pi_r(Nstart, Nfinish-iblk/2, step);
        #pragma omp task shared (b)
        b = pi_r(Nfinish-iblk/2, Nfinish, step);
        #pragma omp taskwait
        return a+b;
    }
}

int main () {
    long i;
    double step, pi;
    double init_time, final_time;
    step = 1.0/(double) num_steps;
    init_time = omp_get_wtime();
    double c;
    #pragma omp parallel
    #pragma omp single
    {
        c = pi_r(0, num_steps, step);
    }
    
    pi = step * c;
    final_time = omp_get_wtime() - init_time;

    std::cout << "Tasks:" << std::endl;
    std::cout << "for " << num_steps << " steps pi = " << std::setprecision(15) << pi << " in " << final_time << " secs\n";
}
