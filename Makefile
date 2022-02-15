###############
## Variables ##
###############

NAME		=	test

VPATH		=	src
OBJDIR		=	obj
LIBDIR		=	libft
INCLDIR		=	incld

SRC			=	main.cpp
INCLD		=	iterator_traits.hpp \
				iterator.hpp \
				reverse_iterator.hpp \
				vector.hpp
OBJ			=	$(SRC:%.cpp=$(OBJDIR)/%.o)

CC			=	clang++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3
INCFLAGS	=	-I./$(INCLDIR) -I./$(LIBDIR)/incld
LFLAGS		=
RM			=	/bin/rm -rf
UNAME		:=	$(shell uname -s)


###########
## Rules ##
###########

.PHONY:			all bonus clean fclean re verbose

all:			$(NAME)

$(OBJDIR)/%.o:	%.cpp | $(OBJDIR)
				$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

$(OBJDIR):
				mkdir $(OBJDIR)

bonus:
				@make all

clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME) $(OBJDIR)

re:				fclean all

verbose:		CFLAGS += -DVERBOSE=1
verbose:		$(NAME)
