#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const std::vector<int>& vec, const std::deque<int>& deq)
    : _vector(vec), _deque(deq) {}

PmergeMe::PmergeMe(const PmergeMe& other)
    : _vector(other._vector), _deque(other._deque) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _vector = other._vector;
        _deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

const std::vector<int>& PmergeMe::getVector() const {
    return _vector;
}

const std::deque<int>& PmergeMe::getDeque() const {
    return _deque;
}

static bool pairLargeLess(const Pair& a, const Pair& b) {
    return a.large < b.large;
}

void PmergeMe::sortPairsByLargeVector(std::vector<Pair>& pairs) {
    if (pairs.size() <= 1)
        return;

    size_t mid = pairs.size() / 2;
    std::vector<Pair> left(pairs.begin(), pairs.begin() + mid);
    std::vector<Pair> right(pairs.begin() + mid, pairs.end());

    sortPairsByLargeVector(left);
    sortPairsByLargeVector(right);

    std::vector<Pair> merged;
    merged.reserve(pairs.size());
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (pairLargeLess(right[j], left[i]))
            merged.push_back(right[j++]);
        else
            merged.push_back(left[i++]);
    }
    while (i < left.size())
        merged.push_back(left[i++]);
    while (j < right.size())
        merged.push_back(right[j++]);

    pairs.swap(merged);
}

void PmergeMe::sortPairsByLargeDeque(std::deque<Pair>& pairs) {
    if (pairs.size() <= 1)
        return;

    size_t mid = pairs.size() / 2;
    std::deque<Pair> left(pairs.begin(), pairs.begin() + mid);
    std::deque<Pair> right(pairs.begin() + mid, pairs.end());

    sortPairsByLargeDeque(left);
    sortPairsByLargeDeque(right);

    std::deque<Pair> merged;
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (pairLargeLess(right[j], left[i]))
            merged.push_back(right[j++]);
        else
            merged.push_back(left[i++]);
    }
    while (i < left.size())
        merged.push_back(left[i++]);
    while (j < right.size())
        merged.push_back(right[j++]);

    pairs.swap(merged);
}

std::vector<size_t> PmergeMe::jacobsthalinsert(size_t n) {
    if (n <= 1)
        return std::vector<size_t>();

    std::vector<size_t> jacob;
    size_t a = 0, b = 1;
    jacob.push_back(a);
    jacob.push_back(b);
    while (true) {
        size_t next = b + 2 * a;
        if (next > n) break;
        jacob.push_back(next);
        a = b;
        b = next;
    }

    std::vector<size_t> order;
    std::vector<bool> used(n, false);
    used[0] = true;

    for (size_t k = 1; k < jacob.size(); ++k) {
        size_t hi = jacob[k] < n - 1 ? jacob[k] : n - 1;
        size_t lo = jacob[k - 1];
        for (size_t i = hi; i > lo; --i) {
            if (i < n && !used[i]) {
                used[i] = true;
                order.push_back(i);
            }
        }
    }
    for (size_t i = 1; i < n; ++i)
        if (!used[i]) order.push_back(i);
    return order;
}

std::vector<int> PmergeMe::mergeinsertVector(const std::vector<int>& vec) {
    if (vec.size() <= 1)
        return vec;

    std::vector<Pair> pairs;
    for (size_t i = 0; i + 1 < vec.size(); i += 2) {
        if (vec[i] < vec[i + 1])
            pairs.push_back(Pair{vec[i], vec[i + 1]});
        else
            pairs.push_back(Pair{vec[i + 1], vec[i]});
    }
    bool hasleftover = (vec.size() % 2 != 0);
    int leftover = hasleftover ? vec.back() : 0;

    sortPairsByLargeVector(pairs);

    std::vector<int> chain;
    chain.reserve(vec.size());
    for (size_t i = 0; i < pairs.size(); ++i)
        chain.push_back(pairs[i].large);

    if (!pairs.empty())
        chain.insert(chain.begin(), pairs[0].small);

    std::vector<size_t> order = jacobsthalinsert(pairs.size());
    for (size_t idx = 0; idx < order.size(); ++idx) {
        int val = pairs[order[idx]].small;
        chain.insert(std::lower_bound(chain.begin(), chain.end(), val), val);
    }

    if (hasleftover)
        chain.insert(std::lower_bound(chain.begin(), chain.end(), leftover), leftover);

    return chain;
}

std::deque<int> PmergeMe::mergeinsertDeque(const std::deque<int>& deq) {
    if (deq.size() <= 1)
        return deq;

    std::deque<Pair> pairs;
    for (size_t i = 0; i + 1 < deq.size(); i += 2) {
        if (deq[i] < deq[i + 1])
            pairs.push_back(Pair{deq[i], deq[i + 1]});
        else
            pairs.push_back(Pair{deq[i + 1], deq[i]});
    }
    bool hasleftover = (deq.size() % 2 != 0);
    int leftover = hasleftover ? deq.back() : 0;

    sortPairsByLargeDeque(pairs);

    std::deque<int> chain;
    for (size_t i = 0; i < pairs.size(); ++i)
        chain.push_back(pairs[i].large);

    if (!pairs.empty())
        chain.push_front(pairs[0].small);

    std::vector<size_t> order = jacobsthalinsert(pairs.size());
    for (size_t idx = 0; idx < order.size(); ++idx) {
        int val = pairs[order[idx]].small;
        chain.insert(std::lower_bound(chain.begin(), chain.end(), val), val);
    }

    if (hasleftover)
        chain.insert(std::lower_bound(chain.begin(), chain.end(), leftover), leftover);

    return chain;
}

void PmergeMe::sortVector() {
    _vector = mergeinsertVector(_vector);
}

void PmergeMe::sortDeque() {
    _deque = mergeinsertDeque(_deque);
}
