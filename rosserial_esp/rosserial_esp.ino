/*
 * rosserial Publisher Example
 * Prints "hello world!"
 * This intend to connect to a Wifi Access Point
 * and a rosserial socket server.
 * You can launch the rosserial socket server with
 * roslaunch rosserial_server socket.launch
 * The default port is 11411
 *
 */
// #include <ESP8266WiFi.h>
#include "WiFi.h"
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32MultiArray.h>

const char* ssid     = "Tselhome-5423";
const char* password = "71531656";
// Set the rosserial socket server IP address
IPAddress server(192,168,0,64);
// Set the rosserial socket server port
const uint16_t serverPort = 11411;

ros::NodeHandle nh;
// Make a chatter publisher
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

// Subscriber and callback function
void wheelVelCmdCb(const std_msgs::Float32MultiArray& wheel_velocities_command);
ros::Subscriber<std_msgs::Float32MultiArray> wheel_vel_sub("/wheel_vel_cmd", &wheelVelCmdCb);

// Be polite and say hello
char hello[13] = "hello world!";


