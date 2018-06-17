#include <stdio.h>
#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QPushButton>

#include <geometry_msgs/Twist.h>
#include <QDebug>

#include "teleop_pad.h"
#define PI 3.141592653
namespace rviz_teleop_commander
{

// 构造函数，初始化变量
TeleopPanel::TeleopPanel( QWidget* parent ) : rviz::Panel( parent )
{
      

      // 显示关节角度的窗口
       QVBoxLayout *connect_layout = new QVBoxLayout;
       connect_layout->setContentsMargins(0,50,0,50);

       connect_layout->addWidget( new QLabel( "voice control" ));
           record=new QPushButton;
      record->setText("start ");
      connect_layout->addWidget(record);

              Delete=new QPushButton;
      Delete->setText("end ");
      connect_layout->addWidget(Delete);
      connect_layout->addWidget( new QLabel( "Robot Connect" ));
      ip=new QLineEdit;
      connect_layout->addWidget( new QLabel( "ip" ));
      connect_layout->addWidget(ip);

         port=new QLineEdit;
      connect_layout->addWidget( new QLabel( "port" ));
      connect_layout->addWidget(port);

       connect_layout->addWidget( new QLabel( "Current Connecting Status" ));
        connect_layout->addWidget( new QLineEdit( "" ));

        record=new QPushButton;
      record->setText("connect");
      connect_layout->addWidget(record);

              Delete=new QPushButton;
      Delete->setText("disconnect");
      connect_layout->addWidget(Delete);
         start=new QPushButton;
      start->setText("start");
      connect_layout->addWidget(start);

         stop=new QPushButton;
      stop->setText("stop");
      connect_layout->addWidget(stop);
          help=new QPushButton;
      help->setText("help");
      connect_layout->addWidget(help);

      robotStatus=new QPushButton;
      robotStatus->setText("robotStatus");
      connect_layout->addWidget(robotStatus);



            log=new QPushButton;
      log->setText("log");
      connect_layout->addWidget(log);

              other=new QPushButton;
            other->setText("other function");
      connect_layout->addWidget(other);
      coordinateDialog=new QFileDialog;
      connect_layout->addWidget(coordinateDialog);
      QVBoxLayout *topic_layout = new QVBoxLayout;
      topic_layout->addWidget( new QLabel( "angular of joints" ));
  topic_layout->addWidget( new QLabel( "joint1" ));

   QLjoint1 = new QLabel;
   topic_layout->addWidget(QLjoint1);

  topic_layout->addWidget( new QLabel( "joint2" ));
  QLjoint2 = new QLabel;
  topic_layout->addWidget(QLjoint2);

  topic_layout->addWidget( new QLabel( "joint3" ));
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

  //显示末端关节位姿的窗口
    QVBoxLayout *pose_layout = new QVBoxLayout;
    pose_layout->addWidget( new QLabel( "pose of the end effector" ));
     pose_layout->addWidget( new QLabel( "position X" ));
     Px= new QLabel;
     pose_layout->addWidget(Px);

      pose_layout->addWidget( new QLabel( "position Y" ));
     Py= new QLabel;
     pose_layout->addWidget(Py);

      pose_layout->addWidget( new QLabel( "position Z" ));
     Pz= new QLabel;
     pose_layout->addWidget(Pz);

          pose_layout->addWidget( new QLabel( "orientation X" ));
     Ox= new QLabel;
     pose_layout->addWidget(Ox);

      pose_layout->addWidget( new QLabel( "orientation Y" ));
     Oy= new QLabel;
     pose_layout->addWidget(Oy);

      pose_layout->addWidget( new QLabel( "orientation Z" ));
     Oz= new QLabel;
     pose_layout->addWidget(Oz);

      pose_layout->addWidget( new QLabel( "orientation W" ));
     Ow= new QLabel;
     pose_layout->addWidget(Ow);
   
    pose_layout->addWidget( new QLabel( "pitch" ));
     pitchAg= new QLabel;
     pose_layout->addWidget( pitchAg);

      pose_layout->addWidget( new QLabel( "roll" ));
     rollAg= new QLabel;
     pose_layout->addWidget(rollAg);

      pose_layout->addWidget( new QLabel( "yaw" ));
    yawAg= new QLabel;
     pose_layout->addWidget(yawAg);
   


  QHBoxLayout* layout = new QHBoxLayout;
  layout->addLayout( topic_layout );
  setLayout( layout );
   layout->addLayout( pose_layout );
  setLayout( layout );
  layout->addLayout( connect_layout );
  setLayout( layout );
  // 创建一个定时器，用来定时发布消息
  QTimer* output_timer = new QTimer( this );
  QTimer* tf_pose_timer =new QTimer(this);


  // 设置定时器的回调函数，按周期调用sendVel()
 connect(tf_pose_timer,SIGNAL(timeout()),this,SLOT(update_pose_value()));
  connect(output_timer, SIGNAL(timeout()), this, SLOT(update_joint_value()));
  // 设置定时器的周期，1s,不可设置的过小，一旦设置过小就会出现响应的问题，所以这里不能设置定时器的时间过短，否则容易出问题
  output_timer->start( 1000 );
  tf_pose_timer->start(50);

   ros::param::get("sim", sim);
   ROS_INFO("the sim is %d", sim);
   if (sim == true)
   {
     topicName = "jakaUr/joint_states";
   }
   else
   {
     topicName = "joint_states";
   }

    listener.waitForTransform("base_link", "link_6", ros::Time(), ros::Duration(1.0));
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
    jointSub = nh_.subscribe(topicName, 1000, &TeleopPanel::chatterCB, this);
}

void TeleopPanel::update_pose_value()
{
   

  if(nh_tf.ok())
    {
      try
      {
        tf::StampedTransform echo_transform;
        listener.lookupTransform("base_link", "link_6", ros::Time(), echo_transform);

        double yaw, pitch, roll;
        echo_transform.getBasis().getRPY(roll, pitch, yaw);
        tf::Quaternion q = echo_transform.getRotation();
        tf::Vector3 v = echo_transform.getOrigin();
        Px->setNum(v.getX());
        Py->setNum(v.getY());
        Pz->setNum(v.getZ());
        Ox->setNum(q.getX());
        Oy->setNum(q.getY());
        Oz->setNum(q.getZ());
        Ow->setNum(q.getW());
        pitchAg->setNum(pitch*180/PI);
        rollAg->setNum(roll*180/PI);
        yawAg->setNum(yaw*180/PI);
      }
      catch(tf::TransformException& ex)
      {
        std::cout << "Failure at "<< ros::Time::now() << std::endl;
        std::cout << "Exception thrown:" << ex.what()<< std::endl;
        std::cout << "The current list of frames is:" <<std::endl;
        std::cout << listener.allFramesAsString()<<std::endl;

      }
    }



}



} // end namespace rviz_teleop_commander

// 声明此类是一个rviz的插件
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(rviz_teleop_commander::TeleopPanel,rviz::Panel )
// END_TUTORIAL
