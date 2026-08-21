#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
#include <map>
#include <cctype>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <charconv>
#include <iostream>
#include <stdexcept>

class BitcoinExchange {
public:
    BitcoinExchange();
    BitcoinExchange(const std::string& filename);
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void readData(const std::string& filename) const;

private:
    std::map<std::string, double> _data;

    bool isValidDate(const std::string& date) const;
    bool isValidValue(const std::string& valstr, float& outval) const;
    
};

#endif