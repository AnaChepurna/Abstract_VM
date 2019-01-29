NAME = avm
FLAGS = -Wall -Wextra -Werror
CC = clang++ -std=c++11
FSRC =       Lexer.cpp \
            OperandFactory.cpp \
            Parser.cpp \
            Token.cpp \
            VirtualMachine.cpp \
            main.cpp \
            Error.cpp
FINCL =     IOperand.h \
            Lexer.h \
            Operand.h \
            OperandFactory.h \
            Parser.h \
            Token.h \
            VirtualMachine.h \
            Error.h
SRC_DIR = src/
INCL_DIR = incl/
OBJ_DIR = obj/
SRC = $(addprefix $(SRC_DIR), $(FSRC))
INCL = $(addprefix $(INCL_DIR), $(FINCL))
OBJ = $(addprefix $(OBJ_DIR), $(FSRC:.cpp=.o))


all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(INCL)
	$(CC) $(FLAGS) -I $(INCL_DIR) -c $< -o $@

clean: 
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
