#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <sensor_msgs/msg/joint_state.hpp>

class DiffDriveController : public rclcpp::Node
{
public:
    DiffDriveController() : Node("diff_drive_controller")
    {
        cmd_vel_subscriber_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel", 10, std::bind(&DiffDriveController::cmdVelCallback, this, std::placeholders::_1));

        joint_state_publisher_ = this->create_publisher<sensor_msgs::msg::JointState>("/joint_states", 10);

        odom_publisher_ = this->create_publisher<nav_msgs::msg::Odometry>("/odom", 10);

        RCLCPP_INFO(this->get_logger(), "Differential Drive Controller Node Started");
    }

private:
    void cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg)
    {
        double linear_x = msg->linear.x;
        double angular_z = msg->angular.z;

        // Simulate wheel motion based on velocity commands
        sensor_msgs::msg::JointState joint_state;
        joint_state.header.stamp = this->get_clock()->now();
        joint_state.name = {"left_wheel_joint", "right_wheel_joint"};
        joint_state.position = {linear_x - angular_z, linear_x + angular_z};
        joint_state_publisher_->publish(joint_state);

        // Publish Odometry
        nav_msgs::msg::Odometry odom;
        odom.header.stamp = this->get_clock()->now();
        odom.header.frame_id = "odom";
        odom.child_frame_id = "base_link";
        odom.twist.twist.linear.x = linear_x;
        odom.twist.
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <sensor_msgs/msg/joint_state.hpp>

class DiffDriveController : public rclcpp::Node
{
public:
    DiffDriveController() : Node("diff_drive_controller")
    {
        cmd_vel_subscriber_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel", 10, std::bind(&DiffDriveController::cmdVelCallback, this, std::placeholders::_1));

        joint_state_publisher_ = this->create_publisher<sensor_msgs::msg::JointState>("/joint_states", 10);

        odom_publisher_ = this->create_publisher<nav_msgs::msg::Odometry>("/odom", 10);

        RCLCPP_INFO(this->get_logger(), "Differential Drive Controller Node Started");
    }

private:
    void cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg)
    {
        double linear_x = msg->linear.x;
        double angular_z = msg->angular.z;

        // Simulate wheel motion based on velocity commands
        sensor_msgs::msg::JointState joint_state;
        joint_state.header.stamp = this->get_clock()->now();
        joint_state.name = {"left_wheel_joint", "right_wheel_joint"};
        joint_state.position = {linear_x - angular_z, linear_x + angular_z};
        joint_state_publisher_->publish(joint_state);

        // Publish Odometry
        nav_msgs::msg::Odometry odom;
        odom.header.stamp = this->get_clock()->now();
        odom.header.frame_id = "odom";
        odom.child_frame_id = "base_link";
        odom.twist.twist.linear.x = linear_x;
        odom.twist.

