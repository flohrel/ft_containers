###############
## Variables ##
###############

INCLUDE		=	# MUST be set to the folder with your container files
TESTDIR		=	tester
LOGDIR		=	log

RM			=	/bin/rm -rf

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
CHECK		=	\xE2\x9C\x94
CROSS		=	\xE2\x9D\x8C


###########
## Rules ##
###########

all:			run

clean:
				@printf "$(YELLOW)Deleting log files...$(DEFAULT)\n"
				@$(RM) $(OBJ)
				@printf "$(DELPREV)Log files deleted\n"

fclean:			clean
				@printf "$(YELLOW)Deleting log directory...$(DEFAULT)\n"
				@$(RM) $(LOGDIR)
				@printf "$(DELPREV)Log directory deleted\n"
				@make -C $(TESTDIR) fclean

run:
ifeq ($(strip $(INCLUDE)),)
	$(error Set the INCLUDE variable before running (eg. make INCLUDE='../include'))
endif
				@INCLUDE=$(INCLUDE)
				@./run.sh

re:				fclean
				@make -s all
