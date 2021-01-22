#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include <stdio.h>

float linear = 0.0, angular = 0.0;
float radius = 0.508;
float width  = 0.203;

void twistCB(const geometry_msgs::Twist::ConstPtr &msg)
{
    linear = msg->linear.x;
    angular= msg->angular.z;
}
int main( int argc, char **argv)
{
    ros::init(argc, argv, "twist_to_gz");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<geometry_msgs::Twist>("twist", 100, twistCB);
    ros::Publisher front_right = nh.advertise<std_msgs::Float64>("/rom1/front_right_wheel_controller/command", 100);
    ros::Publisher front_left  = nh.advertise<std_msgs::Float64>("/rom1/front_left_wheel_controller/command", 100);
    ros::Publisher back_right  = nh.advertise<std_msgs::Float64>("/rom1/back_right_wheel_controller/command", 100);
    ros::Publisher back_left   = nh.advertise<std_msgs::Float64>("/rom1/back_left_wheel_controller/command", 100);

    ros::Rate timer(5);
    std_msgs::Float64 right_wheels_velocity;
    std_msgs::Float64 left_wheels_velocity;

    while(ros::ok())
    {
        right_wheels_velocity.data = (2 * linear + angular * width) / (2*radius);
        left_wheels_velocity.data  = (2 * linear - angular * width) / (2*radius);
        front_right.publish(right_wheels_velocity);
        front_left.publish(left_wheels_velocity);
        back_right.publish(right_wheels_velocity);
        back_left.publish(left_wheels_velocity);

        ROS_INFO_STREAM("Right wheel = "<< right_wheels_velocity.data << "Left wheel = "<< left_wheels_velocity.data);
        ros::spinOnce();
        timer.sleep();
    }
}

