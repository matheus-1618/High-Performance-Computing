#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>
#define  N  100000

using namespace std;

int main(){
    double sum = 0;
    double init_time, final_time;
    init_time = omp_get_wtime();
    
    #pragma omp parallel
    {   
        #pragma omp parallel for num_threads(4) reduction(+:sum)
        for (int i = 0; i < N; i++){
            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            //int tid = omp_get_thread_num();
            int tid = omp_get_thread_num();
            default_random_engine generator(seed);
            uniform_real_distribution<double> distribution(0.0, 1.0);
            double x = (double) distribution(generator);
            double y = (double) distribution(generator);
            if (x*x + y*y <= 1){
                #pragma omp critical
                sum += 1;
            }
        }
    }
    final_time = omp_get_wtime() - init_time;
    cout <<"Pi Monte carlo Parallel For2: "<< std::setprecision(15)<< 4 * sum / N << endl << "Time: " << final_time  <<"\n"<<endl;
    return 0;
}