#!/bin/ksh

BASEDIR=$1
EXEC=$2
FLAG=$3

if [[ $# == 2 ]]
then
	FLAG=N
fi

if [[ $FLAG == Y || $FLAG == y ]]
then
	echo "Running $EXEC with argument "
	$EXEC $ITEM
else
	echo "Running $EXEC without argument"
	$BASEDIR/$EXEC
fi
