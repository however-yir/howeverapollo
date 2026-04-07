/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#include "modules/my_company/planning_plugin/strategy_plugin_manager.h"

namespace apollo {
namespace my_company {

bool StrategyPluginManager::Register(std::unique_ptr<StrategyPlugin> plugin) {
  if (plugin == nullptr) {
    return false;
  }
  const std::string name = plugin->Name();
  if (name.empty()) {
    return false;
  }
  auto inserted = plugins_.emplace(name, std::move(plugin));
  return inserted.second;
}

PlanningDecision StrategyPluginManager::Evaluate(
    const std::string& plugin_name, const PlanningContext& context) const {
  auto iter = plugins_.find(plugin_name);
  if (iter == plugins_.end()) {
    return PlanningDecision{0.0, "Plugin not found"};
  }
  return iter->second->Evaluate(context);
}

}  // namespace my_company
}  // namespace apollo
