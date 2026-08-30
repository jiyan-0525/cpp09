# include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

PRN::RPN(const std::string& expression) {
    evaluate(expression);
}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        _stack = other._stack;
    }
    return *this;
}

RPN::~RPN() {}

bool RPN::isOperator(const std::string& token) const {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

void RPN::performOperation(const std::string& operatorToken) {
    if (_stack.size() < 2) {
        throw std::runtime_error("Insufficient operands for operation: " + operatorToken);
    }

    int b = _stack.top(); _stack.pop();
    int a = _stack.top(); _stack.pop();
    int result;

    if (operatorToken == "+") {
        result = a + b;
    } else if (operatorToken == "-") {
        result = a - b;
    } else if (operatorToken == "*") {
        result = a * b;
    } else if (operatorToken == "/") {
        if (b == 0) {
            throw std::runtime_error("Division by zero");
        }
        result = a / b;
    } else {
        throw std::runtime_error("Unknown operator: " + operatorToken);
    }
    _stack.push(result);
}

void RPN::evaluate(const std::string& expression) {
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (isOperator(token)) {
            performOperation(token);
        } else {
            try {
                int number = std::stoi(token);
                _stack.push(number);
            } catch (const std::invalid_argument&) {
                throw std::runtime_error("Error");
            }
        }
    }

    if (_stack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    std::cout << _stack.top() << std::endl;
}
