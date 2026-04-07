/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#include "modules/my_company/planning_plugin/rule_based_strategy_plugin.h"

#include <algorithm>

namespace apollo {
namespace my_company {

std::string RuleBasedStrategyPlugin::Name() const { return "rule_based_v1"; }

PlanningDecision RuleBasedStrategyPlugin::Evaluate(
    const PlanningContext& context) const {
  PlanningDecision decision;

  if (context.obstacle_ahead) {
    decision.speed_limit_mps = 0.0;
    decision.reason = "Obstacle ahead";
    return decision;
  }

  const double env_limit = context.simulation_mode ? 6.0 : 12.0;
  decision.speed_limit_mps = std::max(0.0, std::min(context.requested_speed_mps, env_limit));
  decision.reason = context.simulation_mode ? "Simulation speed limit" : "Real vehicle speed limit";
  return decision;
}

}  // namespace my_company
}  // namespace apollo
