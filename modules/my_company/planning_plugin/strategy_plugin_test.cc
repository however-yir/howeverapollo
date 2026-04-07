/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#include "modules/my_company/planning_plugin/rule_based_strategy_plugin.h"
#include "modules/my_company/planning_plugin/strategy_plugin_manager.h"

#include <memory>

#include "gtest/gtest.h"

namespace apollo {
namespace my_company {

TEST(StrategyPluginTest, RuleBasedPluginCanBeLoadedAndEvaluated) {
  StrategyPluginManager manager;
  ASSERT_TRUE(
      manager.Register(std::unique_ptr<StrategyPlugin>(new RuleBasedStrategyPlugin())));

  PlanningDecision free_road = manager.Evaluate(
      "rule_based_v1", PlanningContext{10.0, false, true});
  EXPECT_DOUBLE_EQ(free_road.speed_limit_mps, 6.0);

  PlanningDecision blocked = manager.Evaluate(
      "rule_based_v1", PlanningContext{10.0, true, false});
  EXPECT_DOUBLE_EQ(blocked.speed_limit_mps, 0.0);
  EXPECT_EQ(blocked.reason, "Obstacle ahead");
}

TEST(StrategyPluginTest, UnknownPluginReturnsFallbackDecision) {
  StrategyPluginManager manager;
  PlanningDecision decision = manager.Evaluate("missing", PlanningContext{});
  EXPECT_DOUBLE_EQ(decision.speed_limit_mps, 0.0);
  EXPECT_EQ(decision.reason, "Plugin not found");
}

}  // namespace my_company
}  // namespace apollo
