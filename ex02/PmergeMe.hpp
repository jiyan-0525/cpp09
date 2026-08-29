#ifndef PMERGEME_HPP
# define PMERGEME_HPP
#include <deque>
#include <vector>
#include <cctype>
#include <utility>
#include <iostream>
#include <algorithm>

class PmergeMe {
public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void fillContainers(int argc, char **argv);
    void printContainers() const;

    std::vector<int>& vector();
    std::deque<int>& deque();

private:
    std::vector<int> _vector;
    std::deque<int> _deque;
};

template <typename T>
void mergeInsertionSort(T& container) {
    if (container.size() <= 1)
        return;

    typedef typename T::value_type value_type;

    std::vector<std::pair<value_type, value_type> > pairs;
    bool hasOdd = false;
    value_type odd;
    typename T::iterator it = container.begin();
    while (it != container.end()) {
        value_type a = *it;
        ++it;
        if (it == container.end()) {
            hasOdd = true;
            odd = a;
            break;
        }
        value_type b = *it;
        ++it;
        if (a > b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }

    T main;
    std::vector<value_type> pend;
    for (typename std::vector<std::pair<value_type, value_type> >::iterator p = pairs.begin();
         p != pairs.end(); ++p)
    {
        main.push_back(p->second);
        pend.push_back(p->first);
    }
    if (main.size() > 1)
        mergeInsertionSort(main);

    T sorted(main);

    std::vector<std::size_t> order;

    // Jacobsthal insertion
    for (std::size_t idx = 2; idx < pend.size() || idx - 1 < pend.size(); idx += 2) {
        if (idx < pend.size())
            order.push_back(idx);
        if (idx - 1 < pend.size())
            order.push_back(idx - 1);
    }
    for (std::size_t k = 0; k < order.size(); ++k) {
        std::size_t i = order[k];
        typename T::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), pend[i]);
        sorted.insert(pos, pend[i]);
    }
    {
        typename T::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), pend[0]);
        sorted.insert(pos, pend[0]);
    }
    if (hasOdd) {
        typename T::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), odd);
        sorted.insert(pos, odd);
    }
    container.assign(sorted.begin(), sorted.end());
}

#endif
