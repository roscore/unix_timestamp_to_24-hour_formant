#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"

#include <sstream>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "pub_time");
	ros::NodeHandle nh;

	ros::Publisher time_pub = nh.advertise<std_msgs::Int32>("sys_time", 10);

	ros::Rate loop_rate(100);

	while(ros::ok())
	{
		std_msgs::Int32 msg;
		
		int now_time, now_hour, kor_hour;

		now_time = ros::Time::now().toSec();
	        now_hour = now_time % 86400;
		kor_hour = now_hour + 32400;	

		msg.data = kor_hour;
		
		if(msg.data > 43200)	ROS_INFO("PM || %d : %d : %d ", kor_hour / 3600, (kor_hour % 3600) / 60, kor_hour % 60);
		else			ROS_INFO("AM || %d : %d : %d ", kor_hour / 3600, (kor_hour % 3600) / 60, kor_hour % 60);	
		time_pub.publish(msg);	

		ros::spinOnce();

		loop_rate.sleep();
	}

	return 0;
}

