###############
## Variables ##
###############

NAME		=	test

VPATH		=	src
OBJDIR		=	obj
INCLDIR		=	incld

SRC			=	main.cpp
INCLD		=	iterator_traits.hpp \
				iterator.hpp \
				reverse_iterator.hpp \
				vector.hpp
INCLDS		=	$(addprefix -include,$(INCLD))
OBJ			=	$(SRC:%.cpp=$(OBJDIR)/%.o)

CC			=	clang++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -g3
INCFLAGS	=	$(addprefix -I./$(INCLDIR) , $(INCLDS))
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
