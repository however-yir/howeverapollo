/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#pragma once

#include <set>
#include <string>

namespace apollo {
namespace my_company {

class FaultInjectionSwitch final {
 public:
  void Enable(bool enable);

  void SetInjectableChannels(const std::set<std::string>& channels);

  bool ShouldInject(const std::string& channel) const;

  bool enabled() const { return enabled_; }

 private:
  bool enabled_ = false;
  std::set<std::string> injectable_channels_;
};

}  // namespace my_company
}  // namespace apollo
