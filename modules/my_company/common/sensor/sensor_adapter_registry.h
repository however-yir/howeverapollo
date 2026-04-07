/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "modules/my_company/common/sensor/sensor_adapter.h"

namespace apollo {
namespace my_company {

class SensorAdapterRegistry final {
 public:
  static SensorAdapterRegistry& Instance();

  bool Register(std::unique_ptr<SensorAdapter> adapter);

  const SensorAdapter* Get(const std::string& vendor_name) const;

  std::vector<std::string> ListVendors() const;

  void ClearForTest();

 private:
  SensorAdapterRegistry() = default;

  mutable std::mutex mutex_;
  std::map<std::string, std::unique_ptr<SensorAdapter>> adapters_;
};

}  // namespace my_company
}  // namespace apollo
