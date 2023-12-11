#include <iostream>
#include <mpi.h>
using namespace std;

int main(){
  int i, nb_rec = 10000000;
  double x, h, pi =  0.0;
  int myRank, size, tag = 10;
  int retangulos;
  int meu_inicio, meu_fim;
  double minha_soma = 0.0;
  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Status status;
  if (myRank == 0) {
      retangulos = nb_rec / size;
  }
  MPI_Bcast(&retangulos,1,MPI_INT,0,MPI_COMM_WORLD);

  h = 1.0 / (retangulos * size);
  pi = h*minha_soma;
  meu_inicio = myRank * retangulos;
  meu_fim = meu_inicio+retangulos;
  for (i = meu_inicio; i < meu_fim; i++){
    x = (i+0.5)*h;
    minha_soma += 4.0 / (1.0+x*x);
  }
 minha_soma = h*minha_soma;
  MPI_Reduce(&minha_soma, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (myRank == 0)
    cout << " O valor aproximado de  PI é: " << pi << endl;
  MPI_Finalize();
  return 0;
}
