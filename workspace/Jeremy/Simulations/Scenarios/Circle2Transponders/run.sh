#!/bin/bash

# Run the scene
optirun morse run scene_init.py &
sleep 10s

# Run the datalogger
#python data_logger.py &
#sleep 1s

# Control the trajectory
python trajectory_controller.py
