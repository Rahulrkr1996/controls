#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "controls/SetSpeed.h"

ros::NodeHandle *n;
ros::ServiceClient *client;

void commandStearingAngleCallback(const std_msgs::Float64::ConstPtr& msg) {
	controls::SetSpeed srv;
	
	int angle = int(msg->data);
	ROS_INFO("Received angle : %d", angle);
	srv.request.stearing_angle = msg->data ;

	if (client->call(srv))
	{
		ROS_INFO("Stearing target set to : %ld", (long int)srv.request.stearing_angle);
		ROS_INFO("Response : %ld", (long int)srv.response.code);
	}
	else
	{
		ROS_ERROR("Failed to call service set speed");
		ROS_INFO("Response : %ld", (long int)srv.response.code);
		return;
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "command_subscriber_motor_controller_client");
	
	ros::NodeHandle n1;
	n = &n1;
	
	ros::ServiceClient serviceClient = n->serviceClient<controls::SetSpeed>("motor_controller");
	
	client = &serviceClient;
    
    ros::Subscriber sub = n->subscribe("alpha_val_manipulated", 1, commandStearingAngleCallback);
    
    ros::spin();
    
    return 0;
}
