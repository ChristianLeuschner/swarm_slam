cmake_minimum_required(VERSION 3.8)
project(swarm_slam_core)

# --- 1. Compiler Setup (C++20 & Performance) ---
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -O3 -march=native)
endif()

# --- 2. find dependencies ---
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(pcl_conversions REQUIRED)

# extern SLAM Libraries
find_package(PCL REQUIRED)
find_package(Eigen3 REQUIRED)

# load g2o Modul
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(g2o REQUIRED)

# --- 3. include Directories ---
include_directories(
  include
  ${PCL_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${g2o_INCLUDE_DIRS}
)

# PCL Definitions (for processor flags)
add_definitions(${PCL_DEFINITIONS})
link_directories(${PCL_LIBRARY_DIRS})

# --- 4. Build Targets ---

# A. Library (Core Logic)
add_library(slam_core_lib
  src/slam_node.cpp
)
target_include_directories(slam_core_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
ament_target_dependencies(slam_core_lib
  rclcpp sensor_msgs pcl_conversions PCL Eigen3
)

# B. Executable
add_executable(slam_node src/main.cpp)
target_link_libraries(slam_node slam_core_lib)
ament_target_dependencies(slam_node rclcpp)

# --- 5. Install & Test ---
install(TARGETS slam_core_lib slam_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

ament_export_include_directories(include)
ament_export_dependencies(rclcpp sensor_msgs pcl_conversions PCL Eigen3 g2o)

ament_package()