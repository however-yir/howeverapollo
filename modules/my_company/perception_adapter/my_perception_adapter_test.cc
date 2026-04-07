/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#include "modules/my_company/perception_adapter/my_perception_adapter.h"

#include <memory>

#include "gtest/gtest.h"

namespace apollo {
namespace my_company {

namespace {

class UnitTestVendorAdapter final : public SensorAdapter {
 public:
  std::string VendorName() const override { return "unit_vendor"; }

  bool Decode(const std::string& raw_payload,
              SensorFrame* unified_frame) const override {
    if (unified_frame == nullptr || raw_payload != "ok") {
      return false;
    }
    unified_frame->timestamp_sec = 42.0;
    unified_frame->numeric_fields["object_count"] = 7.0;
    return true;
  }
};

}  // namespace

TEST(MyPerceptionAdapterTest, IngestsFromRegisteredVendor) {
  auto& registry = SensorAdapterRegistry::Instance();
  registry.ClearForTest();
  ASSERT_TRUE(
      registry.Register(std::unique_ptr<SensorAdapter>(new UnitTestVendorAdapter())));

  MyPerceptionAdapter adapter(&registry);
  PerceptionObservation observation;

  EXPECT_TRUE(adapter.IngestVendorPayload("unit_vendor", "ok", &observation));
  EXPECT_TRUE(observation.valid);
  EXPECT_EQ(observation.obstacle_count, 7);
  EXPECT_DOUBLE_EQ(observation.timestamp_sec, 42.0);
}

TEST(MyPerceptionAdapterTest, RejectsUnknownVendor) {
  auto& registry = SensorAdapterRegistry::Instance();
  registry.ClearForTest();

  MyPerceptionAdapter adapter(&registry);
  PerceptionObservation observation;
  EXPECT_FALSE(adapter.IngestVendorPayload("missing_vendor", "ok", &observation));
}

}  // namespace my_company
}  // namespace apollo
