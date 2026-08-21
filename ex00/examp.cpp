#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <cctype>
#include <stdexcept>

BitcoinExchange::BitcoinExchange() {
	loadDatabase("data.csv");
}

BitcoinExchange::BitcoinExchange(const std::string &dbFile) {
	loadDatabase(dbFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _db(other._db) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other)
		_db = other._db;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::trim(std::string &s) const {
	size_t start = s.find_first_not_of(" \t\r\n");
	size_t end = s.find_last_not_of(" \t\r\n");
	if (start == std::string::npos) {
		s.clear();
		return;
	}
	s = s.substr(start, end - start + 1);
}

bool BitcoinExchange::isValidDate(const std::string &date) const {
	if (date.size() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	for (size_t i = 0; i < date.size(); ++i) {
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return false;
	}

	int year = std::stoi(date.substr(0, 4));
	int month = std::stoi(date.substr(5, 2));
	int day = std::stoi(date.substr(8, 2));

	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;

	static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int maxDay = daysInMonth[month - 1];
	bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	if (month == 2 && isLeap)
		maxDay = 29;
	if (day > maxDay)
		return false;

	return true;
}

bool BitcoinExchange::parseValue(const std::string &str, double &value) const {
	if (str.empty())
		return false;
	try {
		size_t pos;
		value = std::stod(str, &pos);
		if (pos != str.size())
			return false;
	} catch (const std::exception &) {
		return false;
	}
	return true;
}

void BitcoinExchange::loadDatabase(const std::string &dbFile) {
	std::ifstream file(dbFile);
	if (!file.is_open())
		throw std::runtime_error("could not open database file.");

	std::string line;
	std::getline(file, line); // skip header "date,exchange_rate"

	while (std::getline(file, line)) {
		if (line.empty())
			continue;
		size_t commaPos = line.find(',');
		if (commaPos == std::string::npos)
			continue;

		std::string date = line.substr(0, commaPos);
		std::string rateStr = line.substr(commaPos + 1);
		trim(date);
		trim(rateStr);

		double rate;
		if (!isValidDate(date) || !parseValue(rateStr, rate))
			continue;
		_db[date] = rate;
	}
}

void BitcoinExchange::processFile(const std::string &inputFile) const {
	std::ifstream file(inputFile);
	if (!file.is_open()) {
		std::cout << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line); // skip header "date | value"

	while (std::getline(file, line)) {
		if (line.empty())
			continue;
		processLine(line);
	}
}

void BitcoinExchange::processLine(const std::string &line) const {
	size_t sepPos = line.find('|');
	if (sepPos == std::string::npos) {
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}

	std::string date = line.substr(0, sepPos);
	std::string valueStr = line.substr(sepPos + 1);
	trim(date);
	trim(valueStr);

	if (!isValidDate(date)) {
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}

	double value;
	if (!parseValue(valueStr, value)) {
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}

	if (value < 0) {
		std::cout << "Error: not a positive number." << std::endl;
		return;
	}
	if (value > 1000) {
		std::cout << "Error: too large a number." << std::endl;
		return;
	}

	if (_db.empty()) {
		std::cout << "Error: database is empty." << std::endl;
		return;
	}

	auto it = _db.lower_bound(date);
	if (it == _db.end() || it->first != date) {
		if (it == _db.begin()) {
			std::cout << "Error: no earlier date in database => " << line << std::endl;
			return;
		}
		--it;
	}

	std::cout << date << " => " << value << " = " << value * it->second << std::endl;
}