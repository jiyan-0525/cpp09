#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& filename) {
    read_data(filename);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
    *this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        _data = other._data;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool isValidDate(const std::string& date) {
    ....
    return true;
}

bool isValidValue(const std::string& valstr, float& outval) {
    .....
    return true;
}

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

    std::string line;

    while (std::getline(file, line)) {
        size_t delimpos = line.find("|");
        if (delimpos == std::string::npos) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue; 
        }
        std::string dateStr = line.substr(0, delimpos);
        std::string valStr = line.substr(delimpos + 3);

        float value;
        if (!isValidDate(dateStr)) {
            std::cerr << "Error: bad date => " << dateStr << std::endl;
        } else if (!isValidValue(valStr, value)) {
            // 根据具体错误显示提示
        } else {
            // 一切正常，可以结合你的数据库逻辑进行处理
        }
    }
    return 0;
}