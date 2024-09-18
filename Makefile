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
INC := ltypes.h lag.h init.h simple_operations.h \
       simple_operations_1.h simple_operations_2.h \
       simple_operations_3.h simple_operations_4.h \
       vec4_linear_algebra.h lavx.h 

INCLUDE := $(addprefix $(INC_DIR)/, $(INC))

# Src
SRC_DIR := src
SRC := mat4.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRC))

# Obj
OBJ_DIR := obj
OBJS := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CFLAGS += -I$(INC_DIR)

HEADER_DEPENDING := $(addprefix -I, $(INCLUDE))

.PHONY: all clean fclean re objs

all: $(NAME)

$(NAME): | objs $(OBJS)
	@ar -rcs $@ $(OBJS)
	@printf "\n$(GREEN)Compiled LagAMat!$(DFLT)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(HEADER_DEPENDING) -c $< -o $@

objs:
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
