#! /usr/bin/env bash
if [ "$1" != "" ] && [ "$2" != "" ]
	export SIMULATION_DURATION=$3
	then
	if [ -f "$WORKSPACE_DIR/Simulations/data/$1" ]
	then
		export TRANSPONDERS_POS="$1"
		echo "Using position file: $TRANSPONDERS_POS"
	else
		echo "Position file not found, using the default one"
		export TRANSPONDERS_POS="default.pos"
	fi
	optirun morse run Simulations &
	sleep 15
	if [ ! -f "$WORKSPACE_DIR/Simulations/scripts/$2" ]
	then
		echo "Control script $WORKSPACE_DIR/Simulations/scripts/$2 doesn't exist, using manual control instead"
		export CTL_SCRIPT="ManualCtl.py"
	else
		echo "Using control script $2"
		export CTL_SCRIPT=$2
	fi
	"$WORKSPACE_DIR/Simulations/scripts/DataLogger.py"
	sleep 5
	"$WORKSPACE_DIR/Simulations/scripts/$CTL_SCRIPT"
else
	echo "Usage: run_simu.sh position_file.pos control_script.py duration"
fi
