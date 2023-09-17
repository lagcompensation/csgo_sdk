#pragma once

namespace valve {
    struct cvar_t;

    struct recv_prop_t;
}

class c_ctx {
private:
    using modules_t = std::unordered_map< sdk::hash_t, sdk::x86_pe_image_t* >;

    using interfaces_t = std::unordered_map< sdk::hash_t, sdk::address_t >;

    struct ent_offset_t {
        valve::recv_prop_t* m_prop{};
        std::uint32_t       m_offset{};
    };

    using ent_offsets_t = std::unordered_map< sdk::hash_t, ent_offset_t >;

    bool wait_for_all_modules( modules_t& modules ) const;

    void init_imgui( const modules_t& modules ) const;

    void init_renderer( ) const;

    void parse_interfaces( sdk::x86_pe_image_t* const image, interfaces_t& interfaces ) const;

    void init_interfaces( const modules_t& modules ) const;

    bool parse_ent_offsets( ent_offsets_t& offsets, const modules_t& modules ) const;

    void init_offsets( const modules_t& modules );

    void init_cvars( );

    void init_hooks( const modules_t& modules ) const;

    void init_players( ) const;

    struct {
        sdk::address_t  m_local_player{},
                        m_weapon_system{},
                        m_user_cmd_checksum{},
                        m_pred_player{},
                        m_random_seed{},
                        m_setup_velocity{},
                        m_accumulate_layers{},
                        m_is_extrapolated{},
                        m_should_hit_entity{},
                        m_should_hit_entity_two_entities{};

        struct {
            sdk::address_t m_init{}, m_load_from_buffer{};
        }               m_key_values{};

        struct {
            sdk::address_t m_reset{}, m_update{};
        }               m_anim_state{};

        struct {
            std::uint32_t m_bone_cache{}, m_mdl_bone_cnt{};
        }               m_renderable{};

        struct {
            sdk::address_t  m_set_abs_origin{}, m_set_abs_angles{},
                            m_breakable_game{};

            std::uint32_t   m_health{}, m_team_num{},
                            m_sim_time{}, m_flags{},
                            m_origin{}, m_velocity{},
                            m_abs_velocity{}, m_abs_rotation{}, 
                            m_move_type{}, m_mins{}, 
                            m_maxs{}, m_eflags{};
        }               m_base_entity{};

        struct {
            std::uint32_t   m_owner{};
        }               m_view_model{};

        struct {
            std::uint32_t   m_sequence{},
                            m_hitbox_set_index{}, m_studio_hdr{},
                            m_pose_params{}, m_anim_layers{},
                            m_client_side_anim{};
        }               m_base_animating{};

        struct {
            std::uint32_t   m_pin_pulled{},
                            m_throw_time{}, m_throw_strength{};
        }               m_base_grenade{};

        struct {
            std::uint32_t   m_item_index{};
        }               m_base_attributable_item{};

        struct {
            std::uint32_t   m_clip1{}, m_primary_reserve_ammo_count{},
                            m_next_primary_attack{}, m_next_secondary_attack{};
        }               m_base_weapon{};

        struct {
            std::uint32_t   m_burst_mode{},
                            m_last_shot_time{}, m_recoil_index{},
                            m_postpone_fire_ready_time{};
        }               m_weapon_cs_base{};

        struct {
            std::uint32_t   m_zoom_lvl{},
                            m_burst_shots_remaining{}, m_next_burst_shot{};
        }               m_weapon_cs_base_gun{};

        struct {
            std::uint32_t   m_weapon_handle{}, m_next_attack{};
        }               m_base_combat_character{};

        struct {
            std::uint32_t   m_tick_base{}, m_life_state{},
                            m_duck_amt{}, m_duck_speed{},
                            m_spawn_time{}, m_aim_punch{},
                            m_view_punch{}, m_view_offset{},
                            m_punch_vel{};
        }               m_base_player{};

        struct {
            sdk::address_t  m_most_recent_model_cnt{},
                            m_update_collision_bounds{},
                            m_seq_activity{}, m_set_collision_bounds{};

            std::uint32_t   m_lby{}, m_eye_angles{},
                            m_survival_team{},
                            m_anim_state{}, m_defusing{},
                            m_walking, m_scoped{},                            
                            m_effects{}, m_has_helmet{},
                            m_has_heavy_armor{}, m_armor_value{};
        }               m_cs_player{};

        struct {
            std::uint32_t   m_warmup_period{}, m_freeze_period{},
                            m_valve_ds{}, m_bomb_planted{};
        }               m_game_rules{};
    } m_offsets{};

    struct {
        valve::cvar_t*  cl_forwardspeed{}, *cl_backspeed{},
                        *cl_sidespeed{}, *cl_upspeed{},
                        *cl_pitchdown{}, *cl_pitchup{},
                        *mp_teammates_are_enemies{}, *sv_gravity{},
                        *mp_damage_headshot_only{}, *ff_damage_bullet_penetration{},
                        *mp_damage_scale_ct_head{}, *mp_damage_scale_ct_body{},
                        *mp_damage_scale_t_head{}, *mp_damage_scale_t_body{},
                        *sv_clip_penetration_traces_to_players{}, *ff_damage_reduction_bullets{};
    } m_cvars{};
public:
    void init( );

    ALWAYS_INLINE const auto& offsets( ) const;

    ALWAYS_INLINE const auto& cvars( ) const;
};

inline const auto g_ctx = std::make_unique< c_ctx >( );


#include "impl/ctx.inl"