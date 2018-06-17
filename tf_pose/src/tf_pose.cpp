#include "ros/ros.h"
#include "tf/transform_listener.h"
#include "sensor_msgs/JointState.h"
#include "geometry_msgs/Pose.h"
#include "tf/transform_broadcaster.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "tf_pose");
    ros::NodeHandle nh;
    ros::Rate rate(1000);
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(0.5, 0.0, 0.1));
    tf::Quaternion q;
    q.setRPY(0,30,45);
    transform.setRotation(q);
    double X=q.getX();
    double Y=q.getY();
    double Z=q.getZ();
    double W=q.getW();
   // ros::Rate rate(100);
   for(int i=0;i<100;i++)
    {
      ROS_INFO("x%f y%f z%f w%f",X,Y,Z,W);
      rate.sleep();
    }
    
    //   tf::TransformListener listener;
    // listener.waitForTransform("/world", "link_6", ros::Time(), ros::Duration(1.0));
    //   while(nh.ok())
    // {
    //   try
    //   {
    //     tf::StampedTransform echo_transform;
    //     listener.lookupTransform("/world", "link_6", ros::Time(), echo_transform);
    //     std::cout.precision(3);
    //     std::cout.setf(std::ios::fixed,std::ios::floatfield);
    //     std::cout << "At time " << echo_transform.stamp_.toSec() << std::endl;
    //     double yaw, pitch, roll;
    //     echo_transform.getBasis().getRPY(roll, pitch, yaw);
    //     tf::Quaternion q = echo_transform.getRotation();
    //     tf::Vector3 v = echo_transform.getOrigin();
    //     std::cout << "- Translation: [" << v.getX() << ", " << v.getY() << ", " << v.getZ() << "]" << std::endl;
    //     std::cout << "- Rotation: in Quaternion [" << q.getX() << ", " << q.getY() << ", " 
    //               << q.getZ() << ", " << q.getW() << "]" << std::endl
    //               << "            in RPY (radian) [" <<  roll << ", " << pitch << ", " << yaw << "]" << std::endl
    //               << "            in RPY (degree) [" <<  roll*180.0/M_PI << ", " << pitch*180.0/M_PI << ", " << yaw*180.0/M_PI << "]" << std::endl;

    //     //print transform
    //   }
    //   catch(tf::TransformException& ex)
    //   {
    //     std::cout << "Failure at "<< ros::Time::now() << std::endl;
    //     std::cout << "Exception thrown:" << ex.what()<< std::endl;
    //     std::cout << "The current list of frames is:" <<std::endl;
    //     std::cout << listener.allFramesAsString()<<std::endl;
        
    //   }
    //   rate.sleep();
    // }

  return 0;
}