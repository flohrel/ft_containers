#!/bin/bash

Namespaces=('FT' 'STD')
LOGDIR='log'

compile()
{
	INCLUDE_PARENT_DIR=`dirname ${INCLUDE}`
	make -C tester INCLUDE=../${INCLUDE_PARENT_DIR} NAMESPACE=${1} &> ${LOGFILE}_make
	if [[ "$?" -ne 0 ]]; then
		printf "Error: compilation failed. See ${LOGFILE}_make for more details."
		exit 1
	fi
}

execute()
{
	TESTER="tester/tester"

	if [[ ! -e ${TESTER} ]]; then
		printf "Error: binary not found."
		exit 1
	elif [[ ! -x ${TESTER} ]]; then
		chmod +x ${TESTER}
	fi
	./${TESTER} &> ${LOGFILE}_test
}

tester()
{
	LOGFILE="${LOGDIR}/${1,,}"
	compile ${1}
	execute ${1}
	make -C tester fclean &>> ${LOGFILE}_make
}

if [[ "$#" -lt 1 || "$#" -gt 2 ]]; then
	printf "Usage: ./run.sh INCLUDE [NAMESPACE]"
	exit 1
fi

mkdir -p log
if [[ ! -d "./log" ]]; then
	printf "Error: cannot create log folder."
	exit 1
fi

if [[ ! -d "${1}" ]]; then
	printf "Error: \"${1}\" is not a directory."
	exit 1
fi

if [[ "$#" -eq 2 ]]; then
	case ${2} in
		FT | STD)
			tester ${2}
			;;
		*)
			printf "Namespace argument is either FT or STD"
			exit 1
			;;
	esac
else
	for i in ${Namespaces[@]}; do
		tester ${i}
	done
fi

exit 0