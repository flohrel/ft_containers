###############
## Variables ##
###############

NAME		=	runner

SRCDIR		=	src
INCLDIR		=	incld
OBJDIR		=	obj
TESTDIR		=	cxxtest

INCLD		=	algorithm.hpp \
				iterator.hpp \
				iterator_traits.hpp \
				reverse_iterator.hpp \
				vector.hpp
TEST		=	test.hpp
SRC			=	runner.cpp
INCLDS		=	$(addprefix -include,$(INCLD))
OBJ			=	$(SRC:%.cpp=$(OBJDIR)/%.o)

CXX			=	clang++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3
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
				$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $(SRCDIR)/$< -o $@

$(NAME):		$(OBJ)
				$(CXX) $(CXXFLAGS) -o $@ $(INCFLAGS) $<

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
