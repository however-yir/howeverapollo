load("//tools:apollo_package.bzl", "apollo_cc_library", "apollo_cc_test", "apollo_package")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

apollo_cc_library(
    name = "my_perception_adapter",
    srcs = ["my_perception_adapter.cc"],
    hdrs = ["my_perception_adapter.h"],
    deps = ["//modules/my_company/common/sensor:sensor_adapter_registry"],
)

apollo_cc_test(
    name = "my_perception_adapter_test",
    size = "small",
    srcs = ["my_perception_adapter_test.cc"],
    deps = [
        ":my_perception_adapter",
        "//modules/my_company/common/sensor:sensor_adapter_registry",
        "@com_google_googletest//:gtest_main",
    ],
)

apollo_package()

cpplint()
