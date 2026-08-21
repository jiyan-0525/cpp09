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

void BicninExchange::trim(std::string& str) const {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    if (start == std::string::npos || end == std::string::npos) {
        str.clear();
        return;
    } else {
        str = str.substr(start, end - start + 1);
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        std::cerr << "Error: not enough characters in date => " << date << std::endl;
        return false;
    }
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(date[i])) {
            return false;
        }
    }
        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(5, 2));
        int day = std::stoi(date.substr(8, 2));

        if (month < 1 || month > 12 || day < 1 || day > 31) {
            return false;
        }

        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
            return false;
        }

        if (month == 2) {
            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if ((isLeapYear && day > 29) || (!isLeapYear && day > 28)) {
                return false;
            }
        
        static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (day < 1 || day > daysInMonth[month - 1]) {
            return false;
        }
    return true;
}

bool BitcoinExchange::parseValue(const std::string& valstr, float& outval) const {
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
    return true;
}

bool BitcoinExchange::isValidValue(const std::string& dbfile)const {
    std::ifstream file(dbfile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file." << std::endl;
        return false;

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

void BitcoinExchange::processInput(const std::string& inputFilename) const {
    std::ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error: Could not open input file.");
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string date, valueStr;
        if (std::getline(iss, date, '|') && std::getline(iss, valueStr)) {
            float value;
            if (!isValidDate(date) || !isValidValue(valueStr, value)) {
                std::cerr << "Error: Invalid input data => " << line << std::endl;
                continue;
            }
            auto it = _data.lower_bound(date);
            if (it == _data.end() || it->first != date) {
                if (it == _data.begin()) {
                    std::cerr << "Error: No data available for date => " << date << std::endl;
                    continue;
                }
                --it; // Use the closest previous date
            }
            double exchangeRate = it->second;
            double result = value * exchangeRate;
            std::cout << date << " => " << value << " = " << result << std::endl;
        } else {
            std::cerr << "Error: Invalid input line format => " << line << std::endl;
        }
    }
    inputFile.close();
}

void BitcoinExchange::readData(const std::string& filename) {
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
