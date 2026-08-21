#include "BitcoinExchange.hpp"

int main(int ac, char *av[]) {
    if (ac != 2) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }

    std::ifstream file(av[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }
    return 0;
}