/****************************************************************************
 * Modified by however-yir autonomous driving team.
 ****************************************************************************/

#include "modules/my_company/common/sensor/sensor_adapter_registry.h"

#include <utility>

namespace apollo {
namespace my_company {

SensorAdapterRegistry& SensorAdapterRegistry::Instance() {
  static SensorAdapterRegistry registry;
  return registry;
}

bool SensorAdapterRegistry::Register(std::unique_ptr<SensorAdapter> adapter) {
  if (adapter == nullptr) {
    return false;
  }
  const std::string vendor = adapter->VendorName();
  if (vendor.empty()) {
    return false;
  }

  std::lock_guard<std::mutex> lock(mutex_);
  auto inserted = adapters_.emplace(vendor, std::move(adapter));
  return inserted.second;
}

const SensorAdapter* SensorAdapterRegistry::Get(
    const std::string& vendor_name) const {
  std::lock_guard<std::mutex> lock(mutex_);
  auto iter = adapters_.find(vendor_name);
  if (iter == adapters_.end()) {
    return nullptr;
  }
  return iter->second.get();
}

std::vector<std::string> SensorAdapterRegistry::ListVendors() const {
  std::lock_guard<std::mutex> lock(mutex_);
  std::vector<std::string> vendors;
  vendors.reserve(adapters_.size());
  for (const auto& item : adapters_) {
    vendors.push_back(item.first);
  }
  return vendors;
}

void SensorAdapterRegistry::ClearForTest() {
  std::lock_guard<std::mutex> lock(mutex_);
  adapters_.clear();
}

}  // namespace my_company
}  // namespace apollo
