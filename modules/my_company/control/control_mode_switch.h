/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#pragma once

namespace apollo {
namespace my_company {

enum class ControlRuntimeMode {
  kSimulation = 0,
  kRealVehicle = 1,
};

class ControlModeSwitch final {
 public:
  bool SetMode(ControlRuntimeMode mode);

  void UpdateSafetyCheckResult(bool passed);

  ControlRuntimeMode Mode() const;

  bool CanEngageAutonomy() const;

 private:
  ControlRuntimeMode mode_ = ControlRuntimeMode::kSimulation;
  bool safety_check_passed_ = false;
};

}  // namespace my_company
}  // namespace apollo
