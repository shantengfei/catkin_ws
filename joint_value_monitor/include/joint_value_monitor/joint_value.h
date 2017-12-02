#ifndef JOINT_VALUE_H
#define JOINT_VALUE_H

#include <ros/ros.h>
#include <ros/console.h>
#include <rviz/panel.h> //plugin基类的头文件
#include <sensor_msgs/JointState.h>
#include <QLabel>
class QLineEdit;

namespace joint_value_monitor
{

class joint_value : public rviz::Panel
 {
  // 后边需要用到Qt的信号和槽，都是QObject的子类，所以需要声明Q_OBJECT宏
  Q_OBJECT
public:
  // 构造函数，在类中会用到QWidget的实例来实现GUI界面，这里先初始化为0即可
 joint_value(QWidget *parent = 0);

 // 重载rviz::Panel积累中的函数，用于保存、加载配置文件中的数据，在我们这个plugin
 // 中，数据就是topic的名称 
 //这里还是不知道怎么用
 virtual void load(const rviz::Config &config);
 virtual void save(rviz::Config config) const;

 //公共槽

 //内部槽
 protected Q_SLOTS:
 void update_joint_value();
protected:
  void chatterCB(const sensor_msgs::JointState& msg);
      //内部变量，各个关节的实际数据，使用QLabel来显示
QLabel *QLjoint1;
QLabel* QLjoint2;
QLabel *QLjoint3;
QLabel *QLjoint4;
QLabel *QLjoint5;
QLabel *QLjoint6;
QString joint1Value;
QString joint2Value;
QString joint3Value;
QString joint4Value;
QString joint5Value;
QString joint6Value;

 double joint1{0};
 double joint2{0};
 double joint3{0};
 double joint4{0};
 double joint5{0};
 double joint6{0};
 
 ros::Subscriber sub;
 ros::NodeHandle nh_;

};
} // end of namespace joint_value_monitor
#endif