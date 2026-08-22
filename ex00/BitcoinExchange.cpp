#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& filename) {
    loadDatabase(filename);
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

void BitcoinExchange::trim(std::string& str) const {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    if (start == std::string::npos || end == std::string::npos) {
        str.clear();
        return;
    } else 
        str = str.substr(start, end - start + 1);
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    for (size_t i = 0; i < date.length(); ++i) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(date[i])) {
            return false;
        }
    }

    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[month - 1];
    bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (month == 2 && isLeapYear) {
        maxDay = 29;
    }
    if (day > maxDay) return false;
    return true;
}

bool BitcoinExchange::parseValue(const std::string& valstr, double& outval) const {
    if (valstr.empty()) return false;
    try {
        size_t pos;
        outval = std::stod(valstr, &pos);
        if (pos != valstr.length()) return false;
    } catch (const std::exception&) {
        return false;
    }
    return true;
}

void BitcoinExchange::processLine(const std::string& line) const {
    size_t sepPos = line.find('|');
    if (sepPos == std::string::npos) {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }
    
    std::string date = line.substr(0, sepPos);
    std::string valueStr = line.substr(sepPos + 1);
    trim(date);
    trim(valueStr);
    
    if (!isValidDate(date)) {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }

    double value;
    if (!parseValue(valueStr, value)) {
        std::cerr << "Error: bad input => " << line << std::endl;
        return;
    }

    if (value < 0) {
        std::cerr << "Error: not a positive number." << std::endl;
        return;
    }

    if (value > 1000) {
        std::cerr << "Error: too large a number." << std::endl;
        return;
    }
    auto it = _data.lower_bound(date);
    if (it == _data.end() || it->first != date) {
        if (it == _data.begin()) {
            std::cerr << "Error: no data available for date " << date << std::endl;
            return;
        }
        --it; // Use the closest previous date
    }
    
    double rate = it->second;
    double result = value * rate;
    
    std::cout << date << " => " << value << " = " << result << std::endl;
}

void BitcoinExchange::processFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // skip header "date | value"

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        processLine(line);
    }
}

void BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open database file " + filename);
    }

    std::string line;
    std::getline(file, line); // skip header "date,exchange_rate"

    while (std::getline(file, line)) {
        size_t sepPos = line.find(',');
        if (sepPos == std::string::npos) {
            continue; // skip malformed lines
        }

        std::string date = line.substr(0, sepPos);
        std::string rateStr = line.substr(sepPos + 1);
        trim(date);
        trim(rateStr);

        if (!isValidDate(date)) {
            continue; // skip invalid dates
        }

        double rate;
        if (!parseValue(rateStr, rate)) {
            continue; // skip invalid rates
        }
        _data[date] = rate;
    }
}
