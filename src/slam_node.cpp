#include "swarm_slam_core/slam_node.hpp"

#include <pcl_conversions/pcl_conversions.h>

namespace swarm_slam {

SlamNode::SlamNode() : Node("swarm_slam_node"), current_cloud_(new pcl::PointCloud<pcl::PointXYZ>) {
    // allow renaming of topic name and giving default value
    this->declare_parameter<std::string>("lidar_topic", "/lidar_packets");

    std::string lidar_topic_name;
    this->get_parameter("lidar_topic", lidar_topic_name);

    // definition of quality of service -> best effort (only newest messages are relevant)
    // rclcpp::QoS qos_profile = rclcpp::SensorDataQoS();
    rclcpp::QoS qos_profile(10);

    // subscription to lidar topic
    lidar_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        lidar_topic_name, qos_profile,
        std::bind(&SlamNode::lidar_callback, this, std::placeholders::_1));
};

void SlamNode::lidar_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg) {
    if (msg->data.empty()) {
        RCLCPP_WARN(this->get_logger(), "Received empty PointCloud2 message.");
        return;
    }

    // convert ROS PointCloud2 message to PCL PointCloud
    pcl::fromROSMsg(*msg, *current_cloud_);

    // debug check if conversion was successful
    if (!current_cloud_->empty()) {
        RCLCPP_INFO_ONCE(this->get_logger(),
                         "First point cloud converted! points: %zu, Frame-ID: %s",
                         current_cloud_->size(), msg->header.frame_id.c_str());
    }
}

}  // namespace swarm_slam
