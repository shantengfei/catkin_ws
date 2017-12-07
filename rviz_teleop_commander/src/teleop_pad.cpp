#include <stdio.h>
#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>

#include <geometry_msgs/Twist.h>
#include <QDebug>

#include "teleop_pad.h"

namespace rviz_teleop_commander
{

// 构造函数，初始化变量
TeleopPanel::TeleopPanel( QWidget* parent ) : rviz::Panel( parent )
{
  
      // 创建一个输入topic命名的窗口
      QVBoxLayout *topic_layout = new QVBoxLayout;
  topic_layout->addWidget( new QLabel( "joint1" ));
  // output_topic_editor_ = new QLineEdit;
  // topic_layout->addWidget(output_topic_editor_);
   QLjoint1 = new QLabel;
   topic_layout->addWidget(QLjoint1);
  // 创建一个输入线速度的窗口
  topic_layout->addWidget( new QLabel( "joint2" ));
//  output_topic_editor_1 = new QLineEdit;
//  topic_layout->addWidget( output_topic_editor_1 );
  QLjoint2 = new QLabel;
  topic_layout->addWidget(QLjoint2);

  // 创建一个输入角速度的窗口
  topic_layout->addWidget( new QLabel( "joint3" ));
//  output_topic_editor_2 = new QLineEdit;
//  topic_layout->addWidget( output_topic_editor_2 );
  QLjoint3 = new QLabel;
  topic_layout->addWidget(QLjoint3);

  topic_layout->addWidget(new QLabel("joint4"));
  QLjoint4 = new QLabel;
  topic_layout->addWidget(QLjoint4);

  topic_layout->addWidget(new QLabel("joint5"));
  QLjoint5 = new QLabel;
  topic_layout->addWidget(QLjoint5);

  topic_layout->addWidget(new QLabel("joint6"));
  QLjoint6 = new QLabel;
  topic_layout->addWidget(QLjoint6);

  QHBoxLayout* layout = new QHBoxLayout;
  layout->addLayout( topic_layout );
  setLayout( layout );
  // 创建一个定时器，用来定时发布消息
  QTimer* output_timer = new QTimer( this );

  // 设置定时器的回调函数，按周期调用sendVel()

  connect(output_timer, SIGNAL(timeout()), this, SLOT(update_joint_value()));
  // 设置定时器的周期，100ms,不可设置的过小，一旦设置过小就会出现响应的问题，所以这里不能设置定时器的时间过短，否则容易出问题
  output_timer->start( 100 );

} //构造函数的结尾

void TeleopPanel::chatterCB(const sensor_msgs::JointState &msg)
{
 for(int i=0;i<6;i++)
 joint[i]=msg.position[i];
  QLjoint1->setNum(joint[0]);
  QLjoint2->setNum(joint[1]);
  QLjoint3->setNum(joint[2]);
  QLjoint4->setNum(joint[3]);
  QLjoint5->setNum(joint[4]);
  QLjoint6->setNum(joint[5]);
//  ROS_INFO("%f",joint[2]);            调试的时候的使用在窗口中显示实时的函数执行情况，验证是定时器的问题
}
    void TeleopPanel::update_joint_value() 
{

  if (ros::ok())
 jointSub =nh_.subscribe("joint_states", 1000, &TeleopPanel::chatterCB, this);
}


  
} // end namespace rviz_teleop_commander

// 声明此类是一个rviz的插件
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(rviz_teleop_commander::TeleopPanel,rviz::Panel )
// END_TUTORIAL
