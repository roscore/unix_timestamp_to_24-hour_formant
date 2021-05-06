#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Bool.h"

#include <sstream>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "pub_time");
	ros::NodeHandle nh;

	ros::Publisher unix_time_pub		= nh.advertise<std_msgs::Int32>("unix_time", 10);
	ros::Publisher utc_time_pub			= nh.advertise<std_msgs::String>("utc_time", 10);
	ros::Publisher kor_time_pub			= nh.advertise<std_msgs::String>("kor_time", 10);
	ros::Publisher kor_time_status_pub	= nh.advertise<std_msgs::Bool>("time_status", 10);

	ros::Rate loop_rate(100);

	while(ros::ok())
	{
		std_msgs::Int32 	unix_time_msg;
		std_msgs::String 	utc_time_msg;
		std_msgs::String 	kor_time_msg;
		std_msgs::Bool		kor_time_status_msg;

		int utc_time, utc_hour, kor_hour;
		bool kor_time_status;

		utc_time = ros::Time::now().toSec();

	    utc_hour = utc_time % 86400;
		kor_hour = utc_hour + 32400;	

		if(kor_hour > 43200)
		{
			ROS_INFO("PM || %d : %d : %d ", kor_hour / 3600, (kor_hour % 3600) / 60, kor_hour % 60);
			kor_time_status = true;
		}
		else
		{
			ROS_INFO("AM || %d : %d : %d ", kor_hour / 3600, (kor_hour % 3600) / 60, kor_hour % 60);
			kor_time_status = false;
		}

		unix_time_msg.data = utc_time;
		utc_time_msg.data = std::to_string(utc_hour / 3600) + " : " + std::to_string((utc_hour % 3600) / 60) + " : " + std::to_string(utc_hour % 60);
		kor_time_msg.data = std::to_string(kor_hour / 3600) + " : " + std::to_string((kor_hour % 3600) / 60) + " : " + std::to_string(kor_hour % 60);
		kor_time_status_msg.data = kor_time_status;
		
		unix_time_pub.publish(unix_time_msg);
		utc_time_pub.publish(utc_time_msg);
		kor_time_pub.publish(kor_time_msg);	
		kor_time_status_pub.publish(kor_time_status_msg);

		ros::spinOnce();

		loop_rate.sleep();
	}

	return 0;
}

