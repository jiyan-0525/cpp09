#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>

class BitcoinExchange {
public:
    BitcoinExchange();
    BitcoinExchange(const std::string& filename);
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();
    
    void run(const std::string& filename);

private:
    std::map<std::string, double> data;
};

#endif
