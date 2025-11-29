cmake_minimum_required(VERSION 3.8)
project(swarm_slam_core)

# --- 1. Compiler Setup (C++20 & Performance) ---
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -O3 -march=native)
endif()

# --- 2. Dependencies finden ---
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(pcl_conversions REQUIRED)

# Externe SLAM Libraries
find_package(PCL REQUIRED)
find_package(Eigen3 REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(g2o REQUIRED)

# --- 3. Include Directories ---
include_directories(
  include
  ${PCL_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${g2o_INCLUDE_DIRS}
)

# PCL Definitions (wichtig für Processor-Flags)
add_definitions(${PCL_DEFINITIONS})
link_directories(${PCL_LIBRARY_DIRS})

# --- 4. Build Targets (Aktuell noch leer) ---
# Hier fügen wir später die Library und Executables hinzu.

# --- 5. Install & Test ---
ament_export_include_directories(include)
ament_export_dependencies(rclcpp sensor_msgs pcl_conversions PCL Eigen3 g2o)

ament_package()