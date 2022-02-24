###############
## Variables ##
###############

NAME		=	runner

INCLDIR		=	include
BUILDIR	=	build
TESTDIR		=	cxxtest
DEPDIR		=	$(BUILDIR)/.deps

TEST		=	vectorSuite.hpp
SRC			=	runner.cpp
OBJ			=	$(SRC:%.cpp=$(BUILDIR)/%.o)
DEP			=	$(SRC:%.cpp=$(DEPDIR)/%.d)

CXX			=	clang++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3
CPPFLAGS	=	-I./$(INCLDIR) -I./$(TESTDIR)
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
RM			=	/bin/rm -rf
UNAME		:=	$(shell uname -s)


###########
## Rules ##
###########

.PHONY:			all bonus clean fclean re verbose

all:			$(NAME)

$(SRC):
				$(TESTDIR)/bin/cxxtestgen --error-printer -o $@ $(INCLDIR)/$(TEST)

$(BUILDIR)/%.o:	$(SRC) | $(DEPDIR)
				$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
				$(CXX) $(CXXFLAGS) -o $@ $(CPPFLAGS) $<

$(DEPDIR):		; @mkdir -p $@
$(DEP):
-include $(wildcard $(DEP))

bonus:
				@make all

clean:
				$(RM) $(OBJ) $(SRC)


fclean:			clean
				$(RM) $(NAME) $(BUILDIR)

re:				fclean all

verbose:		CFLAGS += -DVERBOSE=1
verbose:		$(NAME)
