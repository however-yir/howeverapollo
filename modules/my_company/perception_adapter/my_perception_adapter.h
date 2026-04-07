/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#pragma once

#include <string>

#include "modules/my_company/common/sensor/sensor_adapter_registry.h"

namespace apollo {
namespace my_company {

struct PerceptionObservation {
  std::string source_vendor;
  double timestamp_sec = 0.0;
  int obstacle_count = 0;
  bool valid = false;
};

class MyPerceptionAdapter final {
 public:
  explicit MyPerceptionAdapter(const SensorAdapterRegistry* registry =
                                   &SensorAdapterRegistry::Instance())
      : registry_(registry) {}

  bool IngestVendorPayload(const std::string& vendor_name,
                           const std::string& raw_payload,
                           PerceptionObservation* observation) const;

 private:
  const SensorAdapterRegistry* registry_;
};

}  // namespace my_company
}  // namespace apollo
