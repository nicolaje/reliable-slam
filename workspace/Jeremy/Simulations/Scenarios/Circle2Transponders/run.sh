#!/usr/bin/bash

optirun morse run scene_init.py &
sleep 10s

python data_logger.py&
sleep 1s

python trajectory_controller.py
