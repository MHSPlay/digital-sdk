#pragma once

#ifndef VALVE_USER_CMD
#define VALVE_USER_CMD

#include "../../utils/math/math.hh"

class c_user_cmd {
    char pad0[ 0x4 ]{ };
public:
    int m_command_number{ };
    int m_tick_count{ };
    c_vec3 m_view_angles;
    c_vec3 m_aim_direction;
    float m_forward_move{ };
    float m_side_move{ };
    float m_up_move{ };
    int m_buttons{ };
    int m_impulse{ };
    int m_weapon_select{ };
    int m_weapon_sub_type{ };
    int m_random_seed{ };
    short m_moused_x{ };
    short m_moused_y{ };
    bool m_has_been_predicted{ };
    c_vec3 m_head_angles;
    c_vec3 m_head_offset;
    [[nodiscard]] std::uint32_t get_checksum( ) const;
};

class c_verified_user_cmd {
public:
    c_user_cmd m_cmd{ };
    std::uint32_t m_crc{ };
};

#endif