/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#pragma once

#include "modules/my_company/planning_plugin/strategy_plugin.h"

namespace apollo {
namespace my_company {

class RuleBasedStrategyPlugin final : public StrategyPlugin {
 public:
  std::string Name() const override;
  PlanningDecision Evaluate(const PlanningContext& context) const override;
};

}  // namespace my_company
}  // namespace apollo
