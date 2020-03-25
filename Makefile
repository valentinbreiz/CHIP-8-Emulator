##
## EPITECH PROJECT, 2020
## Visual Studio Live Share (Workspace)
## File description:
## Makefile
##

CC      		= 		g++

RM				=		rm -f

NAME            =		chip-8-emulator

CXXFLAGS        =       -I. -I ./include -Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRCS   			=       ./src/main.cpp        \
                        ./src/Emulator.cpp

OBJS   			=		$(SRCS:.cpp=.o)

all:           			$(NAME)

$(NAME)			:       $(OBJS)
						$(CC) $(OBJS) -o $(NAME) $(CXXFLAGS)

clean			:
						$(RM) $(OBJS)

fclean			:   	clean
						$(RM) $(NAME)

re				: 		fclean all

.PHONY			: 		all clean fclean re