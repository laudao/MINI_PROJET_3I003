TEST= test
PROPAGATION= propagation

CC= gcc
CFLAGS= -Werror -Wextra -Wall -fsanitize=address

SRC_SHARED= entree_sortie.c tomographie.c
SRC_TEST= testtomographie.c
SRC_PROPAG= test_propag.c

OBJ_SHARED= $(SRC_SHARED:.c=.o)
OBJ_TEST= $(SRC_TEST:.c=.o)
OBJ_PROPAG= $(SRC_PROPAG:.c=.o)

INC= -I includes/

VPATH= srcs

all: $(TEST) $(PROPAGATION)

### Executables

$(TEST): $(OBJ_TEST) $(OBJ_SHARED)
	@$(CC) $(CFLAGS) -o $@ $^ $(INC) -lm
	@echo "Linking [$^]"

$(PROPAGATION): $(OBJ_PROPAG) $(OBJ_SHARED)
	@$(CC) $(CFLAGS) -o $@ $^ $(INC) -lm
	@echo "Linking [$^]"

### Obj files

$(OBJ_TEST): $(SRC_TEST)
	@$(CC) $(CFLAGS) -c $^ $(INC)
	@echo "Compiling [$^]"

$(OBJ_SHARED): $(SRC_SHARED)
	@$(CC) $(CFLAGS) -c $^ $(INC)
	@echo "Compiling [$^]"

$(OBJ_PROPAG): $(SRC_PROPAG)
	@$(CC) $(CFLAGS) -c $^ $(INC)
	@echo "Compiling [$^]"

clean:
	rm $(OBJ_TEST) $(OBJ_SHARED) $(OBJ_PROPAG)

fclean: clean
	rm $(TEST) $(PROPAGATION)

re: fclean all

.PHONY: clean fclean re
