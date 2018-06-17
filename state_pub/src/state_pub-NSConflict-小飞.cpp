#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/JointState.h"
#include <sstream>
 int main(int argc, char *argv[]) {
  ros::init(argc, argv, "state_pub");
  ros::NodeHandle n;
  ros::Publisher joint_state_pub =
      n.advertise<sensor_msgs::JointState>("/move_group/fake_controller_joint_states",1000);
      ros::Rate loop_rate(20);
     int count=0; 
     double step=0.01;
  
      while (ros::ok())
      {
        sensor_msgs::JointState msg;
       
          msg.name.resize(6);
          msg.position.resize(6);
          msg.header.stamp=ros::Time::now();
          msg.name[0] = "joint_1";
          msg.name[1] = "joint_2";
          msg.name[2] = "joint_3";
          msg.name[3] = "joint_4";
          msg.name[4] = "joint_5";
          msg.name[5] = "joint_6";
          msg.position[0] = -0.1916387038602662;
          msg.position[0] += step;
          msg.position[1] = 0.42403665542350666 ;
          msg.position[2] = -0.8567465700119383 ;
          msg.position[3] = 0.4327368637085671 ;
          msg.position[4] = -0.19177378731986927 ;
          msg.position[5] = 4.100404025919602e-05 ;
          ROS_INFO ("send %f",msg.position[0] );
          joint_state_pub.publish(msg);
          ros::spinOnce();
          loop_rate.sleep();
        
          ++count;
          step+=0.01;
      }


      return 0;
}
