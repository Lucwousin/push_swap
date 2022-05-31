# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lsinke <lsinke@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/20 14:57:29 by lsinke        #+#    #+#                  #
#    Updated: 2022/04/20 14:57:29 by lsinke        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
C_NAME = checker

OBJ_DIR = obj/
SRC_DIR = src/
INC_DIR = include/

PS_SRC_DIR = push_swap/
PS_SRCS = action.c		median.c	push_swap.c		ps_quicksort.c		selection_sort.c		util/utils.c\
	   optimizer/optimizer.c	optimizer/contradictions.c	optimizer/rotation.c\
	   util/partition.c
PS_SRCS_P = $(addprefix $(PS_SRC_DIR), $(PS_SRCS))
PS_OBJS = $(PS_SRCS_P:.c=.o)
PS_OBJS_P = $(addprefix $(OBJ_DIR), $(PS_OBJS))

C_SRC_DIR = checker/
C_SRCS = checker.c		ingest.c
C_SRCS_P = $(addprefix $(C_SRC_DIR), $(C_SRCS))
C_OBJS = $(C_SRCS_P:.c=.o)
C_OBJS_P = $(addprefix $(OBJ_DIR), $(C_OBJS))

SHARED_SRC_DIR = shared/
SHARED_SRCS = error.c		parse.c		stack.c		stack_actions.c
SHARED_SRCS_P = $(addprefix $(SHARED_SRC_DIR), $(SHARED_SRCS))
SHARED_OBJS = $(SHARED_SRCS_P:.c=.o)
SHARED_OBJS_P = $(addprefix $(OBJ_DIR), $(SHARED_OBJS))

CC = gcc
CFLAGS = -Wall -Werror -Wextra

LIBFT = ./libft/
LIBFT_LIB = $(addprefix $(LIBFT), libft.a)
LIBFT_INC = -I ./libft/include

all: $(NAME) $(C_NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(LIBFT)include/libft.h $(INC_DIR)push_swap.h $(INC_DIR)push_swap_shared.h $(INC_DIR)checker.h
	@mkdir -p $(@D)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -I $(INC_DIR) $(LIBFT_INC) -c -o $@ $<

$(NAME): $(LIBFT_LIB) $(PS_OBJS_P) $(SHARED_OBJS_P)
	@echo "Compiling main executable"
	@$(CC) $(CFLAGS) $(PS_OBJS_P) $(SHARED_OBJS_P) $(LIBFT_LIB) -o $(NAME)

$(C_NAME): $(LIBFT_LIB) $(C_OBJS_P) $(SHARED_OBJS_P)
	@echo "Compiling checker"
	@$(CC) $(CFLAGS) $(C_OBJS_P) $(SHARED_OBJS_P) $(LIBFT_LIB) -o $(C_NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Done cleaning $(CURDIR)/$(OBJ_DIR)"
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(C_NAME)
	@echo "Done cleaning archive $(CURDIR)/$(NAME)"
	@$(MAKE) -C $(LIBFT) fclean

re: fclean
	@$(MAKE)

bonus: $(C_NAME)

.PHONY: all clean fclean re bonus