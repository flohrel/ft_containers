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
DELPREV='$(UP)$(DELETE)\r'

# EMOJI
CHECK='\xE2\x9C\x94'
CROSS='\xE2\x9D\x8C'

# SCRIPT VARS
Namespaces=('FT' 'STD')
LOGDIR='log'
RETURN_VALUE=0

header()
{
	PADDING_SIZE1=$((10 - ${#1}))
	PADDING_SIZE2=$((15 - ${#1} % 2))
	printf "%-15.*s${BLUE}%s${DEFAULT}%*.*s\n" "${PADDING_SIZE1}" "**********" "${1}" "${PADDING_SIZE2}" "${PADDING_SIZE1}" "**********"
}

compile()
{
	INCLUDE_PARENT_DIR=`dirname ${INCLUDE}`
	printf "%-30s" "Compiling..."
	make -C tester INCLUDE="../${INCLUDE_PARENT_DIR}" NAMESPACE="$1" &> ${LOGFILE}
	if [[ "$?" -ne 0 ]]; then
		printf "${RED}${CROSS}${DEFAULT}\n"
		printf "Error: compilation failed. See ${LOGFILE} for more details.\n"
		exit $?
	else
		printf "${GREEN}${CHECK}${DEFAULT}\n"
	fi
}

execute()
{
	TESTER="tester/tester"

	if [[ ! -e ${TESTER} ]]; then
		printf "Error: binary not found.\n"
		exit $?
	elif [[ ! -x ${TESTER} ]]; then
		chmod +x ${TESTER}
	fi

	printf "%-30s" "Executing..."

	./${TESTER} &>> ${LOGFILE}

	RETURN_VALUE=$(($RETURN_VALUE+$?))

	if [[ "$?" -ne 0 ]]; then
		printf "${RED}${CROSS}${DEFAULT} => "
		printf "errors reported in ${LOGFILE}.\n"
	else
		printf "${GREEN}${CHECK}${DEFAULT}\n"
	fi
}

tester()
{
	header "$1"
	LOGFILE="${LOGDIR}/${1,,}.out"
	compile "$1"
	execute "$1"
	make -C tester fclean &>> ${LOGFILE}
	printf "Time elapsed:"
	printf "%19s\n\n" `grep 'Total elapsed time' ${LOGFILE} | grep -Eo "[+-]?([0-9]*[.])?[0-9]+ms$"`
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
	done
fi

if [[ "${RETURN_VALUE}" -eq 0 ]]; then
	for n in $(grep 'Total elapsed time' ${LOGDIR}/*.out | grep -Eo "[+-]?([0-9]*[.])?[0-9]+") ; do		# Get total execution time of each binary
		NB+=("$n")																						# and put them in a list
	done
	QUOTIENT=$(echo "scale=1 ; ${NB[0]} / ${NB[1]}" | bc)												# get the quotient of (ft_exec_time / std_exec_time)
	printf "FT containers are "
	if [[ $(echo "${QUOTIENT} > 1" | bc | grep 1) ]]; then												# if quotient > 1
		if [[ $(echo "${QUOTIENT} > 20" | bc | grep 1) ]]; then											#	&& quotient > 20
			RETURN_VALUE=1																				# then test failed
		fi
		printf "%s times slower" ${QUOTIENT}
	else
		printf "%s times faster" `echo "scale=1; 1 / ${QUOTIENT}" | bc`
	fi
	printf " than STD ones\n"
fi

exit ${RETURN_VALUE}