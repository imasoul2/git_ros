#!/usr/bin/env python
import rospy
import baxter_interface
import actionlib
from baxter_movement.msg import BaxterHeadFeedback, BaxterHeadResult, BaxterHeadAction

rospy.init_node('head')

def callback (goal):
	feedback = BaxterHeadFeedback()
	feedback.feedback = 1
	result = BaxterHeadResult()
	result.result = 1
	
	print "Head moving !"
	angleH = dict()

	angle = goal.angle
	speed = goal.speed

	head.set_pan(angle, speed, timeout=5)

	server.publish_feedback(feedback)
	server.set_succeeded(result)

rospy.sleep(0.25)
head = baxter_interface.Head()
server = actionlib.SimpleActionServer('/Head_server', BaxterHeadAction, callback, False)
server.start()
print ("Head ready")
rospy.spin()


	
