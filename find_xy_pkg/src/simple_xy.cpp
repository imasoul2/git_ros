#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <nav_msgs/Odometry.h>



// variables definition


class SubandPub
{
public:


    // public functions
                // public variables
        double yaw, angularv, linearv ;
        double x,y;
        double vx,vy;
        double diff_x, diff_y;
        double temp;

        ros::Time current_time;
        ros::Time previous_time;

        nav_msgs::Odometry data;

    // Constructor
    SubandPub()
    {
        sub = nh.subscribe("/odom", 1000, &SubandPub::odomCallback,this);
        pub =  nh.advertise<nav_msgs::Odometry>("/result", 1000);


            // public variables
        angularv, linearv, vx, vy, temp= 0;
         x = 1.1641;
         y = 1.2894;
         yaw = 0.6959;

      // Setting the time variables
      current_time = ros::Time::now();
      previous_time = ros::Time::now();



    }



    void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
    {



 	// Setting the current time as now
      current_time = ros::Time::now();
       // Gettting linear x and angular z from odom/Twist and set them into variables

      angularv = msg->twist.twist.angular.z ;

        // Eliminating the outliers
      if (angularv > 10)
      {
        angularv = temp ;
      }
      else
      {
        temp = msg->twist.twist.angular.z;
      }

      linearv = msg->twist.twist.linear.x;




       // setting dt
      double dt =(current_time-previous_time).toSec();

      double dyaw = angularv*dt;
      yaw=yaw+dyaw;


     // calculating each part
      vx = linearv*cos(yaw);
      vy = linearv*sin(yaw);

      double dx = vx*dt;
      double dy = vy*dt;


   //  Final values for x and y

      x +=dx;
      y +=dy;

// Comparing two diff values from odom topic and our algorithm

      std::cout<<"x and y from /prom: "<< x <<" , "<< y << std::endl;
      std::cout<<"x and y from /odom: " << msg->pose.pose.position.x <<" , " <<msg->pose.pose.position.y << std::endl;


      data.pose.pose.position.x = x;
      data.pose.pose.position.y = y;


      pub.publish(data);
      previous_time = current_time;




    }



private:
     ros::NodeHandle nh;
    ros::Subscriber sub;
    ros::Publisher pub;



};



int main(int argc, char** argv) {

    ros::init(argc, argv, "simple_xy");

    std::cout << " Start of the program : \n   " << std::endl;


       SubandPub OdomObj;

      ros::spin();

    return 0;

}
