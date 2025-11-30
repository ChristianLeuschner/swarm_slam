#include <rclcpp/rclcpp.hpp>

#include "swarm_slam_core/slam_node.hpp"

int main(int argc, char** argv) {
    // 1. initialize ROS 2
    rclcpp::init(argc, argv);

    // 2. create our node
    auto node = std::make_shared<swarm_slam::SlamNode>();

    // 3. start executor
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);

    // 4. spinning loop
    executor.spin();

    // 5. clean shutdown
    rclcpp::shutdown();
    return 0;
}