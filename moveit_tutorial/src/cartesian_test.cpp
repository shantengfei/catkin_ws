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
//    geometry_msgs::PoseStamped pose = group.getRandomPose();
//    pose.header.stamp = ros::Time::now();

//    target_pose1.position.x = 0.3;
//    target_pose1.position.y = 0.2;
//    target_pose1.position.z = 0.1;

// ROS_INFO("target_pose1.orientation w %f,x%f,y%f,z%f",target_pose1.orientation.w,target_pose1.orientation.x,target_pose1.orientation.y,target_pose1.orientation.z);
//   group.setPoseTarget(target_pose1);

//  moveit::planning_interface::MoveGroup::Plan my_plan;

//  bool success = group.plan(my_plan);
 
//  ROS_INFO("Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");
//   /* Sleep to give Rviz time to visualize the plan. */
//  sleep(5.0);

//笛卡尔路径
std::vector<geometry_msgs::Pose> waypoints;
geometry_msgs::Pose start_pose= group.getCurrentPose().pose;
ROS_INFO("%f %f %f",start_pose.position.x,start_pose.position.y,start_pose.position.z);
 waypoints.push_back(start_pose);
//geometry_msgs::Pose target_pose3 = target_pose1;
geometry_msgs::Pose target_pose3 = start_pose;
// waypoints.push_back(target_pose3);
  target_pose3.position.x += 0.1;
 // target_pose3.position.z += 0.1;
 waypoints.push_back(target_pose3);
 //第二个点
target_pose3.position.z += 0.1;
  waypoints.push_back(target_pose3);
//第三个点
  //target_pose3.position.z -= 0.2;
 // target_pose3.position.y += 0.2;
  target_pose3.position.x += 0.1;
  waypoints.push_back(target_pose3); 
//步长1cm，设置为0.01，jump threshold是0.0意味着无jump threshold
  moveit_msgs::RobotTrajectory trajectory;
  double fraction = group.computeCartesianPath(waypoints,
                                               0.01,  // eef_step
                                               0.0,   // jump_threshold
                                               trajectory);
 ROS_INFO("Visualizing plan 4 (cartesian path) (%.2f%% acheived)",
        fraction * 100.0);    
         // group.asyncExecute(my_plan);
   //     group.move();
  /* Sleep to give Rviz time to visualize the plan. */
moveit::planning_interface::MoveGroup::Plan my_plan;
my_plan.trajectory_= trajectory;
group.execute(my_plan);
  sleep(10.0);




 // sleep(2.0);
  ros::shutdown();
  return 0;
}