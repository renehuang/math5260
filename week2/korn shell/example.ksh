#!/bin/ksh

BASEDIR=/mnt/nas/shared/cPlusPlus/lecture2/exampleKornShell

YEAR=`/bin/date +%Y`
MONTH=`/bin/date +%m`
TODAY=`/bin/date +%d`
HOUR=`/bin/date +%H`
MINUTE=`/bin/date +%M`
#HOUR=16
#MINUTE=20
echo "$HOUR:$MINUTE"

LISTFILE=listExample

SUBLIST=$BASEDIR/$LISTFILE
BINDIR=$BASEDIR
PROG=exampleExe
LIST=`/bin/grep -v ^# $SUBLIST | /bin/cat`

if [[ ! -d $BASEDIR ]]
then
	echo "$BASEDIR does not exist."
	exit 1
fi

# launching all programs
for item in $LIST
do
	MARKET=`/bin/echo $item | /bin/cut -d, -f1`
	SYMBOL=`/bin/echo $item | /bin/cut -d, -f2`
	PRICE=`/bin/echo $item | /bin/cut -d, -f3`
	
	echo "Launch $MARKET for symbol=$SYMBOL"
	
	cd $BINDIR
	echo "Year, Month, Day, Hour, Min = $YEAR/$MONTH/$TODAY at $HOUR:$MINUTE ... "
	$BINDIR/$PROG $MARKET $PRICE $HOUR $MINUTE $SYMBOL & 

done