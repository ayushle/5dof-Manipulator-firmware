#include <Arduino.h>
#include <control.h>
#include <ros.h>
#include <std_msgs/Int16.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>

//psotions of each link
std_msgs::Float32 LINK1_currentPosition;
std_msgs::Float32 LINK2_currentPosition;
std_msgs::Float32 LINK3_currentPosition;
std_msgs::Float32 LINK4_currentPosition;
std_msgs::Float32 LINK5_currentPosition;
std_msgs::Float32 LINK6_currentPosition;


ros::NodeHandle nh;

//controls for all the links
void controlLink1(const std_msgs::Int16& cmd_msg1)
{
  if (cmd_msg1.data>0)
    Link1.rotateAntiClockwise(cmd_msg1.data);
  else if(cmd_msg1.data<0)
    Link1.rotateClockwise(abs(cmd_msg1.data));
  else
    Link1.stop();
}

void controlLink2(const std_msgs::Int16& cmd_msg2)
{
  if (cmd_msg2.data>0)
    Link2.increaseLength();
  else if(cmd_msg2.data<0)
    Link2.decreaseLength();
  else
    Link2.stop();
}

void controlLink3(const std_msgs::Int16& cmd_msg3)
{
  if (cmd_msg3.data>0)
    Link3.increaseLength();
  else if(cmd_msg3.data<0)
    Link3.decreaseLength();
  else
    Link3.stop();
}

void controlLink4(const std_msgs::Int16& cmd_msg4)
{
  if (cmd_msg4.data>0)
    Link4.rotateAntiClockwise(cmd_msg4.data);
  else if(cmd_msg4.data<0)
    Link4.rotateClockwise(abs(cmd_msg4.data));
  else
    Link4.stop();
}


void controlLink5(const std_msgs::Int16& cmd_msg5)
{
  if (cmd_msg5.data>0)
    Link5.rotateAntiClockwise(cmd_msg5.data);
  else if(cmd_msg5.data<0)
    Link5.rotateClockwise(abs(cmd_msg5.data));
  else
    Link5.stop();
}

void controlLink6(const std_msgs::Int16& cmd_msg6)
{
  if (cmd_msg6.data>0)
    Link6.rotateAntiClockwise(cmd_msg6.data);
  else if(cmd_msg6.data<0)
    Link6.rotateClockwise(abs(cmd_msg6.data));
  else
    Link6.stop();
}


ros::Subscriber<std_msgs::Int16> sub1("/link1", controlLink1);
ros::Subscriber<std_msgs::Int16> sub2("/link2", controlLink2);
ros::Subscriber<std_msgs::Int16> sub3("/link3", controlLink3);
ros::Subscriber<std_msgs::Int16> sub4("/link4", controlLink4);
ros::Subscriber<std_msgs::Int16> sub5("/link5", controlLink5);
ros::Subscriber<std_msgs::Int16> sub6("/link6", controlLink6);


ros::Publisher LINK1_currentPosition_pub1("LINK1_currentPosition", &LINK1_currentPosition);
ros::Publisher LINK2_currentPosition_pub2("LINK2_currentPosition", &LINK2_currentPosition);
ros::Publisher LINK3_currentPosition_pub3("LINK3_currentPosition", &LINK3_currentPosition);
ros::Publisher LINK4_currentPosition_pub4("LINK4_currentPosition", &LINK4_currentPosition);
ros::Publisher LINK5_currentPosition_pub5("LINK5_currentPosition", &LINK5_currentPosition);
ros::Publisher LINK6_currentPosition_pub6("LINK6_currentPosition", &LINK6_currentPosition);

// void emg_stop()
// {
//   Link1.stop();
//   Link2.stop();
//   Link3.stop();
//   Link4.stop();
//   Link5.stop();
//   Link6.stop();
// }

void enc1Fun()
{
  encLink1.updateEncoder();
}
void enc2Fun()
{
  encLink2.updateEncoder();
}
void enc3Fun()
{
  encLink3.updateEncoder();
}
void enc4Fun()
{
  encLink4.updateEncoder();
}
void enc5Fun()
{
  encLink5.updateEncoder();
}
void enc6Fun()
{
  encLink6.updateEncoder();
}


void setup() {
  intial_setup();
  attachInterrupt(digitalPinToInterrupt(encA1),enc1Fun, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encB1),enc1Fun, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encA2),enc2Fun, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encB2),enc2Fun, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encA3),enc3Fun, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encB3),enc3Fun, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encA4),enc4Fun, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encB4),enc4Fun, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encA5),enc5Fun, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encB5),enc5Fun, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encA6),enc6Fun, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encB6),enc6Fun, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(limit), emg_stop, LOW);
  nh.initNode();
  nh.advertise(LINK1_currentPosition_pub1);
  nh.advertise(LINK2_currentPosition_pub2);
  nh.advertise(LINK3_currentPosition_pub3);
  nh.advertise(LINK4_currentPosition_pub4);
  nh.advertise(LINK5_currentPosition_pub5);
  nh.advertise(LINK6_currentPosition_pub6);

  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
  nh.subscribe(sub5);
  nh.subscribe(sub6);
}


void loop() {
  nh.spinOnce();
  if(nh.connected()){
    LINK1_currentPosition.data = encLink1.encoderValue;
    LINK1_currentPosition_pub1.publish(&LINK1_currentPosition);
    LINK2_currentPosition.data = encLink2.encoderValue;
    LINK2_currentPosition_pub2.publish(&LINK2_currentPosition);
    LINK3_currentPosition.data = encLink3.encoderValue;
    LINK3_currentPosition_pub3.publish(&LINK3_currentPosition);
    LINK4_currentPosition.data = encLink4.encoderValue;
    LINK4_currentPosition_pub4.publish(&LINK4_currentPosition);
    LINK5_currentPosition.data = encLink5.encoderValue;
    LINK5_currentPosition_pub5.publish(&LINK5_currentPosition);
    LINK6_currentPosition.data = encLink6.encoderValue;
    LINK6_currentPosition_pub6.publish(&LINK6_currentPosition);
  }
  delay(10);
}
