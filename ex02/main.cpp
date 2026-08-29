#include "PmergeMe.hpp"
#include <iomanip>
#include <chrono>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    PmergeMe pmergeMe;
    pmergeMe.fillContainers(argc, argv);

    std::cout << "Before:";
    pmergeMe.printContainers();

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    mergeInsertionSort(pmergeMe.vector());
    std::chrono::duration<double, std::micro> vTime = std::chrono::steady_clock::now() - start;

    start = std::chrono::steady_clock::now();
    mergeInsertionSort(pmergeMe.deque());
    std::chrono::duration<double, std::micro> dTime = std::chrono::steady_clock::now() - start;

    std::cout << "After:";
    pmergeMe.printContainers();

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << argc - 1
              << " elements with std::vector : " << vTime.count()
              << " us" << std::endl;
    std::cout << "Time to process a range of " << argc - 1
              << " elements with std::deque : " << dTime.count()
              << " us" << std::endl;

    return 0;
}
