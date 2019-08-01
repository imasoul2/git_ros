#!/usr/bin/env python

import rospy
import sys
import actionlib


from baxter_movement.msg import BaxterActionFeedback, BaxterActionResult, BaxterActionAction, BaxterActionGoal, BaxterHeadFeedback, BaxterHeadResult, BaxterHeadAction, BaxterHeadGoal
from baxter_movement.srv import *

def feedback(fb, fb2):
	None

def handle_motion_request(req):
	# finish the motion
	# if it was successfully done
	goal = BaxterActionGoal()
	headgoal = BaxterHeadGoal()
	
	# (0) IRONMAN POSITION	
	if req.data == 0 :
		# Left hand camera positioning towards the user standing infront		
		goal.coordinates = [-1.1,0.3,2.95,1.8,0.19,-1.57, -3.05]
		goal.precision = 0.1
		LHandClient.send_goal(goal, feedback)
		# Right hand moving down in dormant position 
		goal.coordinates = [0,1,0,0,0,0,0]
		goal.precision = 0.1
		RHandClient.send_goal(goal, feedback)
		# Head positioning straight forward		
		headgoal.angle = 0
		headgoal.speed = 0.1
		headClient.send_goal(headgoal,feedback)
		LHandClient.wait_for_result()
		RHandClient.wait_for_result()
		headClient.wait_for_result()
	
	# (1) HELLO MOVEMENT
	if req.data == 1 :
		# Left hand camera positioning towards the user standing infront		
		goal.coordinates = [-1.1,0.3,2.95,1.8,0.19,-1.57, -3.05]
		goal.precision = 0.1
		LHandClient.send_goal(goal, feedback)
		headgoal.angle = 0
		headgoal.speed = 0.1
		headClient.send_goal(headgoal,feedback)
		
		# FOR loop to constantly swap between joint positions for the hello movement
		for _move in range(3):
			# Position 1 of right hand for the hello movement			
			goal.coordinates = [-0.459,-0.202,1.807,1.714,-0.906,-1.545,-0.276]
			goal.precision = 0.2
			RHandClient.send_goal(goal, feedback)
			RHandClient.wait_for_result()		
			# Position 2 of right hand for the hello movement
			goal.coordinates = [-0.395,-0.202,1.831,1.981,-1.979,-1.100,-0.448]
			goal.precision = 0.2
			RHandClient.send_goal(goal, feedback)
			RHandClient.wait_for_result()
		
		LHandClient.wait_for_result()
		headClient.wait_for_result()
		
	# (2) HANDSHAKE MOVEMENT
	if req.data == 2 :
		# Left hand camera positioning towards the user standing infront
		goal.coordinates = [-1.1,0.3,2.95,1.8,0.19,-1.57, -3.05]
		goal.precision = 0.1
		LHandClient.send_goal(goal, feedback)
		headgoal.angle = 0
		headgoal.speed = 0.1
		headClient.send_goal(headgoal,feedback)
		
		# FOR loop to constantly swap between joint positions for the handshake movement		
		for _move in range(4):
			# Position 1 of right hand for the handshake movement			
			goal.coordinates = [0.5,-0.4,0.4,1.55,-0.4,-1.25,-1.7]
			goal.precision = 0.1
			RHandClient.send_goal(goal, feedback)
			RHandClient.wait_for_result()		
			# Position 2 of right hand for the handshake movement
			goal.coordinates = [0.5, -0.4,0.4,1.35,-0.4,-0.65,-1.7]
			goal.precision = 0.1
			RHandClient.send_goal(goal, feedback)
			RHandClient.wait_for_result()

		LHandClient.wait_for_result()
		headClient.wait_for_result()		
	
	# (3) DAB MOVEMENT	
	if req.data == 3 :
		# Position of left hand for the dab movement		
		goal.coordinates = [1,-0.7,0,0,0,0,0]
		goal.precision = 0.1
		LHandClient.send_goal(goal, feedback)		
		# Position of left hand for the dab movement
		goal.coordinates = [1,0,2.2,1.5,0,0,0]
		goal.precision = 0.1
		RHandClient.send_goal(goal, feedback)
		# Position of head for the dab movement
		headgoal.angle = 0.8
		headgoal.speed = 0.1
		headClient.send_goal(headgoal,feedback)
		LHandClient.wait_for_result()
		RHandClient.wait_for_result()
		headClient.wait_for_result()
	
	# (4) HUG MOVEMENT
	if req.data == 4 :
		# Spread out the hands to get ready for hug, and keep the position for 10 seconds 
		# so that user can move close towards the front of baxter		
		goal.coordinates = [0,0,0,0,0,0,-0.448]
		goal.precision = 0.1
		LHandClient.send_goal(goal, feedback)		
		goal.coordinates = [0,0,0,0,0,0,-0.448]
		goal.precision = 0.1
		RHandClient.send_goal(goal, feedback)
		headgoal.angle = 0
		headgoal.speed = 0.1
		headClient.send_goal(headgoal,feedback)
		LHandClient.wait_for_result()
		RHandClient.wait_for_result()
		headClient.wait_for_result()
		rospy.sleep(10)

		# Position 1 of hug: wrap hands around the user for performing hug
		goal.coordinates = [-0.25,0.2,-1.6,0.55,0,0.7,-0.448]
		goal.precision = 0.1
		LHandClient.send_goal(goal, feedback)		
		goal.coordinates = [0.25,0.2,1.6,0.55,0,0.7,-0.276]
		goal.precision = 0.1
		RHandClient.send_goal(goal, feedback)
		headgoal.angle = 0
		headgoal.speed = 0.1
		headClient.send_goal(headgoal,feedback)
		LHandClient.wait_for_result()
		RHandClient.wait_for_result()
		headClient.wait_for_result()
		# Position 2 of hug: hug the user by bringing both hands close together 
		goal.coordinates = [-0.45,0.2,-1.6,0.35,0,1,-0.448]
		goal.precision = 0.1
		LHandClient.send_goal(goal, feedback)		
		goal.coordinates = [0.45,0.2,1.6,0.5,0,1.3,-0.276]
		goal.precision = 0.1
		RHandClient.send_goal(goal, feedback)
		headgoal.angle = 0
		headgoal.speed = 0.1
		headClient.send_goal(headgoal,feedback)
		LHandClient.wait_for_result()
		RHandClient.wait_for_result()
		headClient.wait_for_result()
		# Position 3 of hug: spread out the arms after finishing the hug
		goal.coordinates = [-0.2,0.2,-1.6,0.35,0,1,-0.448]
		goal.precision = 0.1
		LHandClient.send_goal(goal, feedback)		
		goal.coordinates = [0.2,0.2,1.6,0.5,0,1.3,-0.276]
		goal.precision = 0.1
		RHandClient.send_goal(goal, feedback)
		headgoal.angle = 0
		headgoal.speed = 0.1
		headClient.send_goal(headgoal,feedback)
		LHandClient.wait_for_result()
		RHandClient.wait_for_result()
		headClient.wait_for_result()
		# Position 4 of hug: Move the hands down so that the user can move out of the hug position
		goal.coordinates = [-0.2,1,-1.6,0.2,0,0.2,-0.448]
		goal.precision = 0.1
		LHandClient.send_goal(goal, feedback)		
		goal.coordinates = [0.2,1,1.6,0.2,0,0.2,-0.276]
		goal.precision = 0.1
		RHandClient.send_goal(goal, feedback)
		headgoal.angle = 0
		headgoal.speed = 0.1
		headClient.send_goal(headgoal,feedback)
		LHandClient.wait_for_result()
		RHandClient.wait_for_result()
		headClient.wait_for_result()
		
	# (5) EGYPTIAN DANCE
	if req.data == 5 :
		# Position the hands getting ready for the Egyptian Dance
		goal.coordinates = [-0.8,0,0,1.95,0,-1.75,0]
		goal.precision = 0.2
		RHandClient.send_goal(goal, feedback)		
		goal.coordinates = [0.8,0,3.2,1.95,0,-1.75,0]
		goal.precision = 0.2
		LHandClient.send_goal(goal, feedback)
		LHandClient.wait_for_result()
		RHandClient.wait_for_result()

		# FOR loop to constantly swap between joint positions for the Egyptian Dance
		for _move in range(5):
			# Position 1 for the Egyptian Dance
			goal.coordinates = [-0.8,0,0,1.1,0,-1.25,0]
			goal.precision = 0.25
			RHandClient.send_goal(goal, feedback)
			goal.coordinates = [0.8,0,3.2,1.1,0,-1.25,0]
			goal.precision = 0.25
			LHandClient.send_goal(goal, feedback)
			headgoal.angle = 0.8
			headgoal.speed = 0.2
			headClient.send_goal(headgoal,feedback)
			headClient.wait_for_result()
			RHandClient.wait_for_result()
			LHandClient.wait_for_result()
			# Position 2 for the Egyptian Dance
			goal.coordinates = [-0.8,0,0,1.95,0,-1.75,0]
			goal.precision = 0.25
			RHandClient.send_goal(goal, feedback)
			goal.coordinates = [0.8,0,3.2,1.95,0,-1.75,0]
			goal.precision = 0.25
			LHandClient.send_goal(goal, feedback)
			headgoal.angle = -0.8
			headgoal.speed = 0.2
			headClient.send_goal(headgoal,feedback)
			headClient.wait_for_result()
			RHandClient.wait_for_result()	
			LHandClient.wait_for_result()
		
		LHandClient.wait_for_result()
		RHandClient.wait_for_result()
		headClient.wait_for_result()

	# do your motion planning here
	if (1==1): # You should decide when the robot has finished moving.
		print "Hey, the motion planning was done correctly"
		res.success = True
		res.message = "Baxter has completed an action"
	else:
		print "How come??"
		res.success = False
		res.message = "Baxter did not complete an action"
			
	return res


	
res = BaxterMotionResponse()
rospy.init_node('baxter_motion_server')
LHandClient = actionlib.SimpleActionClient ('/Lhand_server', BaxterActionAction)
RHandClient = actionlib.SimpleActionClient ('/Rhand_server', BaxterActionAction)
headClient = actionlib.SimpleActionClient ('/Head_server', BaxterHeadAction)
motion_srv = rospy.Service('baxtermotion_server', BaxterMotion, handle_motion_request)
LHandClient.wait_for_server()
RHandClient.wait_for_server()
headClient.wait_for_server()

print "movement server ready and spinning."
rospy.spin()

