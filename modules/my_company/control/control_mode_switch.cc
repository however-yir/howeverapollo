/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#include "modules/my_company/control/control_mode_switch.h"

namespace apollo {
namespace my_company {

bool ControlModeSwitch::SetMode(ControlRuntimeMode mode) {
  mode_ = mode;
  return true;
}

void ControlModeSwitch::UpdateSafetyCheckResult(bool passed) {
  safety_check_passed_ = passed;
}

ControlRuntimeMode ControlModeSwitch::Mode() const { return mode_; }

bool ControlModeSwitch::CanEngageAutonomy() const {
  if (mode_ == ControlRuntimeMode::kSimulation) {
    return true;
  }
  return safety_check_passed_;
}

}  // namespace my_company
}  // namespace apollo
