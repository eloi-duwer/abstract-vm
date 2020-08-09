SRC_NAME = main.cpp \
	OperandFactory.cpp \
	Instruction.cpp \
	OperandParser.cpp

NAME = avm

CC = g++

CFLAGS = -Wall -Wextra -I./include -I./src -g

SRCF = ./src/

OBJF = ./obj/

OBJS = $(addprefix $(OBJF), $(SRC_NAME:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

$(OBJF)%.o: $(SRCF)%.cpp
	@mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) -c $(addprefix $(SRCF), $*.cpp) -g

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
