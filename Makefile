# Library
NAME := liblam.a

# Misc.
RED := '\033[0;31m'
GREEN := '\033[0;32m'
DFLT := '\033[0m'

# Necessities
CC := cc
CFLAGS := -Wall -Wextra -Werror -mavx -mavx2

# Include
INC_DIR := include
INC := ltypes.h lavx.h lag.h init.h simple_operations.h

INCLUDE := $(addprefix $(INC_DIR)/, $(INC))

# Src
SRC_DIR := srcs
SRC := mat4.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRC))

# Obj
OBJ_DIR := objs

OBJS := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

.PHONY: all clean fclean re objs check

all: check $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $@ $(OBJS)
	@printf "\n$(GREEN)Compiled LagAMat!$(DFLT)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

check:
	@if [ ! -d $(OBJ_DIR) ] || [ $$(find $(INCLUDE) -newer $(NAME)) ]; then \
		mkdir -p $(OBJ_DIR); \
	else \
		printf "LagAMat: Nothing to be done for \`all'\n"; \
	fi

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
