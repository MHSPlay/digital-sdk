#pragma once

#ifndef VALVE_SHAREDDEFS
#define VALVE_SHAREDDEFS

#define to_ticks( time ) static_cast< int >( 0.5f + time / g_interfaces->m_globals->m_interval_per_tick );
#define to_time( tick ) static_cast< float >( tick ) * g_interfaces->m_globals->m_interval_per_tick;

enum e_damage {
    damage_no,
    damage_events_only,
    damage_yes,
    damage_aim
};

enum e_hitgroups {
    hitgroup_generic = 0,
    hitgroup_head,
    hitgroup_chest,
    hitgroup_stomach,
    hitgroup_leftarm,
    hitgroup_rightarm,
    hitgroup_leftleg,
    hitgroup_rightleg,
    hitgroup_neck,
    hitgroup_gear = 10
};

enum e_invalidate_physics_bits {
    position_changed = 0x1,
    angles_changed = 0x2,
    velocity_changed = 0x4,
    animation_changed = 0x8,
    bounds_changed = 0x10,
    sequence_changed = 0x20,
};

enum e_obs_mode {
    obs_mode_none = 0,
    obs_mode_deathcam,
    obs_mode_freezecam,
    obs_mode_fixed,
    obs_mode_in_eye,
    obs_mode_chase,
    obs_mode_roaming,
    num_observer_modes,
};

#endif