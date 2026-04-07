/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#include "modules/my_company/control/fault_injection_switch.h"

namespace apollo {
namespace my_company {

void FaultInjectionSwitch::Enable(bool enable) { enabled_ = enable; }

void FaultInjectionSwitch::SetInjectableChannels(
    const std::set<std::string>& channels) {
  injectable_channels_ = channels;
}

bool FaultInjectionSwitch::ShouldInject(const std::string& channel) const {
  if (!enabled_) {
    return false;
  }
  return injectable_channels_.find(channel) != injectable_channels_.end();
}

}  // namespace my_company
}  // namespace apollo
