#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

int main(int argc, char **argv) 
{
  ros::init(argc, argv, "move_group_interface_tutorial");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();
  /* 设置休眠时间是rviz启动 */
 // sleep(5.0);
  static const std::string PLANNING_GROUP = "jakaUr";
  //movegroup这个类是给indigo用的，movegroupinterface是给kinetic用的
  moveit::planning_interface::MoveGroup group(PLANNING_GROUP);
  //添，减碰撞物体
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
  //可视化运动规划的部分，可视化与该话题有关
  ros::Publisher display_publisher =node_handle.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path", 1, true);
  moveit_msgs::DisplayTrajectory display_trajectory;
  ROS_INFO("Reference frame: %s", group.getPlanningFrame().c_str());
  ROS_INFO("Reference frame: %s", group.getEndEffectorLink().c_str());
   geometry_msgs::Pose target_pose1;
   //获取一个随机点
   geometry_msgs::PoseStamped pose = group.getRandomPose();
   pose.header.stamp = ros::Time::now();
   target_pose1.orientation.w = pose.pose.orientation.w;
   //target_pose1.orientation.x = pose.pose.orientation.x;
  // target_pose1.orientation.y = pose.pose.orientation.y;
  // target_pose1.orientation.z = pose.pose.orientation.z;
   target_pose1.position.x = pose.pose.position.x;
   target_pose1.position.y = pose.pose.position.y;
   target_pose1.position.z = pose.pose.position.z;
ROS_INFO("target_pose1.orientation w %f,x%f,y%f,z%f",target_pose1.orientation.w,target_pose1.orientation.x,target_pose1.orientation.y,target_pose1.orientation.z);
  group.setPoseTarget(target_pose1);
 // group.setNamedTarget("home");
  //group.move();
//  group.setRandomTarget();
 moveit::planning_interface::MoveGroup::Plan my_plan;
 //group.setPlanningTime(10);
 //plan会自动执行规划可视化
 bool success = group.plan(my_plan);
 
 ROS_INFO("Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");
  /* Sleep to give Rviz time to visualize the plan. */
 sleep(5.0);

 //将规划好的点存到trajectroy中，然后发布出去，发布到的话题是/move_group/display_planned_path
 //这里的数据应该和执行的joint——path——command相同

  if (1) {
    ROS_INFO("Visualizing plan 1 (again)");
    display_trajectory.trajectory_start = my_plan.start_state_;
    display_trajectory.trajectory.push_back(my_plan.trajectory_);           //注意这里的trajectory的压栈操作
    display_publisher.publish(display_trajectory);
    group.move();
    /* Sleep to give Rviz time to visualize the plan. */
    sleep(5.0);
  }
  //获取当前的关节角度
  std::vector<double> group_variable_values;
  group.getCurrentState()->copyJointGroupPositions(group.getCurrentState()->getRobotModel()->getJointModelGroup(group.getName()),group_variable_values);
  for (int i = 0; i <6; i++)
  {
    ROS_INFO("joint_%d=%f", i, group_variable_values[i]);
  }
//设置新的角度
  group_variable_values[0] = -1.0;  
  group.setJointValueTarget(group_variable_values);               //关节空间规划
  success = group.plan(my_plan);                                  //plan并且会有可视化
  ROS_INFO("Visualizing plan 2 (joint space goal) %s",success?"":"FAILED");
  /* Sleep to give Rviz time to visualize the plan. */
  sleep(5.0);

//  // Planning with Path Constraints
//   moveit_msgs::OrientationConstraint ocm;  
//   ocm.link_name = "r_wrist_roll_link";  
//   ocm.header.frame_id = "base_link";
//   ocm.orientation.w = 1.0;
//   ocm.absolute_x_axis_tolerance = 0.1;
//   ocm.absolute_y_axis_tolerance = 0.1;
//   ocm.absolute_z_axis_tolerance = 0.1;
//   ocm.weight = 1.0;

// //将限制添加到group中
//   moveit_msgs::Constraints test_constraints;
//   test_constraints.orientation_constraints.push_back(ocm);  
//   group.setPathConstraints(test_constraints);

//笛卡尔路径
std::vector<geometry_msgs::Pose> waypoints;

geometry_msgs::Pose target_pose3 = target_pose1;
 waypoints.push_back(target_pose3);
  target_pose3.position.x += 0.2;
  target_pose3.position.z += 0.2;
 waypoints.push_back(target_pose3);
 //第二个点
target_pose3.position.y -= 0.2;
  waypoints.push_back(target_pose3);
//第三个点
  target_pose3.position.z -= 0.2;
  target_pose3.position.y += 0.2;
  target_pose3.position.x -= 0.2;
  waypoints.push_back(target_pose3); 
//步长1cm，设置为0.01，jump threshold是0.0意味着无jump threshold
  moveit_msgs::RobotTrajectory trajectory;
  double fraction = group.computeCartesianPath(waypoints,
                                               0.01,  // eef_step
                                               0.0,   // jump_threshold
                                               trajectory);
 ROS_INFO("Visualizing plan 4 (cartesian path) (%.2f%% acheived)",
        fraction * 100.0);    
  /* Sleep to give Rviz time to visualize the plan. */
  sleep(20.0);




 // sleep(2.0);
  ros::shutdown();
  return 0;
}