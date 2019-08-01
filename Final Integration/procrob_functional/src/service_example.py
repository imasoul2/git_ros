#!/usr/bin/env python

import rospy
import sys
from std_srvs.srv import *
from face_recognition.srv import *


#include "face_recognition/BaxterMotion.h"

# Setting the response for service
res = BaxterMotionResponse()

def handle_motion_request(req):
    # finish the motion
    # if it was successfully done

    # do your motion planning here
    if (1==1): # You should decide when the robot has finished moving.
        print "Hey, the motion planning was done correctly"
        res.success = True
        res.message = "Baxter has completed an action"
    else:
        res.success = False
        res.message = "Baxter did not complete an action"

    return res

# this is the main server.
def motion_server():
    rospy.init_node('baxter_motion_server')
    motion_srv = rospy.Service('baxtermotion_server', BaxterMotion, handle_motion_request)
    print "Ready to spin the server."
    rospy.spin()

if __name__ == "__main__":
    motion_server()
