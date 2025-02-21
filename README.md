Differential Drive Robot Controller

Overview

A ROS 2 package for differential drive control and waypoint navigation using PID.

Installation

cd ~/acceleration_ws/src
git clone <repository-url>
cd ~/acceleration_ws
colcon build --packages-select diff_drive
source install/setup.bash

Usage

Run the Controller

ros2 run diff_drive diff_drive_controller

Publish Velocity Commands

ros2 topic pub /cmd_vel geometry_msgs/Twist '{linear: {x: 0.5}, angular: {z: 0.2}}'

Run Waypoint Navigation

ros2 run diff_drive waypoint_navigation.py --ros-args \
-p waypoint_1_x:=2.0 -p waypoint_1_y:=1.0 -p waypoint_2_x:=4.0 -p waypoint_2_y:=3.0

Launch Gazebo Simulation

ros2 launch diff_drive launch_sim.launch.py

Testing

Verify RPM output with ros2 topic echo.

Monitor navigation using /odom.

Tune PID for smooth movement.

License

MIT License

Contributors

Ashwin Sivakumar P

