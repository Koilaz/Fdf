# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leo <leo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/18 17:27:49 by lmarck            #+#    #+#              #
#    Updated: 2025/01/23 15:48:04 by leo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = fdf

CC             = cc
CFLAGS         = -Wall -Wextra -Werror

SRC    = fdf.c

OBJ     = $(SRC:.c=.o)

LIBFT_DIR      = ./libft
FT_PRINTF_DIR  = ./ft_printf
GNL_DIR        = ./GNL

LIBFT          = $(LIBFT_DIR)/libft.a
FT_PRINTF      = $(FT_PRINTF_DIR)/libftprintf.a
GNL            = $(GNL_DIR)/gnl.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@make -C $(FT_PRINTF_DIR)
	@make -C $(GNL_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(GNL) $(LIBFT) $(FT_PRINTF) -o $(NAME)
	@echo "✓ Compilé avec succès."


$(NAME_SERVER): $(OBJ_SERVER)
	@make -C $(LIBFT_DIR)
	@make -C $(FT_PRINTF_DIR)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) $(FT_PRINTF) -o $(NAME_SERVER)
	@echo "✓ Server compilé avec succès."

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(FT_PRINTF_DIR)
	@make clean -C $(GNL_DIR)
	rm -f $(OBJ)
	@echo "✓ Tous les .o ont été supprimés."

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(FT_PRINTF_DIR)
	@make fclean -C $(GNL_DIR)
	rm -f $(NAME)
	@echo "✓ Les exécutables et librairies ont été supprimés."

re: fclean all

.PHONY: all clean fclean re
