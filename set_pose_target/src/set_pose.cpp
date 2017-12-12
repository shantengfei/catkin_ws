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
#include "set_pose.h"

namespace set_pose_target
{

// 构造函数，初始化变量
set_pose::set_pose( QWidget* parent )
  : rviz::Panel( parent ),spinner(1),group("jakaUr")
{
   spinner.start();
  ROS_INFO("Reference frame: %s", group.getPlanningFrame().c_str());
  ROS_INFO("Reference frame: %s", group.getEndEffectorLink().c_str());
 
  // 创建一个输入topic命名的窗口
  QVBoxLayout* topic_layout = new QVBoxLayout;
  topic_layout->addWidget( new QLabel( "Pose Goal position X" ));
  positionX = new QLineEdit;
  topic_layout->addWidget( positionX );

  // 创建一个输入线速度的窗口
  topic_layout->addWidget( new QLabel( "Pose Goal position Y" ));
  positionY = new QLineEdit;
  topic_layout->addWidget( positionY );

  // 创建一个输入角速度的窗口
  topic_layout->addWidget( new QLabel( "Pose Goal position Z" ));
  positionZ = new QLineEdit;
  topic_layout->addWidget( positionZ );

  topic_layout->addWidget( new QLabel( "Pose Goal orientation X" ));
  orientationX = new QLineEdit;
  topic_layout->addWidget( orientationX );

  topic_layout->addWidget( new QLabel( "Pose Goal orientation Y" ));
  orientationY = new QLineEdit;
  topic_layout->addWidget( orientationY );

    topic_layout->addWidget( new QLabel( "Pose Goal orientation Z" ));
  orientationZ = new QLineEdit;
  topic_layout->addWidget( orientationZ );

  topic_layout->addWidget( new QLabel( "Pose Goal orientation W" ));
  orientationW = new QLineEdit;
  topic_layout->addWidget( orientationW );

  Plan=new QPushButton;
  Plan->setText("Plan");
  topic_layout->addWidget(Plan);

    Move=new QPushButton;
     Move->setText("Move");
  topic_layout->addWidget(Move);

    PlanAndMove=new QPushButton;
    PlanAndMove->setText("PlanAndMove");
  topic_layout->addWidget(PlanAndMove);


  QHBoxLayout* layout = new QHBoxLayout;
  layout->addLayout( topic_layout );
  setLayout( layout );

  // 创建一个定时器，用来定时发布消息
 // QTimer* output_timer = new QTimer( this );

  // 设置信号与槽的连接
  connect( positionX, SIGNAL( editingFinished() ), this, SLOT( update_Px() ));            
  connect( positionY, SIGNAL( editingFinished() ), this, SLOT( update_Py() )); 
  connect( positionZ, SIGNAL( editingFinished() ), this, SLOT( update_Pz() ));
  connect( positionX, SIGNAL( editingFinished() ), this, SLOT( update_Ox() ));         
  connect( positionY, SIGNAL( editingFinished() ), this, SLOT( update_Oy() )); 
  connect( positionZ, SIGNAL( editingFinished() ), this, SLOT( update_Oz() ));
  connect( positionZ, SIGNAL( editingFinished() ), this, SLOT( update_Ow() ));
//按钮的信号和槽函数
  connect( Plan, SIGNAL( clicked() ), this, SLOT( planFun() )); 
  connect( Move, SIGNAL( clicked() ), this, SLOT( moveFun() ));
  connect( PlanAndMove, SIGNAL( clicked() ), this, SLOT( planAndMoveFun() ));

  // 设置定时器的回调函数，按周期调用sendVel()
  //connect( output_timer, SIGNAL( timeout() ), this, SLOT( sendGoal() ));
  // 设置定时器的周期，100ms
 // output_timer->start( 100 );
 
} //构造函数


// 更新pose中的位置值
void set_pose::update_Px()
{
    // 获取输入框内的数据
    QString temp_string = positionX->text();
    float Px = temp_string.toFloat();  
    target_pose.position.x = Px;

}

void set_pose::update_Py()
{
    QString temp_string = positionY->text();
    float Py = temp_string.toFloat() ;  
    target_pose.position.y = Py;
}

void set_pose::update_Pz()
{
 QString temp_string = positionY->text();
    float Pz = temp_string.toFloat() ;  
    target_pose.position.y = Pz;
}

void set_pose::update_Ox()
{
 QString temp_string = positionY->text();
    float Ox = temp_string.toFloat() ;  
    target_pose.orientation.x = Ox;
}

void set_pose::update_Oy()
{
 QString temp_string = positionY->text();
    float Oy = temp_string.toFloat() ;  
    target_pose.orientation.y = Oy;
}

void set_pose::update_Oz()
{
 QString temp_string = positionY->text();
    float Oz = temp_string.toFloat() ;  
    target_pose.orientation.z = Oz;
}

void set_pose::update_Ow()
{
 QString temp_string = positionY->text();
    float Ow = temp_string.toFloat() ;  
    target_pose.orientation.w = Ow;
}

// 发布消息
void set_pose::planFun()
{
  // joint_model_group =
  //   group.getCurrentState()->getJointModelGroup("jakaUr");
  //   namespace rvt = rviz_visual_tools;
  // moveit_visual_tools::MoveItVisualTools visual_tools("odom_combined");
  // visual_tools.deleteAllMarkers();
  // Eigen::Affine3d text_pose = Eigen::Affine3d::Identity();
  // text_pose.translation().z() = 1.75; // above head of PR2
  // visual_tools.publishText(text_pose, "MoveGroupInterface Demo", rvt::WHITE, rvt::XLARGE);
  // // visual_tools.trigger();
     

 //geometry_msgs::PoseStamped pose = group.getRandomPose();
   //pose.header.stamp = ros::Time::now();
   //target_pose.orientation.w = pose.pose.orientation.w;
   //target_pose1.orientation.x = pose.pose.orientation.x;
  // target_pose1.orientation.y = pose.pose.orientation.y;
  // target_pose1.orientation.z = pose.pose.orientation.z;
  //  target_pose.position.x = pose.pose.position.x;
  //  target_pose.position.y = pose.pose.position.y;
  //  target_pose.position.z = pose.pose.position.z;
   group.setPoseTarget(target_pose);
   
     bool success = group.plan(my_plan);
 ROS_INFO("Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");
//  visual_tools.publishAxisLabeled(target_pose, "pose1");
//   visual_tools.publishText(text_pose, "Pose Goal", rvt::WHITE, rvt::XLARGE);
//   visual_tools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
// //  visual_tools.trigger();
//   visual_tools.prompt("next step");
  /* Sleep to give Rviz time to visualize the plan. */
 sleep(5.0);
}

void set_pose::moveFun()
{
  group.asyncExecute(my_plan);
}

void set_pose::planAndMoveFun()
{
  //阻塞的，要求必须有一个asynchronous spinner开启
  group.move();
}


} // end namespace rviz_teleop_commander

// 声明此类是一个rviz的插件
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(set_pose_target::set_pose,rviz::Panel )
// END_TUTORIAL
