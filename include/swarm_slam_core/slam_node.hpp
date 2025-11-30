#pragma once

#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>


namespace swarm_slam {
    /**
     * @brief SLAM Node class
     * It receives ROS messages, processes them, and manages the SLAM algorithm.
     */

    class SlamNode : public rclcpp::Node {
        public:
            explicit SlamNode();
            ~SlamNode() override = default;

        private:
            // --- Callbacks ---
            void lidar_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);

            // --- ROS Interfaces ---
            rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr lidar_sub_;

            // --- internal memory ---
            pcl::PointCloud<pcl::PointXYZ>::Ptr current_cloud_;

    };
}