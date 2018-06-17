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
#include "set_cartesian_path.h"

namespace cartesian_path
{

// 构造函数，初始化变量
set_cartesian_path::set_cartesian_path( QWidget* parent )
  : rviz::Panel( parent ),spinner(1),group("jakaUr"),wayPointNum(0)
{
  //初始化使当前位置是路径点的第一个点
  geometry_msgs::Pose start_pose= group.getCurrentPose().pose;
  waypoints.push_back(start_pose);
  //多线程的自缠绕
   spinner.start();
  ROS_INFO("Reference frame: %s", group.getPlanningFrame().c_str());
  ROS_INFO("Reference frame: %s", group.getEndEffectorLink().c_str());
 
  //界面部分，左侧的垂直列 输入必须经过的点的位置
  QVBoxLayout* topic_layout = new QVBoxLayout;
  topic_layout->addWidget( new QLabel( "Pose Goal position X" ));
  positionX = new QLineEdit;
  topic_layout->addWidget( positionX );


  topic_layout->addWidget( new QLabel( "Pose Goal position Y" ));
  positionY = new QLineEdit;
  topic_layout->addWidget( positionY );

  
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

    save=new QPushButton;
  save->setText("save");
  topic_layout->addWidget(save);

  Plan=new QPushButton;
  Plan->setText("Plan");
  topic_layout->addWidget(Plan);

    Move=new QPushButton;
     Move->setText("Move");
  topic_layout->addWidget(Move);

    PlanAndMove=new QPushButton;
    PlanAndMove->setText("PlanAndMove");
  topic_layout->addWidget(PlanAndMove);
  
  PlanRandom=new QPushButton;
   PlanRandom ->setText("PlanRandom");
  topic_layout->addWidget(PlanRandom);





//右侧垂直列，显示当前的点位姿
  QVBoxLayout* current_point_layout = new QVBoxLayout;
  current_point_layout->addWidget(new QLabel("Current point"));
   current_point_layout->addWidget( new QLabel( "position X" ));
   currentPX=new QLabel;
   current_point_layout->addWidget(currentPX);
  current_point_layout->addWidget( new QLabel( "position Y" ));
  currentPY=new QLabel;
   current_point_layout->addWidget(currentPY);
  current_point_layout->addWidget( new QLabel( "position Z" ));
   currentPZ=new QLabel;
   current_point_layout->addWidget(currentPZ);
  current_point_layout->addWidget( new QLabel( "orientation X" ));
  currentOX=new QLabel;
   current_point_layout->addWidget(currentOX);
  current_point_layout->addWidget( new QLabel( "orientation Y" ));
  currentOY=new QLabel;
   current_point_layout->addWidget(currentOY);
  current_point_layout->addWidget( new QLabel( "orientation Z" ));
  currentOZ=new QLabel;
   current_point_layout->addWidget(currentOZ);
  current_point_layout->addWidget( new QLabel( "orientation W" )); 
  currentOW=new QLabel;
   current_point_layout->addWidget(currentOW);
    current_point_layout->addWidget( new QLabel( "waypoint number" ));
   wayPNum=new QLineEdit;
    current_point_layout->addWidget(wayPNum);

   check=new QPushButton;
   check->setText("check");
   current_point_layout->addWidget(check);

   previous=new QPushButton;
   previous->setText("previous");
   current_point_layout->addWidget(previous);

      next=new QPushButton;
   next->setText("next");
   current_point_layout->addWidget(next);



  QHBoxLayout* layout = new QHBoxLayout;
  layout->addLayout( topic_layout );
  layout->addLayout(current_point_layout);
  setLayout( layout );

  // 创建一个定时器，用来定时发布消息
 // QTimer* output_timer = new QTimer( this );

  // 当前输入点的位姿更新
  connect( positionX, SIGNAL( editingFinished() ), this, SLOT( update_Px() ));            
  connect( positionY, SIGNAL( editingFinished() ), this, SLOT( update_Py() )); 
  connect( positionZ, SIGNAL( editingFinished() ), this, SLOT( update_Pz() ));
  connect( orientationX, SIGNAL( editingFinished() ), this, SLOT( update_Ox() ));         
  connect( orientationY, SIGNAL( editingFinished() ), this, SLOT( update_Oy() )); 
  connect( orientationZ, SIGNAL( editingFinished() ), this, SLOT( update_Oz() ));
  connect( orientationW, SIGNAL( editingFinished() ), this, SLOT( update_Ow() ));
  connect( save, SIGNAL( clicked() ), this, SLOT( push_inFun() ));
//按钮的信号和槽函数
  connect( Plan, SIGNAL( clicked() ), this, SLOT( planFun() )); 
  connect( Move, SIGNAL( clicked() ), this, SLOT( moveFun() ));
  connect( PlanAndMove, SIGNAL( clicked() ), this, SLOT( planAndMoveFun() ));
  connect( PlanRandom, SIGNAL( clicked() ), this, SLOT(  planRandomFun() ));

  // 设置定时器的回调函数，按周期调用sendVel()
  //connect( output_timer, SIGNAL( timeout() ), this, SLOT( sendGoal() ));
  // 设置定时器的周期，100ms
 // output_timer->start( 100 );
 
} //构造函数


// 更新pose中的位置值
void set_cartesian_path::update_Px()
{
    // 获取输入框内的数据
    QString temp_string = positionX->text();
    float Px = temp_string.toFloat();  
    target_pose.position.x = Px;
//group.setPoseTarget(target_pose);
}

void set_cartesian_path::update_Py()
{
    QString temp_string = positionY->text();
    float Py = temp_string.toFloat() ;  
    target_pose.position.y = Py;
 //   group.setPoseTarget(target_pose);
}

void set_cartesian_path::update_Pz()
{
 QString temp_string = positionY->text();
    float Pz = temp_string.toFloat() ;  
    target_pose.position.y = Pz;
 //   group.setPoseTarget(target_pose);
}

void set_cartesian_path::update_Ox()
{
 QString temp_string = positionY->text();
    float Ox = temp_string.toFloat() ;  
    target_pose.orientation.x = Ox;
 //   group.setPoseTarget(target_pose);
}

void set_cartesian_path::update_Oy()
{
 QString temp_string = positionY->text();
    float Oy = temp_string.toFloat() ;  
    target_pose.orientation.y = Oy;
  //  group.setPoseTarget(target_pose);
}

void set_cartesian_path::update_Oz()
{
 QString temp_string = positionY->text();
    float Oz = temp_string.toFloat() ;  
    target_pose.orientation.z = Oz;
 //   group.setPoseTarget(target_pose);
}

void set_cartesian_path::update_Ow()
{
 QString temp_string = positionY->text();
    float Ow = temp_string.toFloat();  
    target_pose.orientation.w = Ow;
 //   group.setPoseTarget(target_pose);
}
 void set_cartesian_path::push_inFun()
 {
  
   waypoints.push_back(target_pose);
    int num=waypoints.size();
   ROS_INFO("waypoint number %d",num);
   ROS_INFO("the %d position is %f %f",num,waypoints[num-1].position.x,waypoints[num-1].orientation.x);
   if(wayPointNum==(waypoints.size()-2))
   {
   //记录vector中的路点个数
   wayPointNum++;
   //路点清零；
  //  target_pose.position.x=0;
  //  target_pose.position.y=0;
  //  target_pose.position.z=0;
  //  target_pose.orientation.x=0;
  //  target_pose.orientation.y=0;
  //  target_pose.orientation.z=0;
  //  target_pose.orientation.w=0;
   ROS_INFO("success added 1 point!");
   }
   else
   ROS_INFO("failed push in waypoints");

 }


void set_cartesian_path::planFun()
{

  double fraction = group.computeCartesianPath(waypoints,
                                               0.03,  // eef_step
                                               0.0,   // jump_threshold
                                               trajectory);

  ROS_INFO("Visualizing plan 4 (cartesian path) (%.2f%% acheived)",
        fraction * 100.0);    
 //sleep(15.0);
}

void set_cartesian_path::moveFun()
{
  my_plan.trajectory_= trajectory;
//group.execute(my_plan);
  group.asyncExecute(my_plan);
  //执行完后需要进行当前位置植入首个点
  geometry_msgs::Pose start_pose= group.getCurrentPose().pose;
  waypoints.push_back(start_pose);
}

void set_cartesian_path::planAndMoveFun()
{

}
void set_cartesian_path:: planRandomFun()
{
  geometry_msgs::PoseStamped pose = group.getRandomPose();
   pose.header.stamp = ros::Time::now();
   target_pose.orientation.w = pose.pose.orientation.w;
   target_pose.orientation.x = pose.pose.orientation.x;
   target_pose.orientation.y = pose.pose.orientation.y;
   target_pose.orientation.z = pose.pose.orientation.z;
   target_pose.position.x = pose.pose.position.x;
   target_pose.position.y = pose.pose.position.y;
   target_pose.position.z = pose.pose.position.z;

}


} // end namespace rviz_teleop_commander

// 声明此类是一个rviz的插件
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS( cartesian_path::set_cartesian_path,rviz::Panel )
// END_TUTORIAL
