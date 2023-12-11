# Thrust - Operações customizadas

Vamos conhecer como criar operações customizadas com Thrust. Para isso, vamos resolver um problema clássico denominado `Saxpy`, o que significa `Single precision A X plus Y` . Na prática, consiste em calcular um valor `z`, que é dado por `ax + y`, onde `a` é uma constante e `x` e `y` são vetores.

O código-fonte abaixo resolve o `Saxpy` em C++/Thrust. Vamos avaliá-lo.

```c++
 #include <thrust/host_vector.h>
 #include <thrust/device_vector.h>
 #include <thrust/generate.h>
 #include <thrust/functional.h>
 #include <thrust/copy.h>
 #include <cstdlib>
 #include <algorithm>
 #include <iostream>
 #include <iomanip>

 using namespace  std;
 
struct saxpy
{
    int a;    
    saxpy(int a_) : a(a_) {};
    __host__ __device__
    double operator()(const int& x, const int& y) {
           return a * x + y;
    }
};

int main(int argc, char* argv[]) {
     if (argc != 3) {
         cerr <<
          "***Numero incorreto de argumentos ***\n";
         return 1;
     }

     int n = atoi(argv[1]);
     int m = atoi(argv[2]);

     //gerar numeros aleatorios
     thrust::host_vector<int> a(n);
     thrust::host_vector<int> b(n);
     thrust::host_vector<int> c(n);
     thrust::generate(a.begin(), a.end(), rand);
     thrust::generate(b.begin(), b.end(), rand);

     //transferimos para a GPU
     thrust::device_vector<int> d_a = a;
     thrust::device_vector<int> d_b = b;

     //transformacao
     
     thrust::transform(d_a.begin(), d_a.end(),
                       d_b.begin(), d_b.end(),
                       saxpy(m));
    
     thrust::copy(d_b.begin(), d_b.end(),
     c.begin()); 

     for (int i = 0; i < n; i++ )
         cout << setw(6) << c[i] << " = " 
          << setw(2) << m
          << "*" << setw(5) << a[i]
          << "+" << setw(5) << b[i]
          << endl;

}



```



## Operações customizadas em `transform`

Para criar nossas próprias operações usamos a seguinte sintaxe:

```.cpp
struct custom_transform
{
    // essas marcações indicam que o código deve ser compilado para CPU (host) 
    // e GPU (device)
    // IMPORTANTE: somente código com a marcação __device__ é compilado para GPU
    __host__ __device__
    
        double operator()(const double& x, const double& y) {
            // isto pode ser usado com um transform que usa dois vetores 
            // e coloca o resultado em um terceiro.
            
            // x é um elemento do primeiro vetor
            // y é o elemento correspondente do segundo vetor
            
            // o valor retornado é colocado no vetor de resultados
            
            // para fazer operações unárias basta receber somente um argumento.
        }
};
```

A operação acima seria aceita em um transform como o abaixo:


```cpp
thrust::device_vector<double> A, B, C;
thrust::transform(A.begin(), A.end(), B.begin(), C.begin(), custom_transform());
```

Note que os tipos dos vetores devem bater com os tipos declarados no `struct`. Por vezes precisamos receber parâmetros para a operação customizada funcionar. Um truque comum é adicionar atributos no `struct` usado como operação:

```cpp
struct T {
    int attr;

    T(int a): attr(a) {};

    // TODO: operação customizada aqui
};
```

O valor `attr` estará disponível para uso dentro da operação customizada. A linha `T(int a): attr(a) {}` declara o construtor do `struct T`. Ela faz com que o atributo `attr` seja inicializado com o valor do parâmetro `a`. Se houver mais de uma atribuição parâmetro - atributo é só usar `,` para separar as inicializações. 


# Calculando a norma / magnitude de um vetor

A magnitude de um vetor consiste na raiz quadrada da soma do quadrado de seus elementos. Dessa forma, você deve complementar o código abaixo, de modo a criar uma transformação customizada `square`, a qual faz uma transformação no vetor transformando os seus elementos ao quadrado, e posteriormente você deve fazer uma redução, de modo a obter a magnitude do vetor.

```c++
 #include <iostream>
 #include <iomanip>
 #include <cstdlib>
 #include <chrono>
 #include <cstdlib>
 #include <algorithm>
//INSIRA AS IMPORTACOES NECESSARIAS DA THRUST
 #include <cmath>
 #include <random>
 
 using namespace std::chrono;

 void reportTime(const char* msg, steady_clock::duration span) {
     auto ms = duration_cast<milliseconds>(span);
     std::cout << msg << " - levou - " <<
      ms.count() << " milisegundos" << std::endl;
 }

 // CRIE UMA FUNCTOR PARA CALCULAR A SQUARE



 // IMPLEMENTE O CALCULO DA MAGNITUDE COM THRUST
 float magnitude(                    ) {
     float result;

     // ... add Thrust calls
     // AQUI VAO AS CHAMADAS THRUST 

     return result;
 }

 int main(int argc, char** argv) {
     if (argc != 2) {
         std::cerr << argv[0] << ": numero invalido de argumentos\n"; 
         std::cerr << "uso: " << argv[0] << "  tamanho do vetor\n"; 
         return 1;
     }
     int n = std::atoi(argv[1]); //numero de elementos
     steady_clock::time_point ts, te;

     // Faça um  vector em thrust 
    


     // inicilize o  vector
     ts = steady_clock::now();
     
     std::generate(                ,                      , std::rand);
  
     
     te = steady_clock::now();
     reportTime("Inicializacao", te - ts);

     // Calcule a magnitude do vetor
     ts = steady_clock::now();
     float len = magnitude(v_d);
     te = steady_clock::now();
     reportTime("Tempo para calculo", te - ts);

    
     std::cout << std::fixed << std::setprecision(4);
     std::cout << "Magnitude : " << len << std::endl;
 }


```

# Fusion

Há operações de transformação e redução feitas anteriormente que realizam muita troca de dados. Seria possível otimizar isso?

A resposta é sim. A Thrust possui o conceito de `fusion kernel`, o que representa uma estratégia para otimizar transformações e reduções. Modifique o código anteriormente desenvolvido, agora fazendo uso da transformação abaixo:

```c++

std::sqrt(thrust::transform_reduce( v.begin(), v.end(), unary_op, init, binary_op));

```

Pergunta: para o problema da magnitude, quem é a `unary_op` e a `binary_op`? Qual o valor de `init`? 