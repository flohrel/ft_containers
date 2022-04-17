#!/bin/bash

Namespace=('FT' 'STD')
FT_LOG="log/FT_test"
STD_LOG="log/STD_test"

compile()
{
	make -C tester NAMESPACE=${1} &> logs/${1}_make
	if [[ "$?" -ne 0 ]]; then
		printf "Error: compilation failed. See logs/${1}_make for more details."
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
	./${TESTER} &> logs/${1}_test
}

tester()
{
	compile ${i}
	execute ${i}
	make -C tester fclean &>> logs/${i}_make
}

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

for i in ${Namespace[@]}; do
	tester ${i}
done

if [[ -e ${FT_LOG} && -e ${STD_LOG} ]]; then
	diff -y ${FT_LOG} ${STD_LOG}
fi