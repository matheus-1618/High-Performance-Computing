#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/sort.h>
#include <thrust/copy.h>
#include <thrust/random.h>
#include <vector>
#define N 10
using namespace std;

int main() {
  thrust::device_vector<float> x(N);
  thrust::sequence (x.begin(), x.end());

  float media = thrust::reduce(x.begin(), x.end()) / x.size();

  //thrust::device_vector<float> mu(N);
  //thrust::fill(mu.begin(), mu.end(), media);
  thrust::constant_iterator<float> mu(media);
  thrust::constant_iterator<float> end= mu + N;
  thrust::transform(x.begin(), x.end(), mu, x.begin(), thrust::minus<float>());
  thrust::transform(x.begin(), x.end(), x.begin(), thrust::square<float>());
  float variance = thrust::reduce(x.begin(), x.end()) / N;
  std::cout << "variancia: " << variance << std::endl;
  return 0;
}
