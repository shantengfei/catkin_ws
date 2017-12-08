#ifndef POINT_MOVE_TEST_H
#define POINT_MOVE_TEST_H

//所需要包含的头文件
#include <ros/ros.h>
#include <ros/console.h>
#include <rviz/panel.h>   //plugin基类的头文件
#include <QPushButton>
#include <QLabel>
//#include <QString>
#include <sensor_msgs/JointState.h>
#include <actionlib/client/simple_action_client.h>
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <control_msgs/FollowJointTrajectoryActionGoal.h>
#include <control_msgs/FollowJointTrajectoryGoal.h>
#include <control_msgs/FollowJointTrajectoryFeedback.h>
#include <control_msgs/FollowJointTrajectoryResult.h>
#include <Eigen/Geometry>
class QLineEdit;
 
namespace point_move_test
{
// 所有的plugin都必须是rviz::Panel的子类
class PointMovePanel : public rviz::Panel {
// 后边需要用到Qt的信号和槽，都是QObject的子类，所以需要声明Q_OBJECT宏
Q_OBJECT
public:
  // 构造函数，在类中会用到QWidget的实例来实现GUI界面，这里先初始化为0即可
  PointMovePanel(QWidget *parent = 0);

  // 公共槽.
public Q_SLOTS:
void sendJointValue();

  // 内部槽.
protected Q_SLOTS:
  //获得角度值
  void update_joint_value();
  //增加
  void addButtonClick();
  //减
  
  void reduceButtonClick();
  // 内部变量.
protected:
//标签
  QLabel* joint1;
  QLabel* joint2;
  QLabel* joint3;
  QLabel* joint4;
  QLabel* joint5;
  QLabel* joint6;
  //各轴的按钮
  QPushButton* add1;
  QPushButton* add2;
  QPushButton* add3;
  QPushButton* add4;
  QPushButton* add5;
  QPushButton* add6;
  QPushButton* reduce1;
  QPushButton* reduce2;
  QPushButton* reduce3;
  QPushButton* reduce4;
  QPushButton* reduce5;
  QPushButton* reduce6;
//获取当前launch 文件下的正确的话题
  std::string actionName ;
  std::string topicName ;
  //QString jointNumber;
  bool sim ;
  double step;
  control_msgs::FollowJointTrajectoryGoal goal;
  double currentJointValue[6];
  ros::NodeHandle nh_;
  ros::Subscriber jointSub;
  typedef actionlib::SimpleActionClient<control_msgs::FollowJointTrajectoryAction> Client;

  void chatterCB(const sensor_msgs::JointState &msg);
  void addJstate(int joint);
  void reduceJstate(int joint);
};

} // end namespace rviz_teleop_commander

#endif // TELEOP_PANEL_H


