#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>
#define  N  100000

using namespace std;

int main(){
    //unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    double sum = 0;
    double init_time, final_time;
    init_time = omp_get_wtime();
    
    default_random_engine generator(10);
    uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < N; i++){
        double x = (double) distribution(generator);
        double y = (double) distribution(generator);
        if (x*x + y*y <= 1){
            sum += 1;
        }
    }
    final_time = omp_get_wtime() - init_time;
    cout <<"Pi Monte carlo: "<< std::setprecision(15)<< 4 * sum / N << endl << "Time: " << final_time <<"\n"<< endl;
    return 0;

}