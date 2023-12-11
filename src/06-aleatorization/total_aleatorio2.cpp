#include <random>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

default_random_engine generator(10);
struct  item {
    int id;
    double peso;
    double valor;
};

bool my_compare_valor(item a, item b){
  return a.valor > b.valor;
}

bool my_compare_peso(item a, item b){
  return a.peso < b.peso;
}

double random_number(int start, int end){
    uniform_real_distribution<double> distribution(start, end);
    return distribution(generator);
}

bool is_in_vector(vector<int> indexes, int number){
    for (size_t i = 0; i < indexes.size(); i++){
        if (indexes[i] == number){
            return true;
        }
    }
    return false;
}

void aleatorio(vector<item> itens, size_t N, int W){
    sort(itens.begin(), itens.end(), my_compare_valor);

	double peso = 0;
	double valor = 0;
	vector<size_t> resposta;
    size_t T = 0;
    vector<int> indexes;

    while (peso < W){
        int j = random_number(0,itens.size()-1);
        if (!is_in_vector(indexes, j)){
            
            if (peso + itens[j].peso <= W){
                indexes.push_back(j);
                resposta.push_back(itens[j].id);
                peso += itens[j].peso;
                valor += itens[j].valor;
                T++;
            }
            else{
                break;
            }
        }
    }
    
    cout << peso << " " << valor << " " << "0"  << "\n";

    for (size_t i = 0; i < T; i++){
		cout << resposta[i] << " ";
	}
}

int main(){
    vector<item> itens;
    size_t N;
    int W;
    cin >> N;
    cin >> W;
 	for (size_t i = 0; i < N; i++){
		item t;
		t.id = i;
		cin >> t.peso;
		cin >> t.valor;
		itens.push_back(t);
	}
    cout << "Aleatorio2 agora" << endl;
    aleatorio(itens, N, W);

    return 0;
}