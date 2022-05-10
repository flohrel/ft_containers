#!/bin/bash

# FG COLORS
DEFAULT='\033[0m'
BLACK='\033[1;30m'
RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
MAGENTA='\033[1;35m'
CYAN='\033[1;36m'
WHITE='\033[1;107m'

# TERMCAPS
UP='\033[1A'
DELETE='\033[2K'
DELPREV="${UP}${DELETE}\r"

# EMOJI
CHECK='\xE2\x9C\x94'
CROSS='\xE2\x9D\x8C'

# SCRIPT VARS
Namespaces=('FT' 'STD')
LOGDIR='log'
RETURN_VALUE=0

header()
{
	set -o noglob			# disable globbing to prevent PAD_CHAR from expanding

	HEAD_SIZE=64
	NAME_SIZE=${#1}
	PAD_WIDTH=$(((${HEAD_SIZE} - ${NAME_SIZE}) / 2))
	PAD_PREC=$((${PAD_WIDTH} / 2))
	PAD_CHAR='*'
	PAD_STR=`eval printf "${PAD_CHAR}%.0s" {1..${PAD_WIDTH}}`
	LEFT_PAD=`printf '%-*.*s' ${PAD_WIDTH} ${PAD_PREC} ${PAD_STR}`
	RIGHT_PAD=`printf '%*.*s' $((${PAD_WIDTH} + ${NAME_SIZE} % 2)) ${PAD_PREC} ${PAD_STR}`
	BODY_WIDTH=$((${HEAD_SIZE} - 1))
	
	printf "${LEFT_PAD}${BLUE}${1}${DEFAULT}${RIGHT_PAD}\n"

	set +o noglob			# restore globbing
}

compile()
{
	printf "%-*s" ${BODY_WIDTH} "Compiling..."
	make -sC tester INCLUDE="../${INCLUDE}" NAMESPACE="$1" &> ${LOGFILE}
	if [[ "$?" -ne 0 ]]; then
		printf "${RED}${CROSS}${DEFAULT}\n"
		printf "Error: compilation failed. See ${LOGFILE} for more details.\n"
		exit "$?"
	else
		printf "${GREEN}${CHECK}${DEFAULT}\n"
	fi
}

execute()
{
	TOTAL=0
	for TEST_RUNNER in `ls tester/run_*`; do
		if [[ ! -e ${TEST_RUNNER} ]]; then
			printf "Error: ${TEST_RUNNER}: binary not found.\n"
			exit "$?"
		elif [[ ! -x ${TEST_RUNNER} ]]; then
			chmod +x ${TEST_RUNNER}
		fi

		printf "%-*s" ${BODY_WIDTH} "Executing ${TEST_RUNNER##*/}..."

		./${TEST_RUNNER} &>> ${LOGFILE}

		RETURN_VALUE=$((${RETURN_VALUE}+"$?"))

		local TIME="[$(tac ${LOGFILE} | grep 'Master' | grep 'testing' | grep -Eo "[+-]?([0-9]*[.])?[0-9]+ms$" | head -1)]"
		printf "\033[%dD%s " $((${#TIME} + 1)) ${TIME}

		if [[ "$?" -ne 0 ]]; then
			printf "${RED}${CROSS}${DEFAULT} => errors reported in ${LOGFILE}."
		else
			printf "${GREEN}${CHECK}${DEFAULT}"
		fi
		printf "\n"

		TOTAL=`echo "$(echo ${TIME} | grep -Eo "[+-]?([0-9]*[.])?[0-9]+") + ${TOTAL}" | bc `
	done
}

tester()
{
	header "$1"
	LOGFILE="${LOGDIR}/${1,,}.out"
	compile "$1"
	execute "$1"
	make -C tester fclean &>> ${LOGFILE}
	printf "${MAGENTA}%-*s" ${BODY_WIDTH} "Total time elapsed:"
	printf "\033[%dD%sms${DEFAULT}\n" $((${#TOTAL} + 1)) ${TOTAL}
}

print_usage()
{
	printf "Usage: ./run.sh INCLUDE [FT|STD]\n"
}

if [[ "$#" -lt 1 || "$#" -gt 2 ]]; then
	print_usage
	exit 1
fi

mkdir -p log
if [[ ! -d "./log" ]]; then
	printf "Error: cannot create log folder.\n"
	exit 1
fi

if [[ ! -d "$1" ]]; then
	printf "Error: \"$1\" is not a directory.\n"
	exit 1
else
	INCLUDE="$1"
fi

if [[ "$#" -eq 2 ]]; then
	case "$2" in
		FT | STD)
			tester "$2"
			;;
		*)
			print_usage
			exit 1
			;;
	esac
else
	for i in ${Namespaces[@]}; do
		tester "$i"
		printf "\n"
	done
fi

if [[ "${RETURN_VALUE}" -eq 0 ]]; then
	for log_file in $(ls ${LOGDIR}/*.out); do
		sum=0
		for time in $(cat ${log_file} | grep "Master" | grep testing | grep -Eo "[+-]?([0-9]*[.])?[0-9]+") ; do		# Get total execution time of each binary
			sum=$(echo "${sum} + ${time}" | bc)																							# sum them
		done
		NB+=(${sum})																								# and put them in a list
	done
	QUOTIENT=$(echo "scale=1 ; ${NB[0]} / ${NB[1]}" | bc)															# get the quotient of (ft_exec_time / std_exec_time)
	printf "FT namespace is "
	if [[ $(echo "${QUOTIENT} > 1" | bc | grep 1) ]]; then															# if quotient > 1
		if [[ $(echo "${QUOTIENT} > 20" | bc | grep 1) ]]; then														#	&& quotient > 20
			RETURN_VALUE=1																							 then test failed
		fi
		printf "${RED}%s${DEFAULT} times slower" ${QUOTIENT}
	else
		printf "${GREEN}%s${DEFAULT} times faster" `echo "scale=1; 1 / ${QUOTIENT}" | bc`
	fi
	printf " than STD\n"
fi

exit ${RETURN_VALUE}
