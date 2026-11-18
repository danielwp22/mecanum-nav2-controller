#include <gtest/gtest.h>

#include "nav2_core/controller.hpp"
#include "pluginlib/class_loader.hpp"

TEST(PluginRegistration, LoadsOmniPursuitController)
{
  pluginlib::ClassLoader<nav2_core::Controller> loader(
    "nav2_core", "nav2_core::Controller");
  auto controller = loader.createSharedInstance(
    "nav2_omni_pursuit_controller::OmniPursuitController");
  ASSERT_NE(controller, nullptr);
}
