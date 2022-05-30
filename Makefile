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

OBJ_DIR = obj/
SRC_DIR = src/
INC_DIR = include/

PUSH_SWAP_SRC_DIR = push_swap/
SHARED_SRC_DIR = shared/

SRCS = action.c		median.c	push_swap.c		ps_quicksort.c		selection_sort.c		utils.c\
	   optimizer/optimizer.c	optimizer/contradictions.c	optimizer/rotation.c
SRCS_P = $(addprefix $(PUSH_SWAP_SRC_DIR), $(SRCS))
OBJS = $(SRCS_P:.c=.o)
OBJS_P = $(addprefix $(OBJ_DIR), $(OBJS))

SHARED_SRCS = parse.c\
			  stack.c\
			  stack_actions.c
SHARED_SRCS_P = $(addprefix $(SHARED_SRC_DIR), $(SHARED_SRCS))
SHARED_OBJS = $(SHARED_SRCS_P:.c=.o)
SHARED_OBJS_P = $(addprefix $(OBJ_DIR), $(SHARED_OBJS))

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

LIBFT = ./libft/
LIBFT_LIB = $(addprefix $(LIBFT), libft.a)
LIBFT_INC = -I ./libft/include

all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(LIBFT)include/libft.h $(INC_DIR)push_swap.h $(INC_DIR)push_swap_shared.h
	@mkdir -p $(@D)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -I $(INC_DIR) $(LIBFT_INC) -c -o $@ $<

$(NAME): $(LIBFT_LIB) $(OBJS_P) $(SHARED_OBJS_P)
	@echo "Compiling main executable"
	@$(CC) $(CFLAGS) $(OBJS_P) $(SHARED_OBJS_P) $(LIBFT_LIB) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Done cleaning $(CURDIR)/$(OBJ_DIR)"
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@echo "Done cleaning archive $(CURDIR)/$(NAME)"
	@$(MAKE) -C $(LIBFT) fclean

re: fclean
	@$(MAKE)

.PHONY: all clean fclean re