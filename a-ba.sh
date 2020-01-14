#!/bin/bash

#Hvis miljøvariabel er satt
if [ -n "$KONTO" ]
then
    ./a.out $1 | sort |
	if [ "$KONTO" == "b" ]
	then
	    while read line
	    do
		BNAVN=${line%% *}
		#echo $BNAVN
		printf %s"$line"
		if [ -f /home/$BNAVN/public_html/pub_key.asc ]
		then
		    printf %s" <-- USER HAS KEY!"

		fi
		printf %s"\n"
	    done

	elif [ "$KONTO" != "b" ]
	then
	    while read line
	    do
		BNAVN=${line##* }
		printf %s"$line"
		#echo $BNAVN
		if [ -f /home/$BNAVN/public_html/pub_key.asc ]
		then
		    printf %s" <-- USER HAS KEY!"

		fi
		printf %s"\n"
	    done
	fi
fi

#Hvis miljøvariabel ikke er satt
if [ -z "$KONTO" ]
then
    ./a.out $1 | sort |
	if [ "$1" == "b" ]
	then
	    while read line
	    do
		BNAVN=${line%% *}
		printf %s"$line"
		#printf %s"argument lik b"
		if [ -f /home/$BNAVN/public_html/pub_key.asc ]
		   then
		   printf %s" <-- USER HAS KEY!"
		    
		fi
		printf %s"\n"
	    done
    
	elif [ "$1" != "b" ]
	    then
	    while read line
	    do
		BNAVN=${line##* }
		printf %s"$line"
		#printf %s"argument ulikt b"
		if [ -f /home/$BNAVN/public_html/pub_key.asc ]
		then
		    printf %s" <-- USER HAS KEY!"

		fi
		printf %s"\n"
	    done
	fi
fi
