#include <random>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

struct  item {
    int id;
    int peso;
    int valor;
};

bool is_in_vector(vector<size_t> resposta, size_t number){
    for (size_t i = 0; i < resposta.size(); i++){
        if (resposta[i] == number){
            return true;
        }
    }
    return false;
}


int mochila(vector<item> itens, size_t N, int W, vector<size_t> &resposta){
    if (N == 0 || W == 0) {
        return 0;
    }
    if (itens[N - 1].peso > W) {
        return mochila(itens, N - 1, W, resposta);
    }
    int incluso = itens[N - 1].valor + mochila(itens, N-1, W - itens[N - 1].peso, resposta);
    int nao_incluso = mochila(itens, N-1, W,resposta);
    if (incluso > nao_incluso){
             resposta.push_back(itens[N-1].id);
        return incluso;
    }
    return nao_incluso;
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
    vector<size_t> resposta;
    cout << "Exaustivo agora" << endl;
    int answer = mochila(itens, N, W, resposta);

    cout << answer << endl;
    // cout << peso << " " << valor << " " << "0"  << "\n";

    // for (size_t i = 0; i < resposta.size(); i++){
	// 	cout << resposta[i] << " ";
	// }
    return 0;
}