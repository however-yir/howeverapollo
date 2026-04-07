load("//tools:apollo_package.bzl", "apollo_cc_library", "apollo_cc_test", "apollo_package")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

apollo_cc_library(
    name = "sensor_adapter",
    hdrs = ["sensor_adapter.h"],
)

apollo_cc_library(
    name = "sensor_adapter_registry",
    srcs = ["sensor_adapter_registry.cc"],
    hdrs = ["sensor_adapter_registry.h"],
    deps = [":sensor_adapter"],
)

apollo_cc_test(
    name = "sensor_adapter_registry_test",
    size = "small",
    srcs = ["sensor_adapter_registry_test.cc"],
    deps = [
        ":sensor_adapter_registry",
        "@com_google_googletest//:gtest_main",
    ],
)

apollo_package()

cpplint()
