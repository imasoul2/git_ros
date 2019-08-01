#! /usr/bin/env python

import sys, time
import roslib
import rospy
import os
import sys
import argparse
import cv2
from cv_bridge import CvBridge
import numpy as np
from std_msgs.msg import Int64
from sensor_msgs.msg import (
Image,
)

class screen_test:

    def __init__(self):
        #self.image = None
        self.bridge = CvBridge()
        self.loop_rate = rospy.Rate(100)
        self.image_pub = rospy.Publisher('/robot/xdisplay',Image, latch = True)
        self.image_sub = rospy.Subscriber('/cameras/left_hand_camera/image', Image, self.callback, queue_size = 1)
        self.gui_sub = rospy.Subscriber('/gui_select', Int64, self.gui_callback, queue_size = 1)
        self.gui_select = 10

    def gui_callback(self, data):
        self.gui_select = data.data

    def callback(self, msg):
        #self.image_pub.publish(msg)

        cv_image = self.bridge.imgmsg_to_cv2(msg,desired_encoding = "bgr8")

	#print('Original Dimensions : ', cv_image.shape)
	 
	scale_percent = 150 # percent of original size
	width = int(cv_image.shape[1] * scale_percent / 100)
	height = int(cv_image.shape[0] * scale_percent / 100)
	dim = (width, height)
	# resize image
	resized = cv2.resize(cv_image, dim, interpolation = cv2.INTER_AREA) 
	#print('Resized Dimensions : ',resized.shape) 

        font = cv2.FONT_HERSHEY_SIMPLEX
        y0, dy = 20,30
        fontScale = 0.8
        fontColor = (255,255,255)
        lineType = 2

	#('Original Dimensions : ', (800, 1280, 3))


        menu_options= {
            0: "0. Start facial recognition \n2. Train new face\n4. Exit",
            1: "Hey you ! \n How would you like to greet me today?:\n1. Hello\n2. Handshake\n3. Dab\n4. Hug\n5. Egyption Dance",
            2: "Please type in your name",
            3: "Training in Progress, \n it will go back to menu once it's done",
            4: " Baxter in action    'boop boop -- boop'  ",
            5: " Ey, I coudln't recognize you,\n please run training first!",
            6: " Shutdown trigger, Baxter is in a sleep  ':|' ",
            7: " Detecting famililar faces......",
            10: "Loading up the program ......"

        }

        text = menu_options[self.gui_select]

        for i, line in enumerate(text.split('\n')):
            y = y0+i*dy
            cv2.putText(resized, line,
            (20,y),
            font,
            fontScale,
            fontColor,
            lineType)

        self.image_pub.publish(self.bridge.cv2_to_imgmsg(resized,'bgr8'))
        cv2.imshow("Image Window", resized)
        cv2.waitKey(3)

    def start(self):
        print "Starting..."

        while not rospy.is_shutdown():
            self.loop_rate.sleep()

def main(args):

    rospy.init_node('screen_test', anonymous = True)
    ic = screen_test()
    ic.start()

    try:
        rospy.spin()
    except KeyboardInterrupt:
        print "Shutting down..."
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main(sys.argv)
