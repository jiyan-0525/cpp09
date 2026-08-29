#include "PmergeMe.hpp"
#include <cstdlib>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vector(other._vector), _deque(other._deque) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _vector = other._vector;
        _deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::fillContainers(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        const char *s = argv[i];
        while (*s) {
            if (!std::isdigit(*s)) {
                std::cerr << "Error" << std::endl;
                exit(1);
            }
            ++s;
        }
        long v = std::atol(argv[i]);
        if (v < 0) {
            std::cerr << "Error" << std::endl;
            exit(1);
        }
        int vi = static_cast<int>(v);
        _vector.push_back(vi);
        _deque.push_back(vi);
    }
}

void PmergeMe::printContainers() const {
    for (std::vector<int>::const_iterator it = _vector.begin(); it != _vector.end(); ++it)
        std::cout << " " << *it;
    std::cout << std::endl;
}

std::vector<int>& PmergeMe::vector() {
    return _vector;
}

std::deque<int>& PmergeMe::deque() {
    return _deque;
}