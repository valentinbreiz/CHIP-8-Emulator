##
## EPITECH PROJECT, 2020
## Visual Studio Live Share (Workspace)
## File description:
## Makefile
##

CC      		= 		g++ -g

RM				=		rm -f

NAME            =		chip-8-emulator

CXXFLAGS        =       -I. -I./include -I./include/imgui-1.75 -Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL

SRCS   			=       ./src/main.cpp \
						./src/Application.cpp \
                        ./src/Emulator.cpp \
						./src/Opcodes.cpp \
						./include/imgui-1.75/imgui.cpp \
						./include/imgui-1.75/imgui_draw.cpp \
						./include/imgui-1.75/imgui-SFML.cpp \
						./include/imgui-1.75/imgui_demo.cpp \
						./include/imgui-1.75/imgui_widgets.cpp

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