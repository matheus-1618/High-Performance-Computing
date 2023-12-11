#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm> 

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

void leve( vector<item> itens,size_t N, int W){
    sort(itens.begin(), itens.end(), my_compare_peso);

	double peso = 0;
	double valor = 0;
	vector<size_t> resposta;
    size_t T = 0;

    for (size_t j = 0; j < N; j++){
        if (peso + itens[j].peso <= W){
            resposta.push_back(itens[j].id);
            peso += itens[j].peso;
            valor += itens[j].valor;
            T++;
        }
    }

    cout << peso << " " << valor << " " << "0"  << "\n";

    for (size_t i = 0; i < T; i++){
		cout << resposta[i] << " ";
	}

}

void caro(vector<item> itens,size_t N, int W){
    sort(itens.begin(), itens.end(), my_compare_valor);

	double peso = 0;
	double valor = 0;
	vector<size_t> resposta;
    size_t T = 0;

    for (size_t j = 0; j < N; j++){
        if (peso + itens[j].peso <= W){
            resposta.push_back(itens[j].id);
            peso += itens[j].peso;
            valor += itens[j].valor;
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
    cout << "\nLeve agora" << endl;
    leve(itens, N, W);
    return 0;
}