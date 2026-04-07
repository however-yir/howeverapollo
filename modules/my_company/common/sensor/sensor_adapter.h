/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#pragma once

#include <string>
#include <unordered_map>

namespace apollo {
namespace my_company {

struct SensorFrame {
  std::string sensor_id;
  double timestamp_sec = 0.0;
  std::unordered_map<std::string, double> numeric_fields;
};

class SensorAdapter {
 public:
  virtual ~SensorAdapter() = default;

  virtual std::string VendorName() const = 0;

  // Decode vendor raw payload into unified frame.
  virtual bool Decode(const std::string& raw_payload,
                      SensorFrame* unified_frame) const = 0;
};

}  // namespace my_company
}  // namespace apollo
