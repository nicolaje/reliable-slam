#! /usr/bin/env bash
if [ "$1" != "" ]; then
	optirun morse run Simulations $1 &
	sleep 15
	if [ -z "$2" ]; then
		scripts/DataLogger.py "$1_manual"
		sleep 5
		scripts/ManualCtl.py
	else
		scripts/DataLogger.py "$1_$2"
		sleep 5
		"scripts/$2.sh"
	fi
fi
