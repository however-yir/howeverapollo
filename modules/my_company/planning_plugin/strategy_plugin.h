/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#pragma once

#include <string>

namespace apollo {
namespace my_company {

struct PlanningContext {
  double requested_speed_mps = 0.0;
  bool obstacle_ahead = false;
  bool simulation_mode = true;
};

struct PlanningDecision {
  double speed_limit_mps = 0.0;
  std::string reason;
};

class StrategyPlugin {
 public:
  virtual ~StrategyPlugin() = default;

  virtual std::string Name() const = 0;
  virtual PlanningDecision Evaluate(const PlanningContext& context) const = 0;
};

}  // namespace my_company
}  // namespace apollo
