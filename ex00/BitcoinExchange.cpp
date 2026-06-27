#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
    *this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        data = other.data;
    }
    return *this;
}

void BitcoinExchange::run(const std::string& filename) {
    loadData();
    processInput(filename);
}

void BitcoinExchange::loadData() {
    std::ifstream file("data.csv");
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        processLine(line);
    }
}

void BitcoinExchange::processLine(const std::string& line) {
    std::string date;
    double value;
    std::stringstream ss(line);
    std::getline(ss, date, ',');
    ss >> value;
    data[date] = value;
}

void BitcoinExchange::processInput(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        processData(line);
    }
}

void BitcoinExchange::processData(const std::string& line) {
    std::string date;
    double value;
    std::stringstream ss(line);
    std::getline(ss, date, ',');
    ss >> value;
    data[date] = value;
}
