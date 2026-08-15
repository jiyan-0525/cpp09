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

std::string BitcoinExchange::trim(const std::string& str) const {
    std::string::size_type start = 0;
    std::string::size_type end = str.length();
    
    while (start < end && std::isspace(str[start])) {
        start++;
    }
    while (end > start && std::isspace(str[end - 1])) {
        end--;
    }
    return str.substr(start, end - start);
}

bool BitcoinExchange::is_valid_date(const std::string& date) const {
    if (date.length() != 10) {
        return false;
    }
    if (date[4] != '-' || date[7] != '-') {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            continue;
        }
        if (!std::isdigit(date[i])) {
            return false;
        }
    }
    
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));
    
    if (month < 1 || month > 12) {
        return false;
    }
    
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Leap year check
    if (month == 2) {
        bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (is_leap) {
            days_in_month[1] = 29;
        }
    }
    
    if (day < 1 || day > days_in_month[month - 1]) {
        return false;
    }
    
    return true;
}

bool BitcoinExchange::is_valid_value(const std::string& value_str, double& value) const {
    if (value_str.empty()) {
        return false;
    }
    
    std::stringstream ss(value_str);
    ss >> value;
    
    if (ss.fail() || !ss.eof()) {
        return false;
    }
    
    if (value < 0) {
        return false;
    }
    
    return true;
}

double BitcoinExchange::get_rate(const std::string& date) const {
    std::map<std::string, double>::const_iterator it = _data.lower_bound(date);
    
    if (it == _data.begin()) {
        // Date is before the first entry in the database
        return it->second;
    }
    
    if (it == _data.end() || it->first != date) {
        // Use the closest lower date
        --it;
    }
    
    return it->second;
}

void BitcoinExchange::read_data(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open file.");
    }
    
    std::string line;
    bool first_line = true;
    
    while (std::getline(file, line)) {
        if (first_line) {
            first_line = false;
            continue; // Skip header
        }
        
        if (line.empty()) {
            continue;
        }
        
        std::string::size_type comma_pos = line.find(',');
        if (comma_pos == std::string::npos) {
            continue;
        }
        
        std::string date = line.substr(0, comma_pos);
        std::string rate_str = line.substr(comma_pos + 1);
        
        if (!is_valid_date(date)) {
            continue;
        }
        
        double rate;
        std::stringstream ss(rate_str);
        ss >> rate;
        if (ss.fail()) {
            continue;
        }
        
        _data[date] = rate;
    }
}

void BitcoinExchange::process_file(const std::string& filename) const {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    
    std::string line;
    bool first_line = true;
    
    while (std::getline(file, line)) {
        if (first_line) {
            first_line = false;
            continue; // Skip header
        }
        
        if (line.empty()) {
            continue;
        }
        
        std::string::size_type pipe_pos = line.find('|');
        if (pipe_pos == std::string::npos) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        
        std::string date = trim(line.substr(0, pipe_pos));
        std::string value_str = trim(line.substr(pipe_pos + 1));
        
        if (!is_valid_date(date)) {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }
        
        double value;
        if (!is_valid_value(value_str, value)) {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        
        if (value > 1000) {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }
        
        double rate = get_rate(date);
        double result = value * rate;
        
        std::cout << date << " => " << value_str << " = " << result << std::endl;
    }
}