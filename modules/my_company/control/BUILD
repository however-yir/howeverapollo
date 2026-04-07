load("//tools:apollo_package.bzl", "apollo_cc_library", "apollo_cc_test", "apollo_package")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

apollo_cc_library(
    name = "control_mode_switch",
    srcs = ["control_mode_switch.cc"],
    hdrs = ["control_mode_switch.h"],
)

apollo_cc_library(
    name = "fault_injection_switch",
    srcs = ["fault_injection_switch.cc"],
    hdrs = ["fault_injection_switch.h"],
)

apollo_cc_test(
    name = "control_mode_switch_test",
    size = "small",
    srcs = ["control_mode_switch_test.cc"],
    deps = [
        ":control_mode_switch",
        ":fault_injection_switch",
        "@com_google_googletest//:gtest_main",
    ],
)

apollo_package()

cpplint()
