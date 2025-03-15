#pragma once

#include <mc_rbdyn/RobotModuleMacros.h>
#include <mc_rtc/logging.h>
#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

// #include <mc_rbdyn_urdf/urdf.h>

#include <mc_robots/api.h>

namespace mc_robots
{

struct MC_ROBOTS_DLLAPI TalosCommonRobotModule : public mc_rbdyn::RobotModule
{
public:
  TalosCommonRobotModule();

protected:
  void setupCommon();
  void findConvexes(const std::string &convexPath);

public:
  std::vector<std::string> virtualLinks;
  std::vector<std::string> gripperLinks;
  // mc_rbdyn_urdf::Limits limits;
};

struct MC_ROBOTS_DLLAPI TalosSkeletonRobotModule : public TalosCommonRobotModule
{
public:
  TalosSkeletonRobotModule(bool fixed);
};

struct MC_ROBOTS_DLLAPI TalosRobotModule : public TalosCommonRobotModule
{
public:
 TalosRobotModule(bool fixed);
};

} // namespace mc_robots

extern "C"
{
  ROBOT_MODULE_API void MC_RTC_ROBOT_MODULE(std::vector<std::string> & names)
  {
    names = {"Talos"};
  }
  ROBOT_MODULE_API void destroy(mc_rbdyn::RobotModule * ptr)
  {
    delete ptr;
  }
  ROBOT_MODULE_API mc_rbdyn::RobotModule * create(const std::string & n)
  {
    ROBOT_MODULE_CHECK_VERSION("Talos")
    if(n == "Talos")
    {
      return new mc_robots::TalosRobotModule(false);
    }
    if(n == "TalosFixed")
    {
      return new mc_robots::TalosRobotModule(false);
    }
    else
    {
      mc_rtc::log::error("Talos module Cannot create an object of type {}", n);
      return nullptr;
    }
  }
}
