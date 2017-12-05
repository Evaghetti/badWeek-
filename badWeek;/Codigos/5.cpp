#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
using namespace std;
int main() {
	unordered_map <string, vector<pair<int, string>>> Equipe;
	string exercicio, resultado;
	int parada, tempo;
	cin >> parada;
	while (parada!=0) {
		int quantExercicios = 0, timeLimit = 0;
		for (int i = 0; i < parada; i++) {
			cin >> exercicio >> tempo >> resultado;
			Equipe[exercicio].push_back({tempo, resultado});
		}
		for (auto resultados : Equipe) {
			bool corrigido = false;
			for (auto it : resultados.second) {
				if (it.second == "correct") {
					if (timeLimit == 0)
					    timeLimit = 20;
					timeLimit += it.first;
					corrigido = true;
				}
			}
			if (corrigido)
			    quantExercicios++;
		}
		cout << quantExercicios << ' ' << timeLimit << endl;
		cin >>  parada;
		Equipe.clear();
	}
}