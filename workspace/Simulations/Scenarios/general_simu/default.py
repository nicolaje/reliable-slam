#! /usr/bin/env morseexec
from morse.builder import *
from general_simu.builder.actuators import Motionfull

sub=Submarine()

motionfull=Motionfull()
sub.append(motionfull)

pose = Pose()
sub.append(pose)

sub.add_default_interface('socket')

# set 'fastmode' to True to switch to wireframe mode
env = Environment('sandbox', fastmode = False)
env.place_camera([10.0, -10.0, 10.0])
env.aim_camera([1.05, 0, 0.78])

