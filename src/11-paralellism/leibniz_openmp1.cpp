#include <iostream>
#include <unistd.h>
#include <cmath>
#include <algorithm>
#include <omp.h>

using namespace std;


double leibiniz_series(int N){
    double sum = 0;
    #pragma omp parallel
    {
        omp_set_num_threads(2);
        int id, i, nthreds, istart, iend;
        id = omp_get_thread_num();
        nthreds = omp_get_num_threads();
        cout << "id: " << id  << endl;
        istart = id * N / nthreds;
        iend = (id+1) * N/ nthreds;
        if (id == nthreds-1) iend = N;
        for (i = istart; i < iend; i++){
            sum += pow(-1,i) / (2*i + 1);
        }
    }
    return sum;
}

int main(){
    int N = 1000000000;
    double sum = leibiniz_series(N);
    cout << "For N = " << N << " the answer is " << sum*4 << endl;
    return 0;

}