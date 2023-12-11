#include <iostream>
#include <unistd.h>
#include <cmath>
#include <algorithm>
#include <omp.h>
using namespace std;


double leibiniz_series(int N){
    double sum = 0;
    double tdata = omp_get_wtime();
    for (int i = 0; i < N; i++){
        sum += pow(-1,i) / (2*i + 1);
    }
    tdata = omp_get_wtime() - tdata;
    cout << "Time to run: " << tdata << endl;
    return sum;
}

int main(){
    int N = 10000000;
    double sum = leibiniz_series(N);
    cout << "For N = " << N << " the answer is " << sum*4 << endl;
    return 0;

}