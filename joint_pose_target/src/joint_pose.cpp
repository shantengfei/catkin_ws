#include <stdio.h>

#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <QDebug>
#include "joint_pose.h"

namespace joint_pose_target
{

// 构造函数，初始化变量
joint_pose::joint_pose( QWidget* parent )
  : rviz::Panel( parent ),spinner(1),group("jakaUr"),group_variable_values(6)
{
   spinner.start();
  ROS_INFO("Reference frame: %s", group.getPlanningFrame().c_str());
  ROS_INFO("Reference frame: %s", group.getEndEffectorLink().c_str());
 
  // 创建一个输入topic命名的窗口
  QVBoxLayout* topic_layout = new QVBoxLayout;
  topic_layout->addWidget( new QLabel( "Joint1" ));
  position1 = new QLineEdit;
  topic_layout->addWidget( position1 );
   position1->setObjectName("1");

  // 创建一个输入线速度的窗口
  topic_layout->addWidget( new QLabel( "Joint2" ));
  position2 = new QLineEdit;
  topic_layout->addWidget( position2 );
 position2->setObjectName("2");
  // 创建一个输入角速度的窗口
  topic_layout->addWidget( new QLabel( "Joint3" ));
  position3 = new QLineEdit;
  topic_layout->addWidget( position3 );
   position3->setObjectName("3");

  topic_layout->addWidget( new QLabel( "Joint4" ));
  position4 = new QLineEdit;
  topic_layout->addWidget( position4 );
   position4->setObjectName("4");

  topic_layout->addWidget( new QLabel( "Joint5" ));
  position5 = new QLineEdit;
  topic_layout->addWidget( position5 );
   position5->setObjectName("5");

  topic_layout->addWidget( new QLabel( "Joint6" ));
  position6 = new QLineEdit;
  topic_layout->addWidget( position6 );
   position6->setObjectName("6");

  Plan=new QPushButton;
  Plan->setText("Plan");
  topic_layout->addWidget(Plan);

    Move=new QPushButton;
     Move->setText("Move");
  topic_layout->addWidget(Move);

    PlanAndMove=new QPushButton;
    PlanAndMove->setText("PlanAndMove");
  topic_layout->addWidget(PlanAndMove);
  
  // PlanRandom=new QPushButton;
  //  PlanRandom ->setText("PlanRandom");
  // topic_layout->addWidget(PlanRandom);

  QHBoxLayout* layout = new QHBoxLayout;
  layout->addLayout( topic_layout );
  setLayout( layout );

  // 创建一个定时器，用来定时发布消息
 // QTimer* output_timer = new QTimer( this );

  // 设置信号与槽的连接
  connect( position1, SIGNAL( editingFinished() ), this, SLOT( updateSLOT() ));            
  connect( position2, SIGNAL( editingFinished() ), this, SLOT( updateSLOT() )); 
  connect( position3, SIGNAL( editingFinished() ), this, SLOT( updateSLOT() ));
  connect( position4, SIGNAL( editingFinished() ), this, SLOT( updateSLOT() ));         
  connect( position5, SIGNAL( editingFinished() ), this, SLOT( updateSLOT() )); 
  connect( position6, SIGNAL( editingFinished() ), this, SLOT( updateSLOT() ));
 
//按钮的信号和槽函数
  connect( Plan, SIGNAL( clicked() ), this, SLOT( planFun() )); 
  connect( Move, SIGNAL( clicked() ), this, SLOT( moveFun() ));
  connect( PlanAndMove, SIGNAL( clicked() ), this, SLOT( planAndMoveFun() ));
  // connect( PlanRandom, SIGNAL( clicked() ), this, SLOT(  planRandomFun() ));

} //构造函数


// // 更新pose中的位置值
// void joint_pose::update_J1()
// {
//    // 获取输入框内的数据
//     QString temp_string = position1->text();
//     float pos1 = temp_string.toFloat();  
//     target_pose.position.x = pos1;
// group.setPoseTarget(target_pose);
// }

// void joint_pose::update_J2()
// {
//     QString temp_string = position2->text();
//     float pos2 = temp_string.toFloat() ;  
//     target_pose.position.y = pos2;
//     group.setPoseTarget(target_pose);
// }

// void joint_pose::update_J3()
// {
//  QString temp_string = position2->text();
//     float pos3 = temp_string.toFloat() ;  
//     target_pose.position.y =pos3;
//     group.setPoseTarget(target_pose);
// }

// void joint_pose::update_J4()
// {
//  QString temp_string = position2->text();
//     float Ox = temp_string.toFloat() ;  
//     target_pose.orientation.x = Ox;
//     group.setPoseTarget(target_pose);
// }

// void joint_pose::update_J5()
// {
//  QString temp_string = position2->text();
//     float Oy = temp_string.toFloat() ;  
//     target_pose.orientation.y = Oy;
//     group.setPoseTarget(target_pose);
// }

// void joint_pose::update_J6()
// {
//  QString temp_string = position2->text();
//     float Oz = temp_string.toFloat() ;  
//     target_pose.orientation.z = Oz;
//     group.setPoseTarget(target_pose);
// }

void joint_pose::updateSLOT()
{
   QString jointNumber;
   QLineEdit *lineEdit = qobject_cast<QLineEdit *>(sender());
   if (lineEdit != NULL) 
   {
    int Jnumber;
    bool ok;
    jointNumber = lineEdit->objectName();
    Jnumber=jointNumber.toInt(&ok,10);
   QString temp_string=lineEdit->text();
   double Jvalue= temp_string.toDouble() ; 
    ROS_INFO("%d %f",Jnumber,Jvalue);
    updateJ(Jnumber,Jvalue);
}
}

void joint_pose::updateJ(int i,double Jvalue)
{
  int k;
  k=i-1;
group_variable_values[k]=Jvalue;
group.setJointValueTarget(group_variable_values);
ROS_INFO("joint%d value is%f",i,group_variable_values[k]);
}

void joint_pose::planFun()
{
     bool success = group.plan(my_plan);
 ROS_INFO("Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");

 sleep(5.0);
}

void joint_pose::moveFun()
{
  group.asyncExecute(my_plan);
}

void joint_pose::planAndMoveFun()
{
     group.setJointValueTarget(group_variable_values);
  //阻塞的，要求必须有一个asynchronous spinner开启
   bool success = group.plan(my_plan);
     group.asyncExecute(my_plan);
}
// void joint_pose::planRandomFun()
// {
//   group_variable_values = group.getRandomJointValues();
//   group.setJointValueTarget(group_variable_values);
//      bool success = group.plan(my_plan);
//  ROS_INFO("Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");
//  sleep(5.0);
// }

} // end namespace rviz_teleop_commander

// 声明此类是一个rviz的插件
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(joint_pose_target::joint_pose,rviz::Panel )
// END_TUTORIAL
