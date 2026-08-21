#include "BitcoinExchange.hpp"

int main(int ac, char *av[]) {
    if (ac != 2) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }
    try {
        BitcoinExchange exchange("data.csv");
        exchange.processInput(av[1]);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}