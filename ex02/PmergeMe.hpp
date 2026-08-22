#ifndef PMERGEME_HPP
# define PMERGEME_HPP
#include <iostream>
#include <vector>
#include <deque>

calss PmergeMe {
public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void mergeVectors();
    void mergeDeques();

private:
    std::vector<int> _vector;
    std::deque<int> _deque;
};

#endif