#pragma once

inline const char* json_menu = R"({
    "tabs": [
        {
            "groups": null,
            "name": "Home"
        },
        {
            "groups": [
                {
                    "elements": [
                        {
                            "config": "ragebot_enable",
                            "name": "Enable",
                            "type": 0
                        },
                        {
                            "config": "ragebot_auto_fire",
                            "name": "AutoFire",
                            "type": 0
                        },
                        {
                            "config": "ragebot_auto_silent",
                            "name": "Silent",
                            "type": 0
                        },
                        {
                            "config": "ragebot_auto_scope",
                            "name": "Auto Scope",
                            "type": 0
                        },
                        {
                            "config": "ragebot_penetration",
                            "name": "Penetration",
                            "type": 0
                        },
                        {
                            "config": "ragebot_hideshots",
                            "name": "Hideshots",
                            "type": 0
                        },
                        {
                            "config": "ragebot_nospread",
                            "name": "NoSpread",
                            "type": 0
                        },
                        {
                            "config": "ragebot_rapidfire",
                            "name": "RapidFire",
                            "type": 0
                        },
                        {
                            "config": "group_select",
                            "config_name": [
                                "Pistol",
                                "Rifle",
                                "Machine",
                                "Revolver",
                                "Deagle",
                                "SSG",
                                "AWP",
                                "AutoSniper"
                            ],
                            "name": "Group",
                            "type": 2
                        }
                    ],
                    "name": "General",
                    "same_line": true,
                    "size": [
                        240.0,
                        280.0
                    ]
                },
                {
                    "elements": [
                        {
                            "config": [
                                "ragebot_hitbox_head",
                                "ragebot_hitbox_chest",
                                "ragebot_hitbox_stomach",
                                "ragebot_hitbox_arms",
                                "ragebot_hitbox_legs",
                                "ragebot_hitbox_foot"
                            ],
                            "config_name": [
                                "Head",
                                "Chest",
                                "Stomach",
                                "Arms",
                                "Legs",
                                "Foot"
                            ],
                            "name": "Hitboxes",
                            "should_weapons": true,
                            "type": 3
                        },
                        {
                            "config": "ragebot_hitchance_amount",
                            "max": 100,
                            "min": 0,
                            "name": "Hitchance",
                            "should_weapons": true,
                            "type": 1
                        },
                        {
                            "config": "ragebot_damage",
                            "max": 120,
                            "min": 1,
                            "name": "Damage",
                            "should_weapons": true,
                            "type": 1
                        }
                    ],
                    "name": "Accuracy",
                    "same_line": false,
                    "size": [
                        240.0,
                        120.0
                    ]
                },
                {
                    "elements": [
                        {
                            "config": "ragebot_autostop",
                            "name": "AutoStop",
                            "should_weapons": true,
                            "type": 0
                        }
                    ],
                    "name": "Autostop",
                    "same_line": true,
                    "size": [
                        240.0,
                        100.0
                    ]
                },
                {
                    "elements": [
                        {
                            "config": [
                                "ragebot_multipoint_head",
                                "ragebot_multipoint_chest",
                                "ragebot_multipoint_stomach",
                                "ragebot_multipoint_arms",
                                "ragebot_multipoint_legs",
                                "ragebot_multipoint_foot"
                            ],
                            "config_name": [
                                "Head",
                                "Chest",
                                "Stomach",
                                "Arms",
                                "Legs",
                                "Foot"
                            ],
                            "name": "Multipoint",
                            "should_weapons": true,
                            "type": 3
                        },
                        {
                            "config": "ragebot_multipoint_scale",
                            "max": 100,
                            "min": 1,
                            "name": "Point Scale",
                            "should_weapons": true,
                            "type": 1
                        }
                    ],
                    "name": "Multipoint",
                    "same_line": true,
                    "size": [
                        240.0,
                        150.0
                    ]
                },
                {
                    "elements": [
                        {
                            "config": "misc_autopeek",
                            "name": "AutoPeek",
                            "type": 0
                        },
                        {
                            "config": "ragebot_track",
                            "config_name": [
                                "Low",
                                "Medium",
                                "High"
                            ],
                            "name": "Backtrack",
                            "type": 2
                        }
                    ],
                    "name": "Other",
                    "same_line": false,
                    "size": [
                        240.0,
                        140.0
                    ]
                },
                {
                    "elements": [
                        {
                            "config": "antiaim_enable",
                            "name": "Enable",
                            "type": 0
                        },
                        {
                            "config": "antiaim_at_target",
                            "name": "At target",
                            "type": 0
                        },
                        {
                            "config": "antiaim_pitch",
                            "config_name": [
                                "None",
                                "Down",
                                "Up"
                            ],
                            "name": "Pitch",
                            "type": 2
                        },
                        {
                            "config": "antiaim_yaw",
                            "config_name": [
                                "None",
                                "Backward"
                            ],
                            "name": "Yaw",
                            "type": 2
                        },
                        {
                            "config": "antiaim_yaw_offset",
                            "max": 180,
                            "min": -180,
                            "name": "Yaw Offset",
                            "type": 1
                        },
                        {
                            "config": "antiaim_jitter",
                            "max": 120,
                            "min": -120,
                            "name": "Jitter",
                            "type": 1
                        }
                    ],
                    "name": "AntiAim",
                    "same_line": false,
                    "size": [
                        240.0,
                        410.0
                    ]
                }
            ],
            "name": "Ragebot"
        },
        {
            "groups": [
                {
                    "elements": [
                        {
                            "config": "legitbot_enabled",
                            "name": "Enable",
                            "type": 0
                        },
                        {
                            "config": "legitbot_trigger_bot",
                            "name": "TriggerBot",
                            "type": 0
                        },
                        {
                            "config": "legitbot_draw_fov",
                            "name": "Draw FOV",
                            "type": 0
                        },
                        {
                            "config": "legitbot_silent",
                            "name": "Silent",
                            "type": 0
                        },
                        {
                            "config": [
                                "legitbot_hitbox_head",
                                "legitbot_hitbox_body",
                                "legitbot_hitbox_arms",
                                "legitbot_hitbox_legs"
                            ],
                            "config_name": [
                                "Head",
                                "Body",
                                "Arms",
                                "Legs"
                            ],
                            "name": "Hitboxes",
                            "type": 3
                        },
                        {
                            "config": "legitbot_fov",
                            "max": 50,
                            "min": 0,
                            "name": "FOV",
                            "type": 1
                        },
                        {
                            "config": "legitbot_smooth",
                            "max": 30,
                            "min": 0,
                            "name": "Smooth",
                            "type": 1
                        },
                        {
                            "config": "legitbot_standalone_rcs",
                            "name": "Standalone RCS",
                            "type": 0
                        },
                        {
                            "config": "legitbot_rcs_coefficient",
                            "max": 100,
                            "min": 0,
                            "name": "RCS Amount",
                            "type": 1
                        }
                    ],
                    "name": "General",
                    "same_line": false,
                    "size": [
                        240.0,
                        300.0
                    ]
                }
            ],
            "name": "LegitBot"
        },
        {
            "groups": [
                {
                    "elements": [
                        {
                            "config": "esp_name",
                            "name": "Name",
                            "type": 0
                        },
                        {
                            "config": "esp_name_color",
                            "name": "Name Color",
                            "type": 5
                        },
                        {
                            "config": "esp_avatar",
                            "name": "Avatar",
                            "type": 0
                        },
                        {
                            "config": "esp_box",
                            "name": "Box",
                            "type": 0
                        },
                        {
                            "config": "esp_box_color",
                            "name": "Box Color",
                            "type": 5
                        },
                        {
                            "config": "esp_health",
                            "name": "Health",
                            "type": 0
                        },
                        {
                            "config": [
                                "esp_flags_bomb",
                                "esp_flags_kits",
                                "esp_flags_armor",
                                "esp_flags_flashed",
                                "esp_flags_zeus",
                                "esp_flags_defuser"
                            ],
                            "config_name": [
                                "Bomb",
                                "Kits",
                                "Armor",
                                "Flashed",
                                "Zeus",
                                "Defuser"
                            ],
                            "name": "Flags",
                            "type": 3
                        },
                        {
                            "config": "esp_skeleton",
                            "name": "Skeleton",
                            "type": 0
                        },
                        {
                            "config": "esp_skeleton_color",
                            "name": "Skeleton Color",
                            "type": 5
                        },
                        {
                            "config": [
                                "esp_weapons_name",
                                "esp_weapons_icon"
                            ],
                            "config_name": [
                                "Name",
                                "Icon"
                            ],
                            "name": "Weapons",
                            "type": 3
                        },
                        {
                            "config": "esp_oof",
                            "name": "OOF",
                            "type": 0
                        },
                        {
                            "config": "esp_oof_color",
                            "name": "OOF Color",
                            "type": 5
                        }
                    ],
                    "name": "ESP",
                    "same_line": true,
                    "size": [
                        355.0,
                        260.0
                    ]
                },
                {
                    "elements": [
                        {
                            "config": "chams_visible",
                            "name": "Chams Visible",
                            "type": 0
                        },
                        {
                            "config": "chams_visible_color",
                            "name": "Chams Visible Color",
                            "type": 5
                        },
                        {
                            "config": "chams_type",
                            "config_name": [
                                "Flat",
                                "Regular",
                                "Bloom",
                                "Glow"
                            ],
                            "name": "Chams Type",
                            "type": 2
                        },
                        {
                            "config": "chams_invisible",
                            "name": "Chams Invisible",
                            "type": 0
                        },
                        {
                            "config": "chams_invisible_color",
                            "name": "Chams Invisible Color",
                            "type": 5
                        }
                    ],
                    "name": "Chams",
                    "same_line": false,
                    "size": [
                        355.0,
                        130.0
                    ]
                },
                {
                    "elements": [
                        {
                            "config": [
                                "misc_disable_light",
                                "misc_smoke_remove",
                                "misc_remove_scope",
                                "misc_norecoil",
                                "misc_flashbang",
                                "misc_remove_post_processing",
                                "misc_remove_legs",
                                "misc_remove_bob",
                                "misc_remove_grenade_crosshair" 
                            ],
                            "config_name": [
                                "Light",
                                "Smoke",
                                "Scope",
                                "Recoil",
                                "Flashbang",
                                "PostProcessing", 
                                "Legs",
                                "Bob", 
                                "Grenade Crosshair"
                            ],
                            "name": "Removes",
                            "type": 3
                        },
                        {
                            "config": [
                                "misc_blur",
                                "misc_onshot_capsule",
                                "misc_dark_mode"
                            ],
                            "config_name": [
                                "Blur",
                                "OnShot Capsule",
                                "Dark Mode"
                            ],
                            "name": "Effects",
                            "type": 3
                        },
                        {
                            "config": [
                                "misc_penetration_crosshair",
                                "misc_force_crosshair"
                            ],
                            "config_name": [
                                "Penetration Crosshair",
                                "Force Crosshair"
                            ],
                            "name": "Crosshair",
                            "type": 3
                        },
                        {
                            "config": "misc_world_changer",
                            "config_name": [
                                "None",
                                "FullBright",
                                "White",
                                "Specular Lighting",
                                "Cubemap reflection",
                                "Normal WS",
                                "Tangen WS",
                                "Geometric Normal WS",
                                "Baked Light Direction"
                            ],
                            "name": "World Changer",
                            "type": 2
                        },
                        {
                            "config": "misc_thirdperson",
                            "name": "Thirdperson",
                            "type": 0
                        },
                        {
                            "config": "misc_thirdperson_amount",
                            "max": 200,
                            "min": 35,
                            "name": "Thirdperson Amount",
                            "type": 1
                        },
                       {
                            "config": "misc_server_impact",
                            "name": "Server Impact",
                            "type": 0
                        },
                        {
                            "config": "misc_client_impact",
                            "name": "Client Impact",
                            "type": 0
                        },
                        {
                            "config": "misc_skybox",
                            "name": "Skybox Modulation",
                            "type": 0
                        },
                        {
                            "config": "misc_skybox_color",
                            "name": "Skybox Color",
                            "type": 5
                        },
                        {
                            "config": "misc_bullet_trace",
                            "name": "Bullet Tracer",
                            "type": 0
                        },
                        {
                            "config": "misc_bullet_trace_color",
                            "name": "Bullet Tracer Color",
                            "type": 5
                        },
                        {
                            "config": "misc_bullet_trace_enemy",
                            "name": "Bullet Tracer Enemy",
                            "type": 0
                        },
                        {
                            "config": "misc_bullet_trace_enemy_color",
                            "name": "Bullet Tracer Enemy Color",
                            "type": 5
                        },
                        {
                            "config": "misc_grenade_prediction",
                            "name": "Grenade Prediction",
                            "type": 0
                        }
                    ],
                    "name": "World",
                    "same_line": true,
                    "size": [
                        355.0,
                        400.0
                    ]
                }
            ],
            "name": "Visuals"
        },
        {
            "groups": [
                {
                    "elements": [
                        {
                            "config": "misc_bunnyhop",
                            "name": "Bunnyhop",
                            "type": 0
                        },
                       {
                            "config": "misc_autostrafe",
                            "name": "AutoStrafe",
                            "type": 0
                        },
                       {
                            "config": [
                                "misc_keybind",
                                "misc_spectators",
                                "misc_watermark"
                            ],
                            "config_name": [
                                "Keybind",
                                "Spectators",
                                "Watermark"
                            ],
                            "name": "Windows",
                            "type": 3
                        },
                        {
                            "config": "misc_viewmodel_changer",
                            "name": "Viewmodel Changer",
                            "type": 0
                        },
                        {
                            "config": "misc_viewmodel_x",
                            "max": 10,
                            "min": -10,
                            "name": "Viewmodel x",
                            "type": 1
                        },
                        {
                            "config": "misc_viewmodel_y",
                            "max": 10,
                            "min": -10,
                            "name": "Viewmodel y",
                            "type": 1
                        },
                        {
                            "config": "misc_viewmodel_z",
                            "max": 10,
                            "min": -10,
                            "name": "Viewmodel z",
                            "type": 1
                        },
                        {
                            "config": "misc_fov",
                            "max": 140,
                            "min": 50,
                            "name": "FOV",
                            "type": 1
                        },
                        {
                            "config": "misc_killfeed",
                            "name": "Preserve killfeed",
                            "type": 0
                        },
                        {
                            "config": "misc_unlock_inventory",
                            "name": "Unlock Inventory",
                            "type": 0
                        },
                        {
                            "config": "misc_hitsound",
                            "name": "Hitsound",
                            "type": 0
                        },
                        {
                            "config": "misc_hitmarker",
                            "name": "Hitmarker",
                            "type": 0
                        }
                    ],
                    "name": "General",
                    "same_line": false,
                    "size": [
                        355.0,
                        400.0
                    ]
                },
{
                    "elements": [
                        {
                            "config": "misc_buybot",
                            "name": "Buybot",
                            "type": 0
                        },
                      {
                            "config": "misc_buybot_primary",
                            "config_name": [
                                "None",
                                "SSG08",
                                "AWP",
                                "SCAR20 / G3SG1"
                            ],
                            "name": "Primary",
                            "type": 2
                        },
                      {
                            "config": "misc_buybot_secondary",
                            "config_name": [
                                "None",
                                "Deagle",
                                "Five-Seven"
                            ],
                            "name": "Secondary",
                            "type": 2
                        },
                        {
                            "config": [
                                "misc_buybot_zeus",
                                "misc_buybot_armor",
                                "misc_buybot_grenades"
                            ],
                            "config_name": [
                                "Zeus x27",
                                "Armor",
                                "Grenades"
                            ],
                            "name": "Other",
                            "type": 3
                        }
                    ],
                    "name": "Buybot",
                    "same_line": false,
                    "size": [
                        355.0,
                        160.0
                    ]
                }
            ],
            "name": "Misc"
        },
        {
            "groups": null,
            "name": "Inventory"
        }
    ]
}
)";