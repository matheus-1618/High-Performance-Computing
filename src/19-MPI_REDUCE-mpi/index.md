# 19 - Operações de Redução em MPI

Reduzir é um conceito clássico da programação funcional. A redução de dados envolve a redução de um conjunto de números em um conjunto menor de números por meio de uma função. Por exemplo, digamos que temos uma lista de números [1, 2, 3, 4, 5]. Reduzir esta lista de números com a função sum produziria sum([1, 2, 3, 4, 5]) = 15. Da mesma forma, a redução da multiplicação resultaria em multiplicar([1, 2, 3, 4, 5]) = 120.

Como você deve ter imaginado, pode ser muito complicado aplicar funções de redução em um conjunto de números distribuídos. Junto com isso, é difícil programar de forma eficiente reduções não comutativas, ou seja, reduções que devem ocorrer em uma ordem definida. Felizmente, o MPI tem uma função útil chamada MPI_Reduce que irá lidar com quase todas as reduções comuns que um programador precisa fazer em um aplicativo paralelo.

Para iniciarmos o nosso estudo de reduções em MPI, abra o seguinte notebook no Google Colab e siga as instruções contidas:

[Reduções em MPI](https://colab.research.google.com/drive/17PYAsKifOgbFmnRnboaZ3WV2hI6bv8pD?usp=sharing) Dica: Faça uma cópia do notebook para a sua conta do Colab, no menu File (ou Arquivo), opção Save a Copy in Drive (Salvar uma cópia no Drive). 
