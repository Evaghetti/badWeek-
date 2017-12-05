#include <iostream>
#include <algorithm>
#include <string>
#include <set>

int main() {
	std::set<std::string> joias;
	std::string buffer;
	int cont = 0;
	
	while (std::getline(std::cin, buffer)) {
		if (joias.find(buffer) == joias.end()) {
			joias.insert(buffer);
			cont++;
		}
	}
	
	std::cout << cont << std::endl;
	return 0;
}