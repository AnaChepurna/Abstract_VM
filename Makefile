NAME = avm
FLAGS = -Wall -Wextra -Werror
CC = clang++ -std=c++11

all: $(NAME)

$(NAME) :
	$(CC) $(FLAGS) *.cpp -o $(NAME)
