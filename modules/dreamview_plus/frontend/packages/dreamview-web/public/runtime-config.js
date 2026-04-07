/* Modified by however-yir autonomous driving team. */
window.__MY_COMPANY_CONFIG__ = {
  meta: {
    environment: "dev",
    modified_by: "however-yir autonomous driving team"
  },
  dreamview: {
    brand_name: "HoweverPilot",
    short_name: "HWP",
    logo_asset: "/brand/hwp-logo.svg",
    theme: {
      primary: "#0F6CBD",
      secondary: "#0B3A53",
      accent: "#13B38B"
    },
    navigation: {
      menu_order: ["MODE_SETTING", "PROFILE_MANAGEER", "ADD_PANEL"]
    }
  },
  external_services: {
    workspace_url: "https://console.my-company.example/workspace",
    faq_url: "https://console.my-company.example/help/faq",
    documentation_url: "https://console.my-company.example/docs/dreamview",
    community_url: "https://console.my-company.example/community",
    feedback_url: "https://console.my-company.example/feedback"
  }
};

if (window.__MY_COMPANY_CONFIG__?.dreamview?.brand_name) {
  document.title = window.__MY_COMPANY_CONFIG__.dreamview.brand_name;
}
