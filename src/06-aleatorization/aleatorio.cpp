#include <random>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

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

double random_number(float start, float end){
    default_random_engine generator;
    uniform_real_distribution<double> distribution(start, end);
    return distribution(generator);
}

void caro(vector<item> itens, size_t N, int W){
    sort(itens.begin(), itens.end(), my_compare_valor);

	double peso = 0;
	double valor = 0;
	vector<size_t> resposta;
    size_t T = 0;

    for (size_t j = 0; j < N; j++){
        int k;
        if (random_number(0.0,1.0) >= 0.25){
            k = random_number(j,itens.size()-1);
        }
        else{
            k = j;
        }
        if (peso + itens[k].peso < W){
            resposta.push_back(itens[k].id);
            peso += itens[k].peso;
            valor += itens[k].valor;
            T++;
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
    cout << "Caro agora" << endl;
    caro(itens, N, W);

    return 0;
}