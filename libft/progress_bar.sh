#!/usr/bin/env

function progr_bar()
{
	MAX=$1
	PERCENT=0
	FOO=">"
	BAR=""

	while [ $PERCENT -lt $(($MAX+1)) ]
	do  
		#echo -ne "\r\t[ "
		echo make "\r\t[ $BAR$FOO ] $((PERCENT*100/$MAX))% "
		BAR="${BAR}="
		let PERCENT=$PERCENT+1
		sleep 0.2
		clear
	done
	echo  " Done.\n"
}

progr_bar 20
