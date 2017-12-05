#include <iostream>
#include <sstream>
#include <string>

int main() {
	long long unsigned x, y;
	
	std::cin >> x >> y;
	while (x != 0 || y != 0) {
		std::stringstream ss(std::to_string(x + y));
		std::string most, buffer;
		
		while (std::getline(ss, buffer, '0')) 
			most.append(buffer);
		std::cout << most << std::endl;
		std::cin >> x >> y;
	}
	return 0;
}