#!/usr/bin/env python
import rospy
import baxter_interface
import actionlib
from baxter_movement.msg import BaxterActionFeedback, BaxterActionResult, BaxterActionAction

rospy.init_node('right_hand')

def callback (goal):
	feedback = BaxterActionFeedback()
	feedback.feedback = 1
	result = BaxterActionResult()
	result.result = 1
	
	print "Right hand moving !"
	angles = dict()

	wave_1 = {'right_s0': goal.coordinates[0], 
		   'right_s1': goal.coordinates[1], 
		   'right_e0': goal.coordinates[2], 
		   'right_e1': goal.coordinates[3], 
		   'right_w0': goal.coordinates[4], 
		   'right_w1': goal.coordinates[5], 
		   'right_w2': goal.coordinates[6]}

	limbR.move_to_joint_positions(wave_1, 15, goal.precision)

	server.publish_feedback(feedback)
	server.set_succeeded(result)

rospy.sleep(0.1)
limbR = baxter_interface.Limb('right')
server = actionlib.SimpleActionServer('/Rhand_server', BaxterActionAction, callback, False)
server.start()
print ("right hand ready")
rospy.spin()


	
