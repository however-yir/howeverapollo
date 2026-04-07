/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#include "modules/my_company/perception_adapter/my_perception_adapter.h"

namespace apollo {
namespace my_company {

bool MyPerceptionAdapter::IngestVendorPayload(
    const std::string& vendor_name, const std::string& raw_payload,
    PerceptionObservation* observation) const {
  if (observation == nullptr || registry_ == nullptr) {
    return false;
  }

  const SensorAdapter* adapter = registry_->Get(vendor_name);
  if (adapter == nullptr) {
    return false;
  }

  SensorFrame frame;
  if (!adapter->Decode(raw_payload, &frame)) {
    return false;
  }

  observation->source_vendor = vendor_name;
  observation->timestamp_sec = frame.timestamp_sec;
  auto iter = frame.numeric_fields.find("object_count");
  observation->obstacle_count =
      iter == frame.numeric_fields.end() ? 0 : static_cast<int>(iter->second);
  observation->valid = true;
  return true;
}

}  // namespace my_company
}  // namespace apollo
