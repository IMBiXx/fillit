# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/15 16:47:18 by tpotier           #+#    #+#              #
#    Updated: 2019/04/18 18:29:22 by valecart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FILES = fillit \
		parsing \
		brain \
		io \
		pieces_utils \
		pieces_utils_2 \
		board_utils
IFILES = fillit.h
NAME = fillit
SDIR = srcs/
IDIR = includes/
LIBFTDIR = libft/
LIBFT = $(LIBFTDIR)libft.a
LIBFTINC = $(LIBFTDIR)incs/
LIBFTFLAGS = -L$(LIBFTDIR) -lft
CFLAGS = -Wall -Wextra -Werror -I$(IDIR) -I$(LIBFTINC) -MMD -MP

SRCS = $(addprefix $(SDIR), $(addsuffix .c, $(FILES)))
INCS = $(addprefix $(IDIR), $(IFILES))
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR) libft.a

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LIBFTFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	make -C $(LIBFTDIR) $@
	rm -f $(OBJS) $(DEPS)

fclean: clean
	make -C $(LIBFTDIR) $@
	rm -f $(NAME)

re: fclean all

.PHONY: all $(name) clean fclean re
-include $(DEPS)
