/**
 * Modified by however-yir autonomous driving team.
 */

export type MenuOrderKey = 'MODE_SETTING' | 'ADD_PANEL' | 'PROFILE_MANAGEER';

export interface RuntimeConfig {
    meta?: {
        environment?: string;
        modified_by?: string;
    };
    dreamview: {
        brand_name: string;
        short_name: string;
        logo_asset: string;
        theme: {
            primary: string;
            secondary: string;
            accent: string;
        };
        navigation: {
            menu_order: MenuOrderKey[];
        };
    };
    external_services: {
        workspace_url: string;
        faq_url: string;
        documentation_url: string;
        community_url: string;
        feedback_url: string;
    };
}

const defaultRuntimeConfig: RuntimeConfig = {
    meta: {
        environment: 'dev',
        modified_by: 'however-yir autonomous driving team',
    },
    dreamview: {
        brand_name: 'HoweverPilot',
        short_name: 'HWP',
        logo_asset: '/brand/hwp-logo.svg',
        theme: {
            primary: '#0F6CBD',
            secondary: '#0B3A53',
            accent: '#13B38B',
        },
        navigation: {
            menu_order: ['MODE_SETTING', 'PROFILE_MANAGEER', 'ADD_PANEL'],
        },
    },
    external_services: {
        workspace_url: 'https://console.my-company.example/workspace',
        faq_url: 'https://console.my-company.example/help/faq',
        documentation_url: 'https://console.my-company.example/docs/dreamview',
        community_url: 'https://console.my-company.example/community',
        feedback_url: 'https://console.my-company.example/feedback',
    },
};

function mergeConfig(runtimeRaw: unknown): RuntimeConfig {
    const runtime =
        runtimeRaw && typeof runtimeRaw === 'object'
            ? (runtimeRaw as Partial<RuntimeConfig>)
            : ({} as Partial<RuntimeConfig>);

    const runtimeDreamview = runtime.dreamview || {};
    const runtimeServices = runtime.external_services || {};

    return {
        meta: {
            ...defaultRuntimeConfig.meta,
            ...(runtime.meta || {}),
        },
        dreamview: {
            ...defaultRuntimeConfig.dreamview,
            ...runtimeDreamview,
            theme: {
                ...defaultRuntimeConfig.dreamview.theme,
                ...(runtimeDreamview.theme || {}),
            },
            navigation: {
                ...defaultRuntimeConfig.dreamview.navigation,
                ...(runtimeDreamview.navigation || {}),
            },
        },
        external_services: {
            ...defaultRuntimeConfig.external_services,
            ...runtimeServices,
        },
    };
}

export const runtimeConfig = mergeConfig(window.__MY_COMPANY_CONFIG__);
