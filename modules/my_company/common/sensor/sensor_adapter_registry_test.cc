/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#include "modules/my_company/common/sensor/sensor_adapter_registry.h"

#include <memory>
#include <string>

#include "gtest/gtest.h"

namespace apollo {
namespace my_company {

namespace {

class DemoVendorAdapter final : public SensorAdapter {
 public:
  std::string VendorName() const override { return "demo_vendor"; }

  bool Decode(const std::string& raw_payload,
              SensorFrame* unified_frame) const override {
    if (unified_frame == nullptr || raw_payload.empty()) {
      return false;
    }
    unified_frame->sensor_id = "demo_lidar";
    unified_frame->timestamp_sec = 123.45;
    unified_frame->numeric_fields["object_count"] = 4.0;
    return true;
  }
};

}  // namespace

TEST(SensorAdapterRegistryTest, RegisterAndLookupWorks) {
  auto& registry = SensorAdapterRegistry::Instance();
  registry.ClearForTest();

  EXPECT_TRUE(registry.Register(std::unique_ptr<SensorAdapter>(
      new DemoVendorAdapter())));
  EXPECT_FALSE(registry.Register(std::unique_ptr<SensorAdapter>(
      new DemoVendorAdapter())));

  const SensorAdapter* adapter = registry.Get("demo_vendor");
  ASSERT_NE(adapter, nullptr);

  SensorFrame frame;
  EXPECT_TRUE(adapter->Decode("raw", &frame));
  EXPECT_EQ(frame.sensor_id, "demo_lidar");
  EXPECT_DOUBLE_EQ(frame.numeric_fields["object_count"], 4.0);
}

}  // namespace my_company
}  // namespace apollo
