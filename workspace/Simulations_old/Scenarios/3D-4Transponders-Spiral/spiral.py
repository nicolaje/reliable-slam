import time
import pymorse
import sys
from datetime import datetime
from time import sleep
from math import *
import rospy
from geometry_msgs.msg import Twist

cmd = rospy.Publisher("/atrv/motion", Twist)
motion = Twist()
def callback(msg):
	position = msg.pose.position
	if position.x < 1:
		motion.linear.x = +0.5
		motion.linear.z = +10
	if position.x > 2:
		motion.linear.x = -0.5
	cmd.publish(motion)

rospy.init_node("rostuto1")
rospy.Subscriber("/atrv/pose", PoseStamped, callback)
rospy.spin() # this will block untill you hit Ctrl+C
