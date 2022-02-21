###############
## Variables ##
###############

NAME		=	runner

VPATH		=	src
INCLDIR		=	incld
OBJDIR		=	obj
TESTDIR		=	cxxtest

TEST		=	test.hpp
SRC			=	runner.cpp
OBJ			=	$(SRC:%.cpp=$(OBJDIR)/%.o)

CXX			=	clang++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3
CPPFLAGS	=	-I./$(INCLDIR) -I./$(TESTDIR)
RM			=	/bin/rm -rf
UNAME		:=	$(shell uname -s)


###########
## Rules ##
###########

.PHONY:			all bonus clean fclean re verbose

all:			$(NAME)

%.cpp:
				$(TESTDIR)/bin/cxxtestgen --error-printer -o $@ $(INCLDIR)/$(TEST)

$(OBJDIR)/%.o:	%.cpp | $(OBJDIR)
				$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
				$(CXX) $(CXXFLAGS) -o $@ $(CPPFLAGS) $<

$(OBJDIR):
				mkdir $(OBJDIR)

bonus:
				@make all

clean:
				$(RM) $(OBJ) $(VPATH)/$(SRC)


fclean:			clean
				$(RM) $(NAME) $(OBJDIR)


re:				fclean all

verbose:		CFLAGS += -DVERBOSE=1
verbose:		$(NAME)
