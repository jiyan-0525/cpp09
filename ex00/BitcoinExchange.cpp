#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        data[line.substr(0, 10)] = std::stod(line.substr(12));
    }
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
    *this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        data = other.data;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::read_data(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open file");
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line != "date | value") {
            std::cerr << "Error: invalid line format" << std::endl;
            continue;
        }
        std::string _date = line.substr(0, 10);
        double value = std::stod(line.substr(12));
        if (_data.find(_date) != _data.end()) {
            std::cout << _date << " => " << value << " = " << value * _data[_date] << std::endl;
        } else {
            std::cerr << "Error: date not found in data" << std::endl;
        }
    }
}

