ENUMERATION= enumeration
TESTVECTEUR= testvecteur
PROPAGATION= propagation

CC= gcc
CFLAGS= -Werror -Wextra -Wall -fsanitize=address

SRC_SHARED= entree_sortie.c tomographie.c
SRC_ENUM= test_enumeration.c
SRC_VECTEUR= test_vecteur.c
SRC_PROPAG= test_propag.c

OBJ_SHARED= $(SRC_SHARED:.c=.o)
OBJ_ENUM= $(SRC_ENUM:.c=.o)
OBJ_VECTEUR= $(SRC_VECTEUR:.c=.o)
OBJ_PROPAG= $(SRC_PROPAG:.c=.o)

INC= -I includes/

VPATH= srcs

all: $(ENUMERATION) $(PROPAGATION) $(TESTVECTEUR)

### Executables

$(ENUMERATION): $(OBJ_ENUM) $(OBJ_SHARED)
	@$(CC) $(CFLAGS) -o $@ $^ $(INC) -lm
	@echo "Linking [$^]"

$(TESTVECTEUR): $(OBJ_VECTEUR) $(OBJ_SHARED)
	@$(CC) $(CFLAGS) -o $@ $^ $(INC) -lm
	@echo "Linking [$^]"

$(PROPAGATION): $(OBJ_PROPAG) $(OBJ_SHARED)
	@$(CC) $(CFLAGS) -o $@ $^ $(INC) -lm
	@echo "Linking [$^]"

### Obj files

$(OBJ_ENUM): $(SRC_ENUM)
	@$(CC) $(CFLAGS) -c $^ $(INC)
	@echo "Compiling [$^]"

$(OBJ_VECTEUR): $(SRC_VECTEUR)
	@$(CC) $(CFLAGS) -c $^ $(INC)
	@echo "Compiling [$^]"

$(OBJ_SHARED): $(SRC_SHARED)
	@$(CC) $(CFLAGS) -c $^ $(INC)
	@echo "Compiling [$^]"

$(OBJ_PROPAG): $(SRC_PROPAG)
	@$(CC) $(CFLAGS) -c $^ $(INC)
	@echo "Compiling [$^]"

clean:
	rm $(OBJ_ENUM) $(OBJ_SHARED) $(OBJ_PROPAG) $(OBJ_VECTEUR)

fclean: clean
	rm $(ENUMERATION) $(PROPAGATION) $(TESTVECTEUR)

re: fclean all

.PHONY: clean fclean re
