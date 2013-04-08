#!/bin/bash

# We want Python to find our own modules
export PYTHONPATH=../../Utils:$PYTHONPATH

# Run the scene
optirun morse run scene_init.py &
sleep 10s

# Run the datalogger
#python data_logger.py &
#sleep 1s

# Control the trajectory
python3.3 trajectory_controller.py
