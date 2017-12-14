#ifndef TELEOP_PAD_H
#define TELEOP_PAD_H

//所需要包含的头文件
#include <ros/ros.h>
#include <ros/console.h>
#include <rviz/panel.h>   //plugin基类的头文件
#include <QLabel>
#include <sensor_msgs/JointState.h>
#include "tf/transform_listener.h"

class QLineEdit;

namespace rviz_teleop_commander
{
// 所有的plugin都必须是rviz::Panel的子类
class TeleopPanel: public rviz::Panel
{
// 后边需要用到Qt的信号和槽，都是QObject的子类，所以需要声明Q_OBJECT宏
Q_OBJECT
public:
  // 构造函数，在类中会用到QWidget的实例来实现GUI界面，这里先初始化为0即可
  TeleopPanel( QWidget* parent = 0 );

      // 公共槽.
      public Q_SLOTS :
      // 当用户输入topic的命名并按下回车后，回调用此槽来创建一个相应名称的topic
      // publisher
      void
      setTopic(const QString &topic);

  // 内部槽.
protected Q_SLOTS:
  void update_joint_value();               //更新各个关节的信息
  void update_pose_value(); 
      // 内部变量.
protected:
//显示的是6个关节角度
  QLabel *QLjoint1;
  QLabel *QLjoint2;
  QLabel *QLjoint3;
  QLabel *QLjoint4;
  QLabel *QLjoint5;
  QLabel *QLjoint6;
  double joint[6]={0};
  //显示的是末端在工作空间下的位姿
QLabel *Px;
QLabel *Py;
QLabel *Pz;
QLabel *Ox;
QLabel *Oy;
QLabel *Oz;
QLabel *Ow;
QLabel *pitchAg;
QLabel *yawAg;
QLabel *rollAg;
tf::TransformListener listener;

  void chatterCB(const sensor_msgs::JointState &msg);

  ros::Subscriber jointSub;
  // The ROS node handle.
  //这里的是判断话题是那个话题的部分
  ros::NodeHandle nh_;
  ros::NodeHandle nh_tf;
  std::string topicName ;
  bool sim ;
};

} // end namespace rviz_teleop_commander

#endif // TELEOP_PANEL_H

