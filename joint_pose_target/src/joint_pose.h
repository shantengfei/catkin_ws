#ifndef JOINT_POSE_H
#define JOINT_POSE_H

//所需要包含的头文件
#include <ros/ros.h>
#include <QPushButton>
#include <ros/console.h>
#include <rviz/panel.h>   //plugin基类的头文件
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
class QLineEdit;

namespace joint_pose_target
{
// 所有的plugin都必须是rviz::Panel的子类
class joint_pose: public rviz::Panel
{
// 后边需要用到Qt的信号和槽，都是QObject的子类，所以需要声明Q_OBJECT宏
Q_OBJECT
public:
  // 构造函数，在类中会用到QWidget的实例来实现GUI界面，这里先初始化为0即可
  joint_pose( QWidget* parent = 0 );

  // 公共槽.
public Q_SLOTS:


  // 内部槽.
protected Q_SLOTS:
  void planFun();                 // 
  void moveFun();
  void planAndMoveFun();
  void planRandomFun();
  void updateSLOT();
  // void update_J1();
  // void update_J2(); // 
  // void update_J3();
  // void update_J4(); 
  // void update_J5();
  // void update_J6();
  void updateJ(int i,double Jvalue);

  // 内部变量.
protected:
  // topic name输入框
  QLineEdit* position1;
  double pos1;
  // 线速度值输入框
  QLineEdit* position2;
   double pos2;
  // 角速度值输入框
  QLineEdit* position3;
  double pos3;
 
 QLineEdit* position4;
  double pos4;
  // 线速度值输入框
  QLineEdit* position5;
   double pos5;
  // 角速度值输入框
  QLineEdit* position6;
  double pos6;

 QPushButton* Plan;
 QPushButton* Move;
 QPushButton* PlanAndMove;
// QPushButton* PlanRandom;
//关节角度值
 std::vector<double> group_variable_values;
 geometry_msgs::PoseStamped pose;
geometry_msgs::Pose target_pose;
  // The ROS node handle.
  ros::NodeHandle nh_;
  ros::AsyncSpinner spinner;
  moveit::planning_interface::MoveGroup group;
 moveit::planning_interface::MoveGroup::Plan my_plan;
const robot_state::JointModelGroup *joint_model_group;
   
};

} // end namespace rviz_teleop_commander

#endif // TELEOP_PANEL_H
