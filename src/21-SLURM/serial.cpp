#include <iostream>
using namespace std;

int main(){
  int i; nb_rec = 10000000;
  double x, n, sum = 0.0, pi 0.0;
  h = 1.0 / nb_rec;
  for (i = 0; i<nb_rec; i++){
    x = (i+0.5)*h;
    sum += 4.0 / (1.0 + x*x);
  }
  pi = h * sum;
  cout << " O Valor aproximado de PI é: " << pi << endl;
  return 0;
}
