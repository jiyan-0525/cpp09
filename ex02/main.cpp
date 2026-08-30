#include "PmergeMe.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    std::vector<int> input;
    for (int i = 1; i < argc; ++i)
    {
        std::istringstream iss(argv[i]);
        int value;
        if (!(iss >> value) || !iss.eof() || value < 0)
        {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        input.push_back(value);
    }

    std::deque<int> deq(input.begin(), input.end());

    std::cout << "Before: ";
    for (std::size_t i = 0; i < input.size(); ++i)
        std::cout << input[i] << " ";
    std::cout << std::endl;

    PmergeMe pm(input, deq);

    auto start = std::chrono::high_resolution_clock::now();
    pm.sortVector();
    auto end = std::chrono::high_resolution_clock::now();
    double vecTime = std::chrono::duration<double, std::micro>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    pm.sortDeque();
    end = std::chrono::high_resolution_clock::now();
    double deqTime = std::chrono::duration<double, std::micro>(end - start).count();

    const std::vector<int>& sortedVec = pm.getVector();

    std::cout << "After: ";
    for (std::size_t i = 0; i < sortedVec.size(); ++i)
        std::cout << sortedVec[i] << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << input.size()
              << " elements with std::vector : " << std::fixed << std::setprecision(5)
              << vecTime << " us" << std::endl;
    std::cout << "Time to process a range of " << input.size()
              << " elements with std::deque : " << std::fixed << std::setprecision(5)
              << deqTime << " us" << std::endl;

    return 0;
}
