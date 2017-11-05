#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/09 16:47:54 by tshevchu          #+#    #+#              #
#    Updated: 2017/11/01 14:02:07 by tshevchu         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ls

FLAGS = -Wall -Wextra -Werror

LIBFT = libft/

OBJECTS = init_structs.o list_of_content.o list_of_dirs.o long_format_ls.o long_format_ls2.o ls_argv.o ls_flags.o main.o sorting_ls.o sorting_identical.o

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIBFT)
	@gcc $(OBJECTS) $(FLAGS) $(LIBFT)libft.a $(LIBMLX) -o $(NAME)
	@echo "\x1B[01;34m>>>>>FT_LS IS READY!!<<<<<"

%.o: ./%.c
	@gcc $(FLAGS) -o $@ -c $<

clean:
	@make clean -C libft
	@rm -f $(OBJECTS)
	@echo "\x1B[01;90m>>>CLEAN FT_LS & LIBFT OBJ<<<"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "\x1B[01;93m>>>EVERYTHING IS CLEAR:)<<<"

re: fclean all