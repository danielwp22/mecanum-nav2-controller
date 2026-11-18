cmake_minimum_required(VERSION 3.8)
project(omni_pursuit_controller)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(nav2_common REQUIRED)
find_package(nav2_core REQUIRED)
find_package(nav2_costmap_2d REQUIRED)
find_package(nav2_util REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(pluginlib REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

nav2_package()

include_directories(
  include
)

set(dependencies
  rclcpp
  rclcpp_lifecycle
  geometry_msgs
  nav2_costmap_2d
  pluginlib
  nav_msgs
  nav2_util
  nav2_core
  tf2
  tf2_ros
  tf2_geometry_msgs
)

add_library(omni_pursuit_controller SHARED
        src/omni_pursuit_controller.cpp)

# prevent pluginlib from using boost
target_compile_definitions(omni_pursuit_controller PUBLIC "PLUGINLIB__DISABLE_BOOST_FUNCTIONS")

ament_target_dependencies(omni_pursuit_controller
  ${dependencies}
)

install(TARGETS omni_pursuit_controller
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY include/
  DESTINATION include/
)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(test_plugin_load test/test_plugin_load.cpp)
  ament_target_dependencies(test_plugin_load ${dependencies})
endif()

install(DIRECTORY config DESTINATION share/${PROJECT_NAME})

ament_export_include_directories(include)
ament_export_libraries(omni_pursuit_controller)
ament_export_dependencies(${dependencies})

pluginlib_export_plugin_description_file(nav2_core omni_pursuit_controller_plugin.xml)

ament_package()
