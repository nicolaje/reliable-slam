#! /usr/bin/env bash

# http://stackoverflow.com/questions/59895/can-a-bash-script-tell-what-directory-its-stored-in
export WORKSPACE_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

export SIMU_DURATION=200
export TRANSPONDERS_POS="default.pos"
export CTL_SCRIPT="ManualCtl.py"
