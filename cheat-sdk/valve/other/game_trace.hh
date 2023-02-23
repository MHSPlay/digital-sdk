#pragma once

#ifndef VALVE_GAME_TRACE
#define VALVE_GAME_TRACE

#include "../../utils/math/math.hh"

class c_player;

struct cplane_t {
    c_vec3 m_normal;
    float m_dist;
    uint8_t m_type;
    uint8_t m_signbits;
    uint8_t m_pad[ 2 ];
};

struct csurface_t {
    const char* m_name;
    short m_surface_props;
    uint16_t m_flags;
};

class c_game_trace {
public:
    [[nodiscard]] bool did_hit( ) const {
        return m_fraction < 1.0f || m_all_solid || m_start_solid;
    }

    [[nodiscard]] bool is_visible( ) const {
        return m_fraction > 0.97f;
    }

    c_vec3 m_start{ };
    c_vec3 m_end{ };
    cplane_t m_plane{ };
    float m_fraction{ };
    int m_contents{ };
    std::uint16_t m_disp_flags{ };
    bool m_all_solid{ };
    bool m_start_solid{ };
    float m_fraction_left_solid{ };
    csurface_t m_surface{ };
    int m_hit_group{ };
    std::uint16_t m_world_surface_index{ };
    c_player* m_entity{ };
    int m_hitbox{ };
};

#endif