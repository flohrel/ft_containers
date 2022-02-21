###############
## Variables ##
###############

NAME		=	runner

INCLDIR		=	include
BUILD_DIR	=	build
TESTDIR		=	cxxtest
DEPDIR		=	$(BUILD_DIR)/.deps

TEST		=	test.hpp
SRC			=	runner.cpp
OBJ			=	$(SRC:%.cpp=$(BUILD_DIR)/%.o)
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

$(BUILD_DIR)/%.o:	$(SRC) | $(DEPDIR)
				$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
				$(CXX) $(CXXFLAGS) -o $@ $(CPPFLAGS) $<

$(DEPDIR): ; @mkdir -p $@
$(DEP):
-include $(wildcard $(DEP))

bonus:
				@make all

clean:
				$(RM) $(OBJ) $(SRC)


fclean:			clean
				$(RM) $(NAME) $(BUILD_DIR)

re:				fclean all

verbose:		CFLAGS += -DVERBOSE=1
verbose:		$(NAME)
