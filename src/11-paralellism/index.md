# 10 - Introdução a paralelismo

OpenMP é uma tecnologia de computação multi-core usada para paralelizar programas. Sua principal vantagem é oferecer uma transição suave entre código sequencial e código paralelo.

Fizemos em sala de aula uma série de programas básicos no OpenMP e agora é a hora de praticar.

## Cálculo do PI por meio de uma série infinita de Leibniz

Você sabia que é possível calcular o valor do PI por meio de uma série infinita de Leibniz? Veja abaixo:

$$ 1 - \frac{1}{3} + \frac{1}{5} - \frac{1}{7} + \frac{1}{9} - \dots  = \frac{\pi}{4} $$


$$  \sum_{0}^{\infty} = \frac{(-1)^n}{2n + 1} = \frac{\pi}{4} $$

Essa série converge muito lentamente, o que é bom para nós. 

### Sua tarefa

Implemente a versão serial do cálculo do PI a partir da série infinita de Leibniz. Faça `n = 1000000000`. 


Após implementar a versão serial e calcular o tempo de sua execução, implemente a versão em `openmp`. Você deve fazer sua implementação de duas formas:

a) A primeira implementação você deve trabalhar com `2` threads e a partir do `id` da thread, você deve dividir a soma em duas partes, cada thread executando a sua porção.

b) A segunda implementação você deve trabalhar com `for` do openmp e tratar como uma `redução` do valor de PI. Calcule o tempo de execução.  


O speedup é uma métrica que representa a razão entre o tempo de execução de um programa sequencial e o tempo de execução de sua versão paralela. Por isso, trata-se de uma boa medida para avaliarmos quantitativamente a melhoria trazida pela versão paralela de um programa paralelo em relação à sua versão sequencial. Calcule também o speed up de cada uma das soluções.

## Tasks (tarefas) em OpenMP

Vamos agora criar *tarefas* que podem ser executadas em paralelo.

!!! tip "Definição"
    Uma **tarefa** é um bloco de código que é rodado de maneira paralela usando OpenMP. *Tarefas* são agendadas para cada uma das *threads* criadas em um região paralela. Não existe uma associação **1-1** entre *threads* e *tarefas*. Posso ter mais *tarefas* que *threads* e mais *threads* que *tarefas*.

Veja abaixo um exemplo de criação de tarefas.

```cpp
#pragma omp parallel
{
    #pragma omp task
    {
        std::cout << "Estou rodando na tarefa " << omp_get_thread_num() << "\n";
    }
}
std::cout << "eu só rodo quanto TODAS tarefas acabarem.\n";
```

!!! question choice
    O exemplo acima cria quantas tarefas, supondo que `OMP_NUM_THREADS=4`?

    - [ ] 1
    - [x] 4, uma para cada thread
    - [ ] Nenhuma das anteriores


    !!! details
        Como cada thread roda o código da região paralela, cada uma cria exatamente um tarefa.


Para controlar a criação de tarefas em geral usamos a diretiva `master`, que executa somente na thread de índice `0`. Assim conseguimos criar código legível e que deixa bem claro quantas e quais tarefas são criadas.

```cpp
#pragma omp parallel
{
    #pragma omp master
    {
        std::cout << "só roda uma vez na thread:" << omp_get_thread_num() << "\n";
        #pragma omp task
        {
            std::cout << "Estou rodando na thread:" << omp_get_thread_num() << "\n";
        }
    }
}
```

Somente lendo o código acima, responda as questões abaixo.

!!! question choice
    Quantas tarefas são criadas no exemplo acima?

    - [x] 1
    - [ ] N, uma para cada thread
    - [ ] Nenhuma das anteriores

!!! question choice
    A(s) tarefa(s) criada(s) roda(m) em qual thread?

    - [ ] 0
    - [ ] 1
    - [x] Impossível dizer. Em cada execução rodará em uma thread diferente.

!!! example
    Complete *exercicio1.cpp* criando duas tarefas. A primeira deverá rodar `funcao1` e a segunda `funcao2`. Salve seus resultados nas variáveis indicadas no código.

!!! question short
    Leia o código e responda. Quanto tempo o código sequencial demora? E o paralelo? Verifique que sua implementação está de acordo com suas expectativas.

    !!! details
        Sequencial demora a soma dos tempos das duas funções. Paralelo demora o tempo da maior delas.
