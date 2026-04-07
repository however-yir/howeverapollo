/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#include "modules/my_company/control/control_mode_switch.h"
#include "modules/my_company/control/fault_injection_switch.h"

#include <set>
#include <string>

#include "gtest/gtest.h"

namespace apollo {
namespace my_company {

TEST(ControlModeSwitchTest, SupportsSimulationAndRealVehicleModes) {
  ControlModeSwitch mode_switch;
  EXPECT_EQ(mode_switch.Mode(), ControlRuntimeMode::kSimulation);
  EXPECT_TRUE(mode_switch.CanEngageAutonomy());

  mode_switch.SetMode(ControlRuntimeMode::kRealVehicle);
  EXPECT_FALSE(mode_switch.CanEngageAutonomy());

  mode_switch.UpdateSafetyCheckResult(true);
  EXPECT_TRUE(mode_switch.CanEngageAutonomy());
}

TEST(ControlModeSwitchTest, FaultInjectionCanBeGatedPerChannel) {
  FaultInjectionSwitch fi_switch;
  fi_switch.Enable(true);
  fi_switch.SetInjectableChannels(std::set<std::string>{
      "/apollo/perception/obstacles", "/apollo/control",
  });

  EXPECT_TRUE(fi_switch.ShouldInject("/apollo/control"));
  EXPECT_FALSE(fi_switch.ShouldInject("/apollo/localization/pose"));

  fi_switch.Enable(false);
  EXPECT_FALSE(fi_switch.ShouldInject("/apollo/control"));
}

}  // namespace my_company
}  // namespace apollo
