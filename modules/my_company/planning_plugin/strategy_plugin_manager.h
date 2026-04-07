/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#pragma once

#include <map>
#include <memory>
#include <string>

#include "modules/my_company/planning_plugin/strategy_plugin.h"

namespace apollo {
namespace my_company {

class StrategyPluginManager final {
 public:
  bool Register(std::unique_ptr<StrategyPlugin> plugin);

  PlanningDecision Evaluate(const std::string& plugin_name,
                            const PlanningContext& context) const;

 private:
  std::map<std::string, std::unique_ptr<StrategyPlugin>> plugins_;
};

}  // namespace my_company
}  // namespace apollo
