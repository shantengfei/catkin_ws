#include "ros/ros.h"
#include"std_msgs/String.h"
#include "trajectory_msgs/JointTrajectory.h"
#include "trajectory_msgs/JointTrajectoryPoint.h"
#include <sstream>
#include <vector>
void chatterCB(const trajectory_msgs::JointTrajectory& msg)
{
     double time_nsecs=0.0;
     int points_count=0;
     double joint_positions[6] {0.0};
    ROS_INFO("get the joint_path_command ");
 
   
    std::basic_string<char> jointname=msg.joint_names[0] ;
    points_count= msg.points.size();
    for (size_t i = 0; i < points_count; i++)
    {
       for (size_t j = 0; j < 6; j++)
    {
        joint_positions[j]=msg.points[i].positions[j];
        
    }
    ROS_INFO("points_counts is [%d]",points_count);
    ROS_INFO("the [%d] positions are[%f],[%f],[%f],[%f],[%f],[%f]\n",i,joint_positions[0],joint_positions[1],joint_positions[2],joint_positions[3],joint_positions[4],joint_positions[5]);
    }
    
    
    // std::vector<trajectory_msgs::JointTrajectoryPoint>::iterator it;
    // for( it = msg.points.begin(); it!=msg.points.end();++it)
    // {
    //    for (size_t j = 0; j < 6; j++)
    // {
    //     joint_positions[j]=it->positions[j];
    //     ROS_INFO("[%f]",joint_positions[j]);
        
    // } 
    // } 
  // double positions[6]=msg.points[0].positions;
   // ROS_INFO("[%s]",jointname.c_str());
    //    i=sizeof(msg.points[0]);
  //  ROS_INFO("[%d][%d]",points_count,i);
  
}
 int main(int argc, char *argv[])
{
    /* code for main function */
    ros::init(argc, argv, "joint_path_command_subscriber");
    ros::NodeHandle n;
    ros::Subscriber sub=n.subscribe("joint_path_command",10,chatterCB);
    ros::spin();
    return 0;
}