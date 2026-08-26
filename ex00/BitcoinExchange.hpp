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

    void processFile(const std::string& filename);
    void processLine(const std::string& line) const;
    
private:
    std::map<std::string, double> _data;
    void trim(std::string& s) const;
    void loadDatabase(const std::string& filename);
    bool isValidDate(const std::string& date) const;
    bool parseValue(const std::string& valstr, double& outval) const;
};
#endif