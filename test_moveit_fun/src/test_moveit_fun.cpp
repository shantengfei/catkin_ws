
#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <control_msgs/FollowJointTrajectoryActionGoal.h>
#include <control_msgs/FollowJointTrajectoryGoal.h>
#include <control_msgs/FollowJointTrajectoryFeedback.h>
#include <control_msgs/FollowJointTrajectoryResult.h>
#include <sensor_msgs/JointState.h>
#include <Eigen/Geometry>
// MoveIt!
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit/move_group_interface/move_group.h>

#include <moveit/robot_state/robot_state.h>

typedef actionlib::SimpleActionClient<control_msgs::FollowJointTrajectoryAction>
    Client;
    //获取当前关节角度值
double CurrentJointState[6] {};

// 当action完成后会调用次回调函数一次
void doneCB(const actionlib::SimpleClientGoalState &state,
            const control_msgs::FollowJointTrajectoryResultConstPtr &result) {
  ROS_INFO("Done");
  //  ros::shutdown();
}

// 当action激活后会调用次回调函数一次
void activeCB() { ROS_INFO("Goal just went active"); }

// 收到feedback后调用的回调函数
void feedbackCB(
const control_msgs::FollowJointTrajectoryFeedbackConstPtr &feedback) {
  ROS_INFO("percent_complete:");
}
//订阅joint states话题获得当前机器人的关节角度
void listenerCB(const sensor_msgs::JointState &msg)
{
  for(int i=0;i<msg.position.size();i++)
{
  CurrentJointState[i] = msg.position[i];
  ROS_INFO("current joint_state of joint[%d] is %f\n",i+1,CurrentJointState[i]);
}
}

int main(int argc, char **argv) {
  // init初始化必须在开始，否则会出现Couldn’t find an AF_INET address的错误
  ros::init(argc, argv, "right_arm_kinematics");
  //设置参数，从参数服务器上获得相关的sim参数，假如sim为true那就是带着gazebo，需要发布的话题是jakaUr/jaka_joint_controller/follow_joint_trajectory
  //否则sim为false时，发布的话题是joint_trajectory_action，这是因为action是堵塞机制，不能同时将两个不是同时运行的action放在一起
  std::string actionName = "";
  std::string topicName = "";
  bool sim = true;
  ros::param::get("sim", sim);
  ROS_INFO("the sim is %d", sim);
  if (sim == true) {
    actionName = "jakaUr/jaka_joint_controller/follow_joint_trajectory";
    topicName = "jakaUr/joint_states";
  } 
  else {
    actionName = "joint_trajectory_action";
    topicName = "joint_states";
  }

  double step = 0.01;
  //定义一个客户端,第一个参数是action名称，第二个参数true不用ros::spin()
 
 
  ros::NodeHandle nh;

  ros::AsyncSpinner spinner(1);
  spinner.start();

  Client client(actionName, true);

  ros::Subscriber sub = nh.subscribe(topicName, 1000, listenerCB);

  //等待服务器端
  ROS_INFO("Waiting for action server to start.");
  client.waitForServer();
 // client_without_ga.waitForServer();
   ROS_INFO("Action server started, sending goal.");

  //创建action的goal
  control_msgs::FollowJointTrajectoryGoal goal;
  goal.trajectory.header.stamp = ros::Time::now();
  goal.trajectory.joint_names.resize(6);
  goal.trajectory.points.resize(3);
  goal.trajectory.points[0].positions.resize(6);
  goal.trajectory.points[1].positions.resize(6);
  goal.trajectory.points[2].positions.resize(6);
  goal.trajectory.header.frame_id = "/world";

  {
    goal.trajectory.joint_names[0] = "joint_1";
    goal.trajectory.joint_names[1] = "joint_2";
    goal.trajectory.joint_names[2] = "joint_3";
    goal.trajectory.joint_names[3] = "joint_4";
    goal.trajectory.joint_names[4] = "joint_5";
    goal.trajectory.joint_names[5] = "joint_6";
    //给定当前关节角度值
    for(int k=0;k<goal.trajectory.points.size();k++)
    {
      for (int j = 0; j < goal.trajectory.points[0].positions.size(); j++) {
        goal.trajectory.points[k].positions[j] = CurrentJointState[j]+k*0.2;
      }
      goal.trajectory.points[k].time_from_start = ros::Duration(0, (k+1)*100000000);
    }
   
    // goal.trajectory.points[0].positions[0] = -0.238952;
    // goal.trajectory.points[0].positions[1] = 0.49258470;
    // goal.trajectory.points[0].positions[2] = -0.9567198;
    // goal.trajectory.points[0].positions[3] = 0.464155;
    // goal.trajectory.points[0].positions[4] = -0.2389186;
    // goal.trajectory.points[0].positions[5] = 3.806e-05;
    // goal.trajectory.points[0].time_from_start = ros::Duration(0, 100000000);

  //   goal.trajectory.points[1].positions[0] = -0.238952;
  //   goal.trajectory.points[1].positions[1] = 0.8;
  //   goal.trajectory.points[1].positions[2] = -0.9567198;
  //   goal.trajectory.points[1].positions[3] = 0.464155;
  //   goal.trajectory.points[1].positions[4] = -0.2389186;
  //   goal.trajectory.points[1].positions[5] = 3.806e-05;

  //   goal.trajectory.points[1].time_from_start = ros::Duration(0, 500000000);

  //   goal.trajectory.points[2].positions[0] = -0.238952;
  //   goal.trajectory.points[2].positions[1] = 1.1;
  //   goal.trajectory.points[2].positions[2] = -0.9567198;
  //   goal.trajectory.points[2].positions[3] = 0.464155;
  //   goal.trajectory.points[2].positions[4] = -0.2389186;
  //   goal.trajectory.points[2].positions[5] = 3.806e-05;

  //  goal.trajectory.points[2].time_from_start = ros::Duration(0, 800000000);

    client.sendGoal(goal, &doneCB, &activeCB, &feedbackCB);
   // client_without_ga.sendGoal(goal, &doneCB, &activeCB, &feedbackCB);
 //   ros::spinOnce();

  }

  // moveit::planning_interface::MoveGroup group("jakaUr");
  // group.setNamedTarget("home");
  // group.move();

//   std::vector<double> group_variable_values;
//   group.getCurrentState()->copyJointGroupPositions(group.getCurrentState()->getRobotModel()->getJointModelGroup(group.getName()),group_variable_values);
//   for(auto value:group_variable_values)
//     std::cout<<value<<std::endl;
//   robot_model_loader::RobotModelLoader robot_model_loader("robot_description");
//   robot_model::RobotModelPtr kinematic_model = robot_model_loader.getModel();
//   ROS_INFO("Model frame: %s", kinematic_model->getModelFrame().c_str());

//   robot_state::RobotStatePtr kinematic_state(
//       new robot_state::RobotState(kinematic_model));
//   kinematic_state->setToDefaultValues();
//   const robot_state::JointModelGroup *joint_model_group =
//       kinematic_model->getJointModelGroup("jakaUr");

//   const std::vector<std::string> &joint_names =
//       joint_model_group->getVariableNames();

//   std::vector<double> joint_values;
//   kinematic_state->copyJointGroupPositions(joint_model_group, joint_values);
//   for (std::size_t i = 0; i < joint_names.size(); ++i) {
//     ROS_INFO("Joint %s: %f", joint_names[i].c_str(), joint_values[i]);
//   }
  ros::shutdown();
  return 0;
}