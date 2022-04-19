###############
## Variables ##
###############

NAME		=	tester

VPATH		=	src libunitcpp/src
LIBDIR		=	libunitcpp
INCLUDE		=
INCLDIR		=	$(addsuffix /include,$(INCLUDE) ./libunitcpp .)
BUILDIR		=	build
DEPDIR		=	$(BUILDIR)/.deps

SRC			=	main.cpp \
				vector_suite.cpp
OBJ			=	$(SRC:%.cpp=$(BUILDIR)/%.o)
DEP			=	$(SRC:%.cpp=$(DEPDIR)/%.d)

CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98
CPPFLAGS	=	$(addprefix -I, $(INCLDIR))
LDFLAGS		=	-Llibunitcpp -lunitcpp
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

RM			=	/bin/rm -rf
UNAME		:=	$(shell uname -s)

NAMESPACE	=	STD
ifeq ($(NAMESPACE),STD)
	DEFINE	=	-DSTD=1
else
	DEFINE	=	-DSTD=0
endif

# FG COLORS
DEFAULT		=	\033[0m
BLACK		=	\033[1;30m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
MAGENTA 	=	\033[1;35m
CYAN 		=	\033[1;36m
WHITE 		=	\033[1;107m

# TERMCAPS
UP			=	\033[1A
DELETE		=	\033[2K
DELPREV		=	$(UP)$(DELETE)\r

# EMOJI
CHECK		=	\0xE2\0x9C\0x94
CROSS		=	\0xE2\0x9D\0x8C


###########
## Rules ##
###########

.PHONY:			all bonus clean fclean header lib re verbose

all:			lib header $(NAME)

$(BUILDIR)/%.o:	%.cpp | $(DEPDIR)
				@printf "$(YELLOW)Compiling $@ and generating/checking make dependency file...$(DEFAULT)\n"
				@$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
				@printf "$(DELPREV)%-25s%*s$(GREEN)$(CHECK)$(DEFAULT)\n" $@ $(shell printf "$(NAME)" | wc -c)

$(NAME):		$(OBJ)
				@printf "$(YELLOW)Linking source files and generating $@ binary...\n$(DEFAULT)"
				@$(CXX) $(CXXFLAGS) -o $@ $(CPPFLAGS) $^ $(LDFLAGS)
				@printf "$(DELPREV)$(GREEN)Binary generated$(DEFAULT)\n"

$(DEPDIR):
				@printf "$(YELLOW)Creating $@ folder...$(DEFAULT)\n"
				@mkdir -p $@
				@printf "$(DELPREV)"
$(DEP):
-include $(wildcard $(DEP))

lib:
				@make -C libunitcpp

header:
				@printf "**********%3$1s$(BLUE)$(NAME)$(DEFAULT)%3$1s**********\n" ""

clean:
				@printf "$(YELLOW)Deleting object and dependency files...$(DEFAULT)\n"
				@$(RM) $(OBJ)
				@printf "$(DELPREV)Build files deleted\n"

fclean:			clean
				@printf "$(YELLOW)Deleting build directory and library...$(DEFAULT)\n"
				@$(RM) $(BUILDIR) $(NAME)
				@printf "$(DELPREV)Build directory and binaries deleted\n"
				@make -C $(LIBDIR) fclean

re:				fclean
				@make -s all
