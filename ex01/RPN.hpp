#ifndef RPN_HPP
# define RPN_HPP
#include <stack>
#include <string>
#include <sstream>
#include <iostream>

class RPN {
public:
    RPN();
    RPN(const RPN& other);
    RPN(const std::string& expression);
    RPN& operator=(const RPN& other);
    ~RPN();

    void evaluate(const std::string& expression);

private:
    std::stack<int> _stack;
    bool isOperator(const std::string& token) const;
    void performOperation(const std::string& operatorToken);
};

#endif