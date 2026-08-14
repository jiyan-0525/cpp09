#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

class BitcoinExchange {
public:
    BitcoinExchange();
    BitcoinExchange(const std::string& filename);
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();
    
    void read_data(const std::string& filename);

private:
    std::map<std::string, double> _data;
};

#endif
