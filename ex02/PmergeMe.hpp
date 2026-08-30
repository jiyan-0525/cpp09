#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>
#include <cstddef>

struct Pair {
    int small;
    int large;
};

class PmergeMe {
public:
    PmergeMe();
    PmergeMe(const std::vector<int>& vec, const std::deque<int>& deq);
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void sortVector();
    void sortDeque();

    const std::vector<int>& getVector() const;
    const std::deque<int>& getDeque() const;

private:
    std::vector<int> _vector;
    std::deque<int> _deque;

    static std::vector<int> mergeinsertVector(const std::vector<int>& vec);
    static std::deque<int> mergeinsertDeque(const std::deque<int>& deq);
    static std::vector<std::size_t> jacobsthalinsert(std::size_t n);
    static void sortPairsByLargeVector(std::vector<Pair>& pairs);
    static void sortPairsByLargeDeque(std::deque<Pair>& pairs);
};

#endif
