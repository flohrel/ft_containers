###############
## Variables ##
###############

NAME		=	runner

INCLDIR		=	include
BUILDIR		=	build
TESTDIR		=	
DEPDIR		:=	$(BUILDIR)/.deps

TEST		=	
SRC			=	
OBJ			=	$(SRC:%.cpp=$(BUILDIR)/%.o)
DEP			=	$(SRC:%.cpp=$(DEPDIR)/%.d)

CXX			=	clang++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3
CPPFLAGS	:=	-I./$(INCLDIR) -I./$(TESTDIR)
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


$(BUILDIR)/%.o:	$(SRC) | $(DEPDIR)
				@printf "$(YELLOW)Compiling $@ and generating/checking make dependency file...$(DEFAULT)"
				@$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
				@printf "$(DELETE)\r$(GREEN)$@ compiled$(DEFAULT)\n"

$(NAME):		$(OBJ)
				@printf "$(YELLOW)Linking source files and generating $@ binary...$(DEFAULT)"
				@$(CXX) $(CXXFLAGS) -o $@ $(CPPFLAGS) $<
				@printf "$(DELETE)\r$(GREEN)$@ binary generated$(DEFAULT)\n"

$(DEPDIR):
				@printf "$(YELLOW)Creating $@ folder...$(DEFAULT)"
				@mkdir -p $@
				@printf "$(DELETE)\r$(GREEN)$@ created$(DEFAULT)\n"
$(DEP):
-include $(wildcard $(DEP))

bonus:
				@make all

clean:
				@printf "$(YELLOW)Deleting object and dependency files...$(DEFAULT)"
				@$(RM) $(OBJ)
				@printf "$(DELETE)\r$(GREEN)Build files deleted$(DEFAULT)\n"


fclean:			clean
				@printf "$(YELLOW)Deleting build directory and binary...$(DEFAULT)"
				@$(RM) $(NAME) $(BUILDIR)
				@printf "$(DELETE)\r$(GREEN)Build directory and binary deleted$(DEFAULT)\n"

re:				fclean
				@make -s all
