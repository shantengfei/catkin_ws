#include "joint_value_monitor/joint_value.h"
#include <stdio.h>
#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
//#include <sensor_msgs/JointState.h>
#include <QTimer>
//#include <ros/ros.h>
#include <QDebug>
namespace joint_value_monitor 
{
joint_value::joint_value(QWidget *parent): rviz::Panel(parent)
 {
     //创建joint_value的显示窗口 
  QVBoxLayout *topic_layout = new QVBoxLayout;
  //创建joint_1显示栏
  topic_layout->addWidget(new QLabel("joint1_value"));
  QLjoint1 = new QLabel;
  topic_layout->addWidget(QLjoint1);
  //创建joint_2显示栏
  topic_layout->addWidget(new QLabel("joint2_value"));
  QLjoint2 = new QLabel;
  topic_layout->addWidget(QLjoint2);
  //创建joint_3显示栏
  topic_layout->addWidget(new QLabel("joint3_value"));
  QLjoint3 = new QLabel;
  topic_layout->addWidget(QLjoint3);
  //创建joint_4显示栏
  topic_layout->addWidget(new QLabel("joint4_value"));
  QLjoint4 = new QLabel;
  topic_layout->addWidget(QLjoint4);
  //创建joint_5显示栏
  topic_layout->addWidget(new QLabel("joint5_value"));
  QLjoint5 = new QLabel;
  topic_layout->addWidget(QLjoint5);
  //创建joint_6显示栏
  topic_layout->addWidget(new QLabel("joint6_value"));
  QLjoint6 = new QLabel;
  topic_layout->addWidget(QLjoint6);

  //
  QHBoxLayout *layout = new QHBoxLayout;
  layout->addLayout(topic_layout);
  setLayout(layout);
  // 创建一个定时器，用来定时显示信息；
  QTimer *output_timer = new QTimer(this);
  //设置定时器回调函数，按周期调用update函数
  connect(output_timer, SIGNAL(timeout()), this, SLOT(update_joint_value()));
  output_timer->start(10);
 }
 void joint_value::chatterCB(const sensor_msgs::JointState& msg) 
 {

          joint1=msg.position[0];
          QLjoint1->setNum(joint1);

          joint2 = msg.position[1];
          QLjoint2->setNum(joint2);

          joint3 = msg.position[2];
          QLjoint3->setNum(joint3);

          joint4 = msg.position[3];
          QLjoint4->setNum(joint4);

          joint5 = msg.position[4];
          QLjoint5->setNum(joint5);

          joint6 = msg.position[5];
          QLjoint6->setNum(joint6);
  }
   void joint_value::update_joint_value()
   {
       if(ros::ok())
       {
         sub =
             nh_.subscribe("jakaUr/joint_states", 1000, &joint_value::chatterCB,this);
       }
       ros::spinOnce();
   }
 


} // end of namespace joint_value_monitor

// 声明此类是一个rviz的插件
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(joint_value_monitor::joint_value, rviz::Panel)
