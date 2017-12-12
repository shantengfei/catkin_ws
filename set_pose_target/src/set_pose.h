#ifndef SET_POSE_H
#define SET_POSE_H

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

namespace set_pose_target
{
// 所有的plugin都必须是rviz::Panel的子类
class set_pose: public rviz::Panel
{
// 后边需要用到Qt的信号和槽，都是QObject的子类，所以需要声明Q_OBJECT宏
Q_OBJECT
public:
  // 构造函数，在类中会用到QWidget的实例来实现GUI界面，这里先初始化为0即可
  set_pose( QWidget* parent = 0 );

  // 公共槽.
public Q_SLOTS:


  // 内部槽.
protected Q_SLOTS:
  void planFun();                 // 显示plan的路径规划
  void moveFun();
  void planAndMoveFun();
  void planRandomFun();
  void update_Px();  // 根据用户的输入更新线速度值
  void update_Py(); // 根据用户的输入更新角速度值
  void update_Pz();
  void update_Ox();  // 根据用户的输入更新线速度值
  void update_Oy(); 
  void update_Oz();
  void update_Ow();

  // 内部变量.
protected:
  // topic name输入框
  QLineEdit* positionX;
  double posX;
  // 线速度值输入框
  QLineEdit* positionY;
   double posY;
  // 角速度值输入框
  QLineEdit* positionZ;
  double posZ;
 
 QLineEdit* orientationX;
  double oriX;
  // 线速度值输入框
  QLineEdit* orientationY;
   double oriY;
  // 角速度值输入框
  QLineEdit* orientationZ;
  double oriZ;
  QLineEdit* orientationW;
  double oriW;

 QPushButton* Plan;
 QPushButton* Move;
 QPushButton* PlanAndMove;
 QPushButton* PlanRandom;

 geometry_msgs::Pose target_pose;
 geometry_msgs::PoseStamped pose;
  // ROS的publisher，用来发布速度topic
  ros::Publisher velocity_publisher_;

  // The ROS node handle.
  ros::NodeHandle nh_;
  ros::AsyncSpinner spinner;
moveit::planning_interface::MoveGroup group;
 moveit::planning_interface::MoveGroup::Plan my_plan;
const robot_state::JointModelGroup *joint_model_group;
   
};

} // end namespace rviz_teleop_commander

#endif // TELEOP_PANEL_H
