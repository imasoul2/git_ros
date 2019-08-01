/* Copyright 2012 Pouyan Ziafati, University of Luxembourg and Utrecht University

* actionlib client example for the face_recognition simple actionlib server. The client subscribes to face_recognition::FRClientGoal messages. Each FRClientGoal message contains an order_id and an order_argument which specify a goal to be executed by the face_recognition server. After receiving a message, the client sends the corresponding goal to the server. By registering relevant call back functions, the client receives feedback and result information from the execution of goals in the server and prints such information on the terminal.

*Provided by modifying the ROS wiki tutorial: "actionlib_tutorials/Tutorials/Writing a Callback Based Simple Action Client (last edited 2010-09-13 17:32:34 by VijayPradeep)"

*License: Creative Commons Attribution 3.0.
*/

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <face_recognition/FRClientGoal.h>
#include <face_recognition/FaceRecognitionAction.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>

#include "baxter_movement/BaxterMotion.h"

#include "std_srvs/Trigger.h"
#include "std_msgs/Empty.h"
#include "std_msgs/Int64.h"


using namespace std;
face_recognition::FaceRecognitionGoal goal; //Goal message
actionlib::SimpleActionClient<face_recognition::FaceRecognitionAction> * ac; //action lib client

int doneFlag; // This is a global flag to set if the goal has been accomplished in the Service
string temp;
int trainFlag ;
int detectFlag;

// Called once when the goal completes
void doneCb(const actionlib::SimpleClientGoalState& state,
            const face_recognition::FaceRecognitionResultConstPtr& result)
{
//  ROS_INFO("Goal [%i] Finished in state [%s]", result->order_id,state.toString().c_str());


  if(state.toString() != "SUCCEEDED") return;

  if (result-> order_id ==3)
  {
    ROS_INFO("Done updating the database !");
    doneFlag = 1;
  }
  if( result->order_id==0)
  {
    ROS_INFO("%s was recognized with confidence(accuracy) %f", result->names[0].c_str(),result->confidence[0]);
    detectFlag = 1;
  }
  if( result->order_id==2)
  {
    ROS_INFO("Pictures of %s were successfully added to the training images",result->names[0].c_str());
   // Goal achieved.

   // set the flag as the training has been finished,
   // now the database has to be updated.
   trainFlag = 1;
  }
}

// Called once when the goal becomes active
void activeCb()
{
   ROS_INFO("Goal just went active");
}

// Called every time feedback is received for the goals
void feedbackCb(const face_recognition::FaceRecognitionFeedbackConstPtr& feedback)
{
  // ROS_INFO("Received feedback from Goal [%d] ", feedback->order_id);
  if(feedback->order_id==1 )
  {
//    ROS_INFO("%s was recognized with confidence %f", feedback->names[0].c_str(),feedback->confidence[0]);
    temp = feedback->names[0].c_str();
  }
  if( feedback->order_id==2)
  {}
  //  ROS_INFO("A picture of %s was successfully added to the training images",feedback->names[0].c_str());
}


//shut down
void exit_handler(int s)
{
  delete(ac);
  ros::shutdown();
}


int main (int argc, char **argv)
{
  ros::init(argc, argv, "face_recognition_client");
  ros::NodeHandle n;
  doneFlag = 0;
  ros::Time start_time ;
  std_msgs::Int64 gui_msg;

  // Add functinality to delete a file facedata.xml to update.

  ac = new actionlib::SimpleActionClient<face_recognition::FaceRecognitionAction>("face_recognition", true);
  goal.order_id = 3;
  goal.order_argument = "none";
  ac->sendGoal(goal, &doneCb, &activeCb, &feedbackCb);

  ros::ServiceClient motionclient = n.serviceClient<baxter_movement::BaxterMotion>("baxtermotion_server");
  ros::Publisher gui_pub = n.advertise<std_msgs::Int64>("/gui_select",1);



  baxter_movement::BaxterMotion srv;
  srv.request.data = 0;





  //for proper shutdown exit_handler is used
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = exit_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);

  //wait for the server
  ac->waitForServer();
  //subscribe to the topic of interest
  ROS_INFO("Action client is running now");
  int choice ;



  gui_msg.data = 0;
  gui_pub.publish(gui_msg);

while(ros::ok())
  {

    // Show the default gui on the head screen.
    if (doneFlag ==1)
    {
    gui_msg.data = 0;
    gui_pub.publish(gui_msg);
  }



 // resetting the flags
 // When the doneFlag is set, this will trigger the menu go back to the Default
    doneFlag = 0;
 // Trainflag is needed, so that when the program is done training,
 // the program knows it has to update the database for the facial recognition module.
    trainFlag = 0;


  // Default to "ironman position" to move the left arm to face the person in front.
   srv.request.data = 0;
   motionclient.call(srv);




  // This is the default menu.
  cout << "Choose which functionality you want"<<endl;
  cout << "0. Detect once" << endl;
  cout << "2. Train your face "<<endl;
  cout << "4. End the program"<<endl;
  cin >> choice;

  // Error handling,  Catching false input
    if(cin.fail())
    {
      cin.clear(); // clears error flags
      cin.ignore();
      choice = 5;
    }
    else{  cout << " Your choice : " << choice << endl;}


  // If the user wants to train the face
 if (choice ==2)
  {
    // Set the right gui for the head screen
    gui_msg.data = 2;
    gui_pub.publish(gui_msg);

    cout << "Please type in your name"<<endl;
    cin >> goal.order_argument;


    goal.order_id = choice;
    ac->sendGoal(goal, &doneCb, &activeCb, &feedbackCb);

    // Set the gui again to indicate that the robot is learning your face.
    gui_msg.data = 3;
    gui_pub.publish(gui_msg);

  }
  else if(choice ==0)
    {

      gui_msg.data = 7;
      gui_pub.publish(gui_msg);
      // Start recording time so that it can calculate
      // how many seconds have passsed since the user chose "detect once" menu
       start_time = ros::Time::now();

      // resetting the variables
      goal.order_id = choice;
      goal.order_argument = "none";
      ac->sendGoal(goal, &doneCb, &activeCb, &feedbackCb);



    }
    else if(choice ==4)
    {
      gui_msg.data = 6;
      gui_pub.publish(gui_msg);
      // This will shutdown everything.
      cout<<"Shutting down face recognition module"<<endl;
      // change gui

      goal.order_id = choice;
      goal.order_argument = "none";
      ac->sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
    }
  else{
    // Error handling for false user input
    ROS_INFO("Please check your input again, you only have options 0,2,4");
    doneFlag = 1;
  }

  while(doneFlag==0)
  {
    // This duration records how many seconds have passed since the user selected
    // "Detect Once" menu
    ros::Duration delta_t = ros::Time::now() - start_time;
    double delta_t_sec = delta_t.toSec();





 // If someone has not been detected for longer than 10 secs
    if (delta_t_sec > 10 && choice == 0)
    {
     // In case, no one is detected.
      gui_msg.data = 5;
      gui_pub.publish(gui_msg);

      cout <<"Going back to the menu automatically" << endl;
      cout << "Cancelling the action server" << endl;
      // go back to the menu and pre-empt the goal.
      ac->cancelGoal();
      doneFlag = 1;
    }

    if (trainFlag == 1)
    {
      // If it is done training, then update the database
      // facial recognition module has to be updated after training.


      gui_msg.data = 3;
      gui_pub.publish(gui_msg);
      goal.order_id = 3;
      goal.order_argument = "none";
      ac->sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
      trainFlag = 0;
    }

    while (detectFlag == 1)
    {
        gui_msg.data = 1;
        gui_pub.publish(gui_msg);

     // For future possible extension
     // It should decide if the person recognized has already chosen the action BEFORE

     // if it has, then send the corresponding action to the serviceClient
     // OR ...


     // if it has not then ask for action
      cout << "Choose how you want to interact with Baxter"<<endl;
      cout << "1. Hello" << endl;
      cout << "2. Handshake"<<endl;
      cout << "3. Dab "<<endl;
      cout << "4. Slow Hug"<<endl;
      cout << "5. Egyptian Dance"<<endl;

      cin >> srv.request.data; // push the user input to service



      // Indicating that it is moving
      gui_msg.data = 4;
      gui_pub.publish(gui_msg);


      motionclient.call(srv);  // calling the service for motion

      detectFlag = 0;
      doneFlag = 1;

    }



      ros::spinOnce(); // do all callbacks in the queue

  }

}


  ros::spin();
  return 0;
}
