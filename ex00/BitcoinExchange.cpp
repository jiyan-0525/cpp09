#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& filename) {
    readData(filename);
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
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    if (!std::isdigit(date[0]) || !std::isdigit(date[1]) || 
        !std::isdigit(date[2]) || !std::isdigit(date[3]) ||
        !std::isdigit(date[5]) || !std::isdigit(date[6]) ||
        !std::isdigit(date[8]) || !std::isdigit(date[9])) {
        return false;
    }
    return true;
}

bool isValidValue(const std::string& valstr, float& outval) {
    if(valstr.empty()) {
        std::cerr << "Error: empty value." << std::endl;
        return false;
    }
    const char *start = valstr.data();
    const char *end = valstr.data() + valstr.size();

    auto [ptr, ec] = std::from_chars(start, end, outval);
    if (ec != std::errc() || ptr != end) {
        std::cerr << "Error: invalid value => " << valstr << std::endl;
        return false;
    }
    if (outval < 0) {
        std::cerr << "Error: negative value => " << valstr << std::endl;
        return false;
    }
    if (outval > 1000) {
        std::cerr << "Error: value too large => " << valstr << std::endl;
        return false;
    }
    return true;
}

void BitcoinExchange::readData(const std::string& filename) const {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file.");
    }

    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date, valueStr;
        if (std::getline(iss, date, ',') && std::getline(iss, valueStr)) {
            float value;
            if (!isValidDate(date) || !isValidValue(valueStr, value)) {
                std::cerr << "Error: Invalid data in file." << std::endl;
                continue;
            }
            _data[date] = value;
        } else {
            std::cerr << "Error: Invalid line format => " << line << std::endl;
        }
    }
    file.close();
}
