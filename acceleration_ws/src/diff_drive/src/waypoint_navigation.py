import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
import math
import time

class WaypointNavigation(Node):
    def __init__(self):
        super().__init__('waypoint_navigation')
        self.publisher_ = self.create_publisher(Twist, '/cmd_vel', 10)
        self.subscription = self.create_subscription(Odometry, '/odom', self.odom_callback, 10)
        
        self.current_x = 0.0
        self.current_y = 0.0
        self.waypoints = [(2.0, 2.0), (4.0, 0.0), (0.0, 0.0)]  # Define waypoints (x, y)
        self.current_waypoint_index = 0
        self.tolerance = 0.1

        time.sleep(2)  # Wait for ROS 2 initialization
        self.navigate_to_waypoints()

    def odom_callback(self, msg):
        self.current_x = msg.pose.pose.position.x
        self.current_y = msg.pose.pose.position.y

    def navigate_to_waypoints(self):
        while rclpy.ok() and self.current_waypoint_index < len(self.waypoints):
            target_x, target_y = self.waypoints[self.current_waypoint_index]
            self.get_logger().info(f"Moving to waypoint: {target_x}, {target_y}")

            while not self.reached_waypoint(target_x, target_y):
                cmd_vel = Twist()
                cmd_vel.linear.x = 0.3  # Move forward
                cmd_vel.angular.z = 0.0  # No rotation
                self.publisher_.publish(cmd_vel)
                time.sleep(0.1)

            self.current_waypoint_index += 1

        self.stop_robot()

    def reached_waypoint(self, target_x, target_y):
        distance = math.sqrt((target_x - self.current_x)**2 + (target_y - self.current_y)**2)
        return distance < self.tolerance

    def stop_robot(self):
        cmd_vel = Twist()
        cmd_vel.linear.x = 0.0
        cmd_vel.angular.z = 0.0
        self.publisher_.publish(cmd_vel)
        self.get_logger().info("Navigation complete!")

def main(args=None):
    rclpy.init(args=args)
    waypoint_navigation = WaypointNavigation()
    rclpy.spin(waypoint_navigation)
    waypoint_navigation.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

