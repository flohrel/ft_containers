#!/bin/bash

Namespaces=('FT' 'STD')
LOGDIR='log'

compile()
{
	make -C tester NAMESPACE=${1} &> ${LOGFILE}_make
	if [[ "$?" -ne 0 ]]; then
		printf "Error: compilation failed. See log/${LOGFILE}_make for more details."
		exit 1
	fi
}

execute()
{
	TESTER="tester/${1}_tester"

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

if [[ ! ${INCLUDE} ]]; then
	printf "Error: INCLUDE variable not set."
	exit 1
fi

if [[ "$#" -gt 1 ]]; then
	printf "Usage: ./run.sh [NAMESPACE]"
	exit 1
fi

mkdir -p log
if [[ ! -d "./log" ]]; then
	printf "Error: cannot create log folder."
	exit 1
fi

if [[ "$#" -eq 1 ]]; then
	case ${1} in
		FT | STD)
			tester ${1}
			;;

		*)
			printf "Argument is either FT or STD"
			exit 1
			;;
	esac
	exit 0
fi

for i in ${Namespaces[@]}; do
	tester ${i}
done