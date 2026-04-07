load("//tools:apollo_package.bzl", "apollo_cc_library", "apollo_cc_test", "apollo_package")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

apollo_cc_library(
    name = "strategy_plugin",
    hdrs = ["strategy_plugin.h"],
)

apollo_cc_library(
    name = "rule_based_strategy_plugin",
    srcs = ["rule_based_strategy_plugin.cc"],
    hdrs = ["rule_based_strategy_plugin.h"],
    deps = [":strategy_plugin"],
)

apollo_cc_library(
    name = "strategy_plugin_manager",
    srcs = ["strategy_plugin_manager.cc"],
    hdrs = ["strategy_plugin_manager.h"],
    deps = [":strategy_plugin"],
)

apollo_cc_test(
    name = "strategy_plugin_test",
    size = "small",
    srcs = ["strategy_plugin_test.cc"],
    deps = [
        ":rule_based_strategy_plugin",
        ":strategy_plugin_manager",
        "@com_google_googletest//:gtest_main",
    ],
)

apollo_package()

cpplint()
