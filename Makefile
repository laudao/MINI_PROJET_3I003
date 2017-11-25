TEST= test

CC= gcc
CFLAGS= -Werror -Wextra -Wall -fsanitize=address

SRC= entree_sortie.c testtomographie.c tomographie.c

OBJ= $(SRC:.c=.o)

INC= -I includes/

VPATH= srcs

all: $(TEST)

### Executables

$(TEST): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ $(INC) -lm
	@echo "Linking [$^]"

### Obj files

$(OBJ): $(SRC)
	@$(CC) $(CFLAGS) -c $^ $(INC)
	@echo "Compiling [$^]"

clean:
	rm $(OBJ)

fclean: clean
	rm $(TEST)

re: fclean all

.PHONY: clean fclean re
