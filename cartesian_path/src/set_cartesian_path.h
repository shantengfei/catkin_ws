#ifndef SET_CARTESIAN_PATH_H
#define SET_CARTESIAN_PATH_H

//所需要包含的头文件
#include <ros/ros.h>
#include <QPushButton>
#include <QLabel>
#include <ros/console.h>
#include <rviz/panel.h>   //plugin基类的头文件
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
class QLineEdit;

namespace cartesian_path
{
// 所有的plugin都必须是rviz::Panel的子类
class set_cartesian_path: public rviz::Panel
{
// 后边需要用到Qt的信号和槽，都是QObject的子类，所以需要声明Q_OBJECT宏
Q_OBJECT
public:
  // 构造函数，在类中会用到QWidget的实例来实现GUI界面，这里先初始化为0即可
  set_cartesian_path( QWidget* parent = 0 );

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

//显示当前的点的位姿的框
 QLabel* currentPX;
 double curPX;
 QLabel* currentPY;
  double curPY;
 QLabel* currentPZ;
  double curPZ;
 QLabel* currentOX;
 double curOX;
 QLabel* currentOY;
  double curOY;
 QLabel* currentOZ;
  double curOZ;
 QLabel* currentOW;
  double curOW;
 QLineEdit* wayPNum;
 QPushButton* check;
 QPushButton* previous;
 QPushButton* next;
 


 QPushButton* Plan;
 QPushButton* Move;
 QPushButton* PlanAndMove;
 QPushButton* PlanRandom;
 QPushButton* save;

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
    std::vector<geometry_msgs::Pose> waypoints;
};

} // end namespace rviz_teleop_commander

#endif // TELEOP_PANEL_H
