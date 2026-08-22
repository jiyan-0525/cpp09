NAME = RPN

SRCS = main.cpp RPN.cpp
OBJS = $(SRCS:%.cpp=object/%.o)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17

all: object $(NAME)

object:
	mkdir -p object

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

object/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf object

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re