#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/PointCloud2.h"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/ros/conversions.h>
#include <pcl/PCLPointCloud2.h>
#include "pcl_conversions/pcl_conversions.h"

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void streamCallback(const sensor_msgs::PointCloud2& cloud_ros) {
  pcl::PCLPointCloud2 cloud_temp;
  pcl::PointCloud<pcl::PointXYZRGBA> cloud_final;  
  pcl_conversions::toPCL(cloud_ros, cloud_temp);
  pcl::fromPCLPointCloud2(cloud_temp, cloud_final);
  ROS_INFO("I received a point cloud...");
  pcl::io::savePCDFileASCII("test_cloud.pcd", cloud_final);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/rgbdslam/batch_clouds", 1000, streamCallback);
  ros::spin();
  return 0;
}
