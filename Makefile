# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldick <ldick@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/18 19:28:14 by ldick             #+#    #+#              #
#    Updated: 2025/09/15 16:17:21 by ldick            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = conway

#################################################################################################
#											Colors												#
#################################################################################################

CLR_RMV		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
BOLD_BLUE	:= \033[0;34m
NC			:= \033[0m

#################################################################################################
#											Flags												#
#################################################################################################

COMPILER	=	c++
INCLUDES	=	-I includes
CFLAGS		=	-std=c++11 -g  #-Wall -Werror -Wextra #-fsanitize=address
EXTRA_FLAGS	=	#-ffast-math #-0fast
ERROR_FILE	=	error.log

#################################################################################################
#											Sources												#
#################################################################################################

_SRCS			=	main.cpp
SRCS			=	$(addprefix srcs/, $(_SRCS))

OBJS			=	$(SRCS:srcs/%.c=bin/%.o)

#################################################################################################
#											SDL													#
#################################################################################################

USER = $(shell whoami)
OS = $(shell uname)

SDL_FLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2 -lm

#################################################################################################
#											Rules												#
#################################################################################################

all:			SDL $(NAME)

bin:
				@echo "\t\t\t$(BLUE) Making bin directory"
				@mkdir -p bin/

bin/%.o:		srcs/%.c | bin
				@echo "$(GREEN) Compiling $(Compiler) $(CLR_RMV) -c -o $(YELLOW) $@ $(CYAN) $^ $(GREEN) $(EXTRA_FLAGS) $(CFLAGS) $(GREEN) $(INCLUDES) $(NC)"
				@$(COMPILER) -c -o $@ $^ $(EXTRA_FLAGS) $(CFLAGS) $(INCLUDES) 2> $(ERROR_FILE) || (cat $(ERROR_FILE) && echo "$(RED)Compilation failed :0\nfailed file: \t\t$(YELLOW)$<$(NC)\n\n" && exit 1$(NC))

$(LIBRARY):		$(SUBMODULE)
				@make -C main-libs --silent

$(NAME): $(LIBRARY) $(OBJS)
				@$(COMPILER) -o $(NAME) $(OBJS) $(LIB_FLAGS) $(EXTRA_FLAGS) $(CFLAGS) $(SDL_FLAGS)
				@echo "\t\t\t\t$(RED) compilation success :3$(NC)"

SDL:
				@if [ ! -d "SDL" ]; then git clone https://github.com/libsdl-org/SDL.git; fi
				@cd SDL && mkdir build && cd build && cmake .. -DCMAKE_BIULD_TYPE=Release && cmake --build , --config Release --parallel && make install

clean:
				@rm -rf bin
				@rm -f $(ERROR_FILE)

fclean:			clean
				@rm -f $(NAME)
				@rm -rf SDL

soft_clean:
				@rm -f $(NAME)
				@rm -rf bin

re:				fclean all

run:			all
				@./conway

res:			soft_clean all

.PHONY:			all clean fclean re