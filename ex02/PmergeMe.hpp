#ifndef PMERGEME_HPP
# define PMERGEME_HPP
#include <deque>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <algorithm>

class PmergeMe {
public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void sortVector();
    void sortDeque();

private:
    std::vector<int> _vector;
    std::deque<int> _deque;

    static std::vector<int> mergeinsertVector(const std::vector<int>& vec);
    static std::deque<int> mergeinsertDeque(const std::deque<int>& deq);
    static std::vector<size_t> jacobsthalSequence(size_t n);
};

#endif
