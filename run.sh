#!/bin/bash

Namespace=('FT' 'STD')
FT_LOG="logs/FT_test"
STD_LOG="logs/STD_test"

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

mkdir -p logs
if [[ ! -d "./logs" ]]; then
	printf "Error: cannot create log folder."
	exit 1
fi

for i in ${Namespace[@]}; do
	compile ${i}
	execute ${i}
	make -C tester fclean &>> logs/${i}_make
done

if [[ -e ${FT_LOG} && -e ${STD_LOG} ]]; then
	diff -y ${FT_LOG} ${STD_LOG}
fi