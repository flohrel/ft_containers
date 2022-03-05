###############
## Variables ##
###############

NAME		=	runner

INCLDIR		=	include
BUILDIR		=	build
TESTDIR		=	cxxtest
DEPDIR		=	$(BUILDIR)/.deps

TEST		=	mapSuite.hpp
SRC			=	runner.cpp
OBJ			=	$(SRC:%.cpp=$(BUILDIR)/%.o)
DEP			=	$(SRC:%.cpp=$(DEPDIR)/%.d)

CXX			=	clang++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3
CPPFLAGS	=	-I./$(INCLDIR) -I./$(TESTDIR)
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
RM			=	/bin/rm -rf
UNAME		:=	$(shell uname -s)

DEFAULT		=	\033[0m
BLACK		=	\033[1;30m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
MAGENTA 	=	\033[1;35m
CYAN 		=	\033[1;36m
WHITE 		=	\033[1;107m
DELETE		=	\033[2K

###########
## Rules ##
###########

.PHONY:			all bonus clean fclean re verbose

all:			$(NAME)

$(SRC):
				@echo -n "$(YELLOW)Generating $@...$(DEFAULT)"
				@$(TESTDIR)/bin/cxxtestgen --error-printer -o $@ $(INCLDIR)/$(TEST)
				@echo "$(DELETE)\r$(GREEN)$@ generated$(DEFAULT)"


$(BUILDIR)/%.o:	$(SRC) | $(DEPDIR)
				@echo -n "$(YELLOW)Compiling $@ and generating/checking make dependency file...$(DEFAULT)"
				@$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
				@echo "$(DELETE)\r$(GREEN)$@ compiled$(DEFAULT)"

$(NAME):		$(OBJ)
				@echo -n "$(YELLOW)Linking source files and generating $@ binary...$(DEFAULT)"
				@$(CXX) $(CXXFLAGS) -o $@ $(CPPFLAGS) $<
				@echo "$(DELETE)\r$(GREEN)$@ binary generated$(DEFAULT)"

$(DEPDIR):
				@echo -n "$(YELLOW)Creating $@ folder...$(DEFAULT)"
				@mkdir -p $@
				@echo "$(DELETE)\r$(GREEN)$@ created$(DEFAULT)"
$(DEP):
-include $(wildcard $(DEP))

bonus:
				@make all

clean:
				@echo -n "$(YELLOW)Deleting object and dependency files...$(DEFAULT)"
				@$(RM) $(OBJ)
				@echo "$(DELETE)\r$(GREEN)Build files deleted$(DEFAULT)"


fclean:			clean
				@echo -n "$(YELLOW)Deleting build directory and binary...$(DEFAULT)"
				@$(RM) $(NAME) $(SRC) $(BUILDIR)
				@echo "$(DELETE)\r$(GREEN)Build directory and binary deleted$(DEFAULT)"

re:				fclean
				@make -s all
