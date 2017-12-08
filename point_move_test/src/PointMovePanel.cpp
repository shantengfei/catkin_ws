#include <stdio.h>
#include <iostream>
#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QTimer>

#include <QDebug>
#include "PointMovePanel.h"

namespace point_move_test
{
// 构造函数，初始化变量
PointMovePanel::PointMovePanel(QWidget *parent)
    : rviz::Panel(parent), currentJointValue{0}, step(0.01),
      clientNoSim("joint_trajectory_action", true),
      clientSim("jakaUr/jaka_joint_controller/follow_joint_trajectory", true) {

  // 创建一个输入topic命名的窗口
  QVBoxLayout* topic_layout = new QVBoxLayout;
  topic_layout->addWidget( new QLabel( "Joint1" ));
  add1=new QPushButton;
  add1->setText("+");
  topic_layout->addWidget(add1);
  reduce1 = new QPushButton;
  reduce1->setText("-");
  topic_layout->addWidget(reduce1);
  topic_layout->addWidget( new QLabel( "Joint2" ));
  add2 = new QPushButton;
  add2->setText("+");
  topic_layout->addWidget(add2);
  reduce2 = new QPushButton;
  reduce2->setText("-");
  topic_layout->addWidget(reduce2);
  topic_layout->addWidget(new QLabel("Joint3"));
  add3 = new QPushButton;
  add3->setText("+");
  topic_layout->addWidget(add3);

  reduce3 = new QPushButton;
  reduce3->setText("-");
  topic_layout->addWidget(reduce3);
  topic_layout->addWidget(new QLabel("Joint4"));
  add4 = new QPushButton;
  add4->setText("+");
  topic_layout->addWidget(add4);

  reduce4 = new QPushButton;
  reduce4->setText("-");
  topic_layout->addWidget(reduce4);
  topic_layout->addWidget(new QLabel("Joint5"));
  add5 = new QPushButton;
  add5->setText("+");
  topic_layout->addWidget(add5);

  reduce5 = new QPushButton;
  reduce5->setText("-");
  topic_layout->addWidget(reduce5);

  topic_layout->addWidget(new QLabel("Joint6"));
  add6 = new QPushButton;
  add6->setText("+");
  topic_layout->addWidget(add6);
  reduce6 = new QPushButton;
  reduce6->setText("-");
  topic_layout->addWidget(reduce6);

  QHBoxLayout* layout = new QHBoxLayout;
  layout->addLayout( topic_layout );
  setLayout( layout );

  // 创建一个定时器，用来定时发布消息
  QTimer* output_timer = new QTimer( this );

  // 设置定时器的回调函数，按周期调用sendVel()
  connect( output_timer, SIGNAL( timeout() ), this, SLOT( update_joint_value()) );

  //将加信号与槽函数连接,不能直接传递参数
  connect(add1, SIGNAL(clicked()), this, SLOT(addButtonClick()));
  connect(add2, SIGNAL(clicked()), this, SLOT(addButtonClick()));
  connect(add3, SIGNAL(clicked()), this, SLOT(addButtonClick()));
  connect(add4, SIGNAL(clicked()), this, SLOT(addButtonClick()));
  connect(add5, SIGNAL(clicked()), this, SLOT(addButtonClick()));
  connect(add6, SIGNAL(clicked()), this, SLOT(addButtonClick()));
  add1->setObjectName("1");
  add2->setObjectName("2");
  add3->setObjectName("3");
  add4->setObjectName("4");
  add5->setObjectName("5");
  add6->setObjectName("6");
  add1->setAutoRepeat(true);
  add1->setAutoRepeatDelay(20);
  add1->setAutoRepeatInterval(20);
  add2->setAutoRepeat(true);
  add2->setAutoRepeatDelay(20);
  add2->setAutoRepeatInterval(20);
  add3->setAutoRepeat(true);
  add3->setAutoRepeatDelay(20);
  add3->setAutoRepeatInterval(20);
  add4->setAutoRepeat(true);
  add4->setAutoRepeatDelay(20);
  add4->setAutoRepeatInterval(20);
  add5->setAutoRepeat(true);
  add5->setAutoRepeatDelay(20);
  add5->setAutoRepeatInterval(20);
  add6->setAutoRepeat(true);
  add6->setAutoRepeatDelay(20);
  add6->setAutoRepeatInterval(20);
  //将减信号与槽函数连接
  connect(reduce1, SIGNAL(clicked()), this, SLOT(reduceButtonClick()));
  connect(reduce2, SIGNAL(clicked()), this, SLOT(reduceButtonClick()));
  connect(reduce3, SIGNAL(clicked()), this, SLOT(reduceButtonClick()));
  connect(reduce4, SIGNAL(clicked()), this, SLOT(reduceButtonClick()));
  connect(reduce5, SIGNAL(clicked()), this, SLOT(reduceButtonClick()));
  connect(reduce6, SIGNAL(clicked()), this, SLOT(reduceButtonClick()));
  reduce1->setObjectName("1");
  reduce2->setObjectName("2");
  reduce3->setObjectName("3");
  reduce4->setObjectName("4");
  reduce5->setObjectName("5");
  reduce6->setObjectName("6");
  reduce1->setAutoRepeat(true);
  reduce1->setAutoRepeatDelay(20);
  reduce1->setAutoRepeatInterval(20);
  reduce2->setAutoRepeat(true);
  reduce2->setAutoRepeatDelay(20);
  reduce2->setAutoRepeatInterval(20);
  reduce3->setAutoRepeat(true);
  reduce3->setAutoRepeatDelay(20);
  reduce3->setAutoRepeatInterval(20);
  reduce4->setAutoRepeat(true);
  reduce4->setAutoRepeatDelay(20);
  reduce4->setAutoRepeatInterval(20);
  reduce5->setAutoRepeat(true);
  reduce5->setAutoRepeatDelay(20);
  reduce5->setAutoRepeatInterval(20);
  reduce6->setAutoRepeat(true);
  reduce6->setAutoRepeatDelay(20);
  reduce6->setAutoRepeatInterval(20);
  // 设置定时器的周期，100ms
  output_timer->start( 100 );

//获取当前launch文件下到底应该选择哪个话题
  ros::param::get("sim", sim);
  ROS_INFO("the sim is %d", sim);
  ROS_INFO("%f",currentJointValue[3]);
  if (sim == true) 
  {
    actionName = "jakaUr/jaka_joint_controller/follow_joint_trajectory";
    topicName = "jakaUr/joint_states";
  } 
  else 
  {
    actionName = "joint_trajectory_action";
    topicName = "joint_states";
  }


  //初始化goal
  //这里的时间戳加上以后在用gazebo的时候会出现问题，就是时间过期的问题
  //goal.trajectory.header.stamp = ros::Time::now();
  goal.trajectory.joint_names.resize(6);
  goal.trajectory.points.resize(3);
  goal.trajectory.points[0].positions.resize(6);
  goal.trajectory.points[1].positions.resize(6);
  goal.trajectory.points[2].positions.resize(6);
  goal.trajectory.header.frame_id = "/world";

    goal.trajectory.joint_names[0] = "joint_1";
    goal.trajectory.joint_names[1] = "joint_2";
    goal.trajectory.joint_names[2] = "joint_3";
    goal.trajectory.joint_names[3] = "joint_4";
    goal.trajectory.joint_names[4] = "joint_5";
    goal.trajectory.joint_names[5] = "joint_6";

}//end of constructor

//订阅的回调函数
void PointMovePanel::chatterCB(const sensor_msgs::JointState &msg)
{
  for(int i=0;i<6;i++)
  {
    currentJointValue[i]= msg.position[i];
   // ROS_INFO("%f", currentJointValue[i]);
  }
}
//更新当前各轴的角度值；
void PointMovePanel::update_joint_value() 
{
  if (ros::ok())
    jointSub = nh_.subscribe(topicName, 1000, &PointMovePanel::chatterCB, this);
}

//增加的槽函数
void PointMovePanel::addJstate(int joint)
{
     int k=joint-1;   //轴号
   for(int j=0;j<3;j++)
   {
goal.trajectory.points[j].time_from_start = ros::Duration(0, 5000000 * (j + 1));
     for (int i = 0; i < 6; i++) 
     {
       goal.trajectory.points[j].positions[i] = currentJointValue[i];
     }

     if (j > 0) 
     {
       goal.trajectory.points[j].positions[k] += step * j;
       ROS_INFO("%f", goal.trajectory.points[j].positions[k]);
     }
   }
ROS_INFO("joint%d is clicked!",k);
}

void PointMovePanel::addButtonClick()
{
  QString jointNumber;
   QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
   if (clickedButton != NULL) 
   {
    int number;
    bool ok;
    jointNumber = clickedButton->objectName();
    number=jointNumber.toInt(&ok,10);
    ROS_INFO("%d",number);
     addJstate(number);
     if (ros::ok()) 
     {
       if (sim == true)
         clientSim.sendGoal(goal);
       else
         clientNoSim.sendGoal(goal);
      }
   }
}

//减的槽函数
void PointMovePanel::reduceJstate(int joint)
{
  int k = joint-1; //轴号
  for (int j = 0; j < 3; j++) 
  {
goal.trajectory.points[j].time_from_start =ros::Duration(0, 5000000 * (j + 1));
    for (int i = 0; i < 6; i++) 
    {
      goal.trajectory.points[j].positions[i] = currentJointValue[i];
    }
   
    if (j > 0) 
    {
      goal.trajectory.points[j].positions[k] -= step * j;
      ROS_INFO("%f", goal.trajectory.points[j].positions[k]);
    }
  }
  ROS_INFO("joint%d is clicked!", k);
}

void PointMovePanel::reduceButtonClick()
{
  QString jointNumber;
  QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
  if (clickedButton != NULL) {
    int number;
    bool ok;
    jointNumber = clickedButton->objectName();
    number = jointNumber.toInt(&ok, 10);
    ROS_INFO("%d", number);
    reduceJstate(number);
    if (ros::ok())
    {
      if(sim==true)
      clientSim.sendGoal(goal);
      else
      clientNoSim.sendGoal(goal);
    }
      
}
}

 void PointMovePanel::sendJointValue() 
{
  if (ros::ok()) 
    clientSim.sendGoal(goal);
}

} // end namespace rviz_teleop_commander

// 声明此类是一个rviz的插件
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(point_move_test::PointMovePanel,rviz::Panel)
// END_TUTORIAL
