ENUMERATION= enumeration
PROPAGATION= propagation
TEST= test

CC= gcc
CFLAGS= -Werror -Wextra -Wall -fsanitize=address

SRC_SHARED= entree_sortie.c tomographie.c
SRC_ENUM= test_enumeration.c
SRC_PROPAG= test_propag.c
SRC_TEST= testtomographie.c

OBJ_SHARED= $(SRC_SHARED:.c=.o)
OBJ_ENUM= $(SRC_ENUM:.c=.o)
OBJ_PROPAG= $(SRC_PROPAG:.c=.o)
OBJ_TEST= $(SRC_TEST:.c=.o)

INC= -I includes/

VPATH= srcs

all: $(TEST) $(ENUMERATION) $(PROPAGATION)

### Executables

$(ENUMERATION): $(OBJ_ENUM) $(OBJ_SHARED)
	@$(CC) $(CFLAGS) -o $@ $^ $(INC) -lm
	@echo "Linking [$^]"

$(PROPAGATION): $(OBJ_PROPAG) $(OBJ_SHARED)
	@$(CC) $(CFLAGS) -o $@ $^ $(INC) -lm
	@echo "Linking [$^]"

$(TEST): $(OBJ_TEST) $(OBJ_SHARED)
	@$(CC) $(CFLAGS) -o $@ $^ $(INC) -lm
	@echo "Linking [$^]"

### Obj files

$(OBJ_ENUM): $(SRC_ENUM)
	@$(CC) $(CFLAGS) -c $^ $(INC)
	@echo "Compiling [$^]"

$(OBJ_SHARED): $(SRC_SHARED)
	@$(CC) $(CFLAGS) -c $^ $(INC)
	@echo "Compiling [$^]"

$(OBJ_PROPAG): $(SRC_PROPAG)
	@$(CC) $(CFLAGS) -c $^ $(INC)
	@echo "Compiling [$^]"

$(OBJ_TEST): $(SRC_TEST)
	@$(CC) $(CFLAGS) -c $^ $(INC)
	@echo "Compiling [$^]"

clean:
	rm $(OBJ_ENUM) $(OBJ_SHARED) $(OBJ_PROPAG)

fclean: clean
	rm $(ENUMERATION) $(PROPAGATION)

re: fclean all

.PHONY: clean fclean re
