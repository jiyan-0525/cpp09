#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <cstdlib>

class BitcoinExchange {
public:
    BitcoinExchange();
    BitcoinExchange(const std::string& filename);
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();
    
    void read_data(const std::string& filename);
    void process_file(const std::string& filename) const;

private:
    std::map<std::string, double> _data;
    
    bool is_valid_date(const std::string& date) const;
    bool is_valid_value(const std::string& value_str, double& value) const;
    double get_rate(const std::string& date) const;
    std::string trim(const std::string& str) const;
};

#endif