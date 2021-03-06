#!/bin/bash

# We want Python to find our own modules
export PYTHONPATH=../../Utils:$PYTHONPATH

# Run the scene
optirun morse run scene_init.py &
sleep 10s

# Run the datalogger
python3.3 data_logger.py 2D-4Transponders-Circle.res 500 10 &

sleep 5s

# Control the trajectory
python3.3 circle.py

