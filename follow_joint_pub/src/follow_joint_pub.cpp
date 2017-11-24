#include <actionlib/client/simple_action_client.h>
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <control_msgs/FollowJointTrajectoryActionGoal.h>
#include <control_msgs/FollowJointTrajectoryGoal.h>
#include <control_msgs/FollowJointTrajectoryFeedback.h>
#include <control_msgs/FollowJointTrajectoryResult.h>
#include <ros/ros.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>
#include <Eigen/Geometry>

//#include <trajectory_msgs/JointTrajectory.h>
//#include <trajectory_msgs/JointTrajectoryPoint.h>

typedef actionlib::SimpleActionClient<control_msgs::FollowJointTrajectoryAction> Client;



// 当action完成后会调用次回调函数一次
void doneCB(const actionlib::SimpleClientGoalState& state, const control_msgs::FollowJointTrajectoryResultConstPtr& result)
{
    ROS_INFO("Done");
  //  ros::shutdown();
}

// 当action激活后会调用次回调函数一次
void activeCB()
{
    ROS_INFO("Goal just went active");
}

// 收到feedback后调用的回调函数
void feedbackCB(const control_msgs::FollowJointTrajectoryFeedbackConstPtr& feedback)
{
    ROS_INFO("percent_complete:");
}



  int main(int argc, char *argv[])
 {
     ros::init(argc, argv, "follow_joint_pub");
//moveit部分接口
    //  robot_model_loader::RobotModelLoader robot_model_loader( "robot_description");
    //  robot_model::RobotModelPtr kinematic_model = robot_model_loader.getModel();
    //  ROS_INFO("Model frame: %s", kinematic_model->getModelFrame().c_str());
    //  robot_state::RobotStatePtr kinematic_state( new robot_state::RobotState(kinematic_model));
    //  kinematic_state->setToDefaultValues();
    //  const robot_state::JointModelGroup *joint_model_group = kinematic_model->getJointModelGroup("jakaUr");

    //  const std::vector<std::string> &joint_names = joint_model_group->getVariableNames();
    //  std::vector<double> joint_values;
    //  kinematic_state->copyJointGroupPositions(joint_model_group, joint_values);
    //  for (std::size_t i = 0; i < joint_names.size(); ++i) 
    //  {
    //    ROS_INFO("Joint %s: %f", joint_names[i].c_str(), joint_values[i]);
    //  }


// ros::NodeHandle n;
// ros::Subscriber joint_states_sub=n.subscribe("jakaUr/joint_states", joint_states_subCB);

double step=0.01;
     //定义一个客户端,第一个参数是action名称，第二个参数true不用ros::spin()
     Client client("jakaUr/jaka_joint_controller/follow_joint_trajectory",true);
     //等待服务器端
     ROS_INFO("Waiting for action server to start.");
     client.waitForServer();
     ROS_INFO("Action server started, sending goal.");

     //创建action的goal
     control_msgs::FollowJointTrajectoryGoal goal;
     goal.trajectory.header.stamp=ros::Time::now();
     goal.trajectory.joint_names.resize(6);
     goal.trajectory.points.resize(3);
     goal.trajectory.points[0].positions.resize(6);
     goal.trajectory.points[1].positions.resize(6);
     goal.trajectory.points[2].positions.resize(6);
     goal.trajectory.header.frame_id = "/world";
 //    ros::Rate loop_rate(20);
  //  while(ros::ok())
    {

//ros::Rate r(20);
// ros::Duration first_points(0,120000000);
// ros::Duration second_points(0, 620000000);
// ros::Duration third_points(1, 120000000);
      goal.trajectory.joint_names[0] = "joint_1";
      goal.trajectory.joint_names[1] = "joint_2";
      goal.trajectory.joint_names[2] = "joint_3";
      goal.trajectory.joint_names[3] = "joint_4";
      goal.trajectory.joint_names[4] = "joint_5";
      goal.trajectory.joint_names[5] = "joint_6";
      goal.trajectory.points[0].positions[0] = -0.238952;
      goal.trajectory.points[0].positions[1] =  0.49258470;
      goal.trajectory.points[0].positions[2] = -0.9567198;
      goal.trajectory.points[0].positions[3] =  0.464155;
      goal.trajectory.points[0].positions[4] = -0.2389186;
      goal.trajectory.points[0].positions[5] = 3.806e-05;
      goal.trajectory.points[0].time_from_start = ros::Duration(0, 100000000);

      goal.trajectory.points[1].positions[0] = -0.238952;
      goal.trajectory.points[1].positions[1] = 0.8;
      goal.trajectory.points[1].positions[2] = -0.9567198;
      goal.trajectory.points[1].positions[3] = 0.464155;
      goal.trajectory.points[1].positions[4] = -0.2389186;
      goal.trajectory.points[1].positions[5] = 3.806e-05;
   
      goal.trajectory.points[1].time_from_start =ros::Duration(0, 500000000);
      

      goal.trajectory.points[2].positions[0] = -0.238952;
      goal.trajectory.points[2].positions[1] = 1.1;
      goal.trajectory.points[2].positions[2] = -0.9567198;
      goal.trajectory.points[2].positions[3] = 0.464155;
      goal.trajectory.points[2].positions[4] = -0.2389186;
      goal.trajectory.points[2].positions[5] = 3.806e-05;

      goal.trajectory.points[2].time_from_start = ros::Duration(0, 800000000);
      
      client.sendGoal(goal, &doneCB, &activeCB, &feedbackCB);
    //  r.sleep();
      ros::spinOnce();
  //    loop_rate.sleep();
    } 
     

      return 0;
 }