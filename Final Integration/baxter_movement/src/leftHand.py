#!/usr/bin/env python
import rospy
import baxter_interface
import actionlib
from baxter_movement.msg import BaxterActionFeedback, BaxterActionResult, BaxterActionAction

rospy.init_node('left_hand')


def callback (goal):
	feedback = BaxterActionFeedback()
	feedback.feedback = 1
	result = BaxterActionResult()
	result.result = 1
	
	print "Left hand moving !"
	anglesL = dict()

	for x in range (0,6):
		print goal.coordinates[x]
	
	print goal.precision

	#limbL.move_to_joint_positions(anglesL)

	wave_1L = {'left_s0': goal.coordinates[0], 
		   'left_s1': goal.coordinates[1], 
		   'left_e0': goal.coordinates[2], 
		   'left_e1': goal.coordinates[3], 
		   'left_w0': goal.coordinates[4], 
		   'left_w1': goal.coordinates[5], 
		   'left_w2': goal.coordinates[6]}

	limbL.move_to_joint_positions(wave_1L, 15, goal.precision)

	server.publish_feedback(feedback)
	server.set_succeeded(result)

rospy.sleep(0.5)
limbL = baxter_interface.Limb('left')
server = actionlib.SimpleActionServer('/Lhand_server', BaxterActionAction, callback, False)
server.start()
print ("left hand ready")
rospy.spin()


