###############
## Variables ##
###############

NAME		=	tester

VPATH		=	src libunitcpp/src
LIBDIR		=	libunitcpp
INCLUDE		=	# MUST be set to your headers' directory path before running (eg. "../include")
INCLDIR		=	$(addsuffix /include,$(LIBDIR) .) $(INCLUDE)
BUILDIR		=	build
DEPDIR		=	$(BUILDIR)/.deps

SRC			=	vector_suite.cpp \
				map_suite.cpp \
				set_suite.cpp \
				stack_suite.cpp
OBJ			=	$(SRC:%.cpp=$(BUILDIR)/%.o)
DEP			=	$(SRC:%.cpp=$(DEPDIR)/%.d)

CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3
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
DIM			=	\033[2m

# TERMCAPS
UP			=	\033[1A
DELETE		=	\033[2K
DELPREV		=	$(UP)$(DELETE)\r

# EMOJI
CHECK		=	\xE2\x9C\x94
CROSS		=	\xE2\x9D\x8C

# DISPLAY
HEAD_SIZE	=	64
NAME_SIZE	=	$(shell NAME='$(NAME)'; printf "$${\#NAME}")
PAD_WIDTH	=	$(shell printf "$$((($(HEAD_SIZE) - $(NAME_SIZE)) / 2))")
PAD_PREC	=	$(shell printf "$$(($(PAD_WIDTH) / 2))")
PAD_CHAR	=	\*
PAD_STR		=	$(shell printf '$(PAD_CHAR)%.0s' {1..$(PAD_WIDTH)})
LEFT_PAD	=	$(shell printf '%-*.*s' $(PAD_WIDTH) $(PAD_PREC) $(PAD_STR))
RIGHT_PAD	=	$(shell printf '%*.*s' $$(($(PAD_WIDTH) + $(NAME_SIZE) % 2)) $(PAD_PREC) $(PAD_STR))
BODY_WIDTH	=	$(shell printf "$$(($(HEAD_SIZE) - 1))")


###########
## Rules ##
###########


.PHONY:			all bonus clean fclean header lib re verbose

all:			lib header $(NAME)

ifeq (,$(strip $(findstring clean, $(MAKECMDGOALS))))		# if the command call is not a cleaning rule
ifeq (,$(strip $(INCLUDE)))									# if INCLUDE variable hasn't been set
  	$(error Set the INCLUDE variable before running (eg. make 'INCLUDE=../include'))	# abort
endif
endif

$(BUILDIR)/%.o:	%.cpp | $(DEPDIR)
				@printf "$(YELLOW)Compiling $@ and generating/checking make dependency file...$(DEFAULT)\n"
				@$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
				@printf '$(DELPREV)%-*s$(GREEN)$(CHECK)$(DEFAULT)\n' $(BODY_WIDTH) $(notdir $@)
				@printf "$(YELLOW)Linking source files and generating $@ binary...\n$(DEFAULT)"
				@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o run_$(basename $(notdir $@)) $^ $(LDFLAGS)
				@printf "$(DELPREV)$(GREEN)Binary generated$(DEFAULT)\n"

$(NAME):		$(OBJ)

$(DEPDIR): 
				@printf "$(YELLOW)Creating $@ folder...$(DEFAULT)\n"
				@mkdir -p $@
				@printf "$(DELPREV)"
$(DEP):
-include $(wildcard $(DEP))

lib:
				@$(MAKE) -sC libunitcpp

header:
				@printf "\n$(LEFT_PAD)$(BLUE)$(NAME)$(DEFAULT)$(RIGHT_PAD)\n"

clean:
				@printf "$(YELLOW)[$(NAME)] Deleting object and dependency files...$(DEFAULT)\n"
				@$(RM) $(OBJ)
				@printf "$(DELPREV)$(DIM)[$(NAME)] Build files deleted$(DEFAULT)\n"

fclean:			clean
				@printf "$(YELLOW)[$(NAME)] Deleting build directory and library...$(DEFAULT)\n"
				@$(RM) $(BUILDIR) $(wildcard run_*)
				@printf "$(DELPREV)$(DIM)[$(NAME)] Build directory and binary deleted$(DEFAULT)\n"
				@$(MAKE) -sC $(LIBDIR) fclean

re:				fclean
				@$(MAKE) -s all
