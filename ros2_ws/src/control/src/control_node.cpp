#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "kinematics/differential_drive.h"
#include "std_msgs/msg/float64_multi_array.hpp"

using namespace std::chrono_literals;

DifferentialDrive diff_drive = DifferentialDrive();

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class Control : public rclcpp::Node
{
public:
  Control()
      : Node("control"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    wheel_velocity_command_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("wheel_velocity_command", 10);
    
    twist_command_subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
        "cmd_vel", 10, std::bind(&Control::twist_command_callback, this, std::placeholders::_1));
    timer_ = this->create_wall_timer(
        500ms, std::bind(&Control::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    message.data = "Hello, world! " + std::to_string(count_++);
    // RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
  }
  
  void twist_command_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%f %f %f'", msg->linear.x ,
                msg->linear.y, msg->angular.z
      );
    // static double wheel_velocity[2];
    double* wheel_velocity;
    wheel_velocity = diff_drive.computeWheelVelocities(msg->linear.x, msg->linear.y, msg->angular.z);

    RCLCPP_INFO(this->get_logger(), "Left wheel velocity: '%f'", wheel_velocity[0]);
    // RCLCPP_INFO(this->get_logger(), "Left wheel velocity: '%f'",diff_drive.computeWheelVelocities(msg->linear.x, msg->linear.y, msg->angular.z) [0]);
    auto message = std_msgs::msg::Float64MultiArray();
    message.data = {wheel_velocity[0], wheel_velocity[1]};
    wheel_velocity_command_publisher_->publish(message);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr wheel_velocity_command_publisher_;
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr twist_command_subscription_;
  size_t count_;
};

int main(int argc, char *argv[])
{

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Control>());
  rclcpp::shutdown();
  return 0;
}