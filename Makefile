###############
## Variables ##
###############

NAME		=	runner

SRCDIR		=	src
INCLDIR		=	incld
OBJDIR		=	obj
TESTDIR		=	cxxtest

TEST		=	test.hpp
SRC			=	runner.cpp
INCLD		=	iterator_traits.hpp \
				iterator.hpp \
				reverse_iterator.hpp \
				vector.hpp
INCLDS		=	$(addprefix -include,$(INCLD))
OBJ			=	$(SRC:%.cpp=$(OBJDIR)/%.o)

CC			=	clang++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -g3
INCFLAGS	=	$(addprefix -I./$(INCLDIR) , $(INCLDS)) -I./$(TESTDIR)
RM			=	/bin/rm -rf
UNAME		:=	$(shell uname -s)


###########
## Rules ##
###########

.PHONY:			all bonus clean fclean re verbose

all:			$(NAME)

%.cpp:
				$(TESTDIR)/bin/cxxtestgen --error-printer -o src/$@ $(INCLDIR)/$(TEST)

$(OBJDIR)/%.o:	%.cpp | $(OBJDIR)
				$(CC) $(CFLAGS) $(INCFLAGS) -c $(SRCDIR)/$< -o $@

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) -o $@ $(INCFLAGS) $<

$(OBJDIR):
				mkdir $(OBJDIR)

bonus:
				@make all

clean:
				$(RM) $(OBJ) $(SRCDIR)/$(SRC)


fclean:			clean
				$(RM) $(NAME) $(OBJDIR)


re:				fclean all

verbose:		CFLAGS += -DVERBOSE=1
verbose:		$(NAME)
