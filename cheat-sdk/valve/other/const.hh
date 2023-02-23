#pragma once

#ifndef VALVE_OTHER_CONST
#define VALVE_OTHER_CONST

enum e_move_type {
    move_type_none = 0,
    move_type_isometric,
    move_type_walk,
    move_type_step,
    move_type_fly,
    move_type_fly_gravity,
    move_type_vphysics,
    move_type_push,
    move_type_noclip,
    move_type_ladder,
    move_type_ob_server,
    move_type_custom,
    move_type_last = move_type_custom,
    move_type_max_bits = 4
};

enum e_flags {
    fl_on_ground = 1 << 0,
    fl_ducking = 1 << 1,
    fl_anim_ducking = 1 << 2,
    fl_water_jump = 1 << 3,
    fl_on_train = 1 << 4,
    fl_in_rain = 1 << 5,
    fl_frozen = 1 << 6,
    fl_at_controls = 1 << 7,
    fl_client = 1 << 8,
    fl_fake_client = 1 << 9,
    fl_in_water = 1 << 10,
    fl_fly = 1 << 11,
    fl_swim = 1 << 12,
    fl_conveyor = 1 << 13,
    fl_npc = 1 << 14,
    fl_god_mode = 1 << 15,
    fl_no_target = 1 << 16,
    fl_aim_target = 1 << 17,
    fl_partial_ground = 1 << 18,
    fl_static_prop = 1 << 19,
    fl_graphed = 1 << 20,
    fl_grenade = 1 << 21,
    fl_step_movement = 1 << 22,
    fl_dont_touch = 1 << 23,
    fl_base_velocity = 1 << 24,
    fl_world_brush = 1 << 25,
    fl_object = 1 << 26,
    fl_kill_me = 1 << 27,
    fl_on_fire = 1 << 28,
    fl_dissolving = 1 << 29,
    fl_trans_ragdoll = 1 << 30,
    fl_unblockable_by_player = 1 << 31
};

enum e_collision_group {
    collision_group_none = 0,
    collision_group_debris,
    // collides with nothing but world and static stuff
    collision_group_debris_trigger,
    // same as debris, but hits triggers
    collision_group_interactive_debris,
    // collides with everything except other interactive debris or debris
    collision_group_interactive,
    // collides with everything except interactive debris or debris
    collision_group_player,
    collision_group_breakable_glass,
    collision_group_vehicle,
    collision_group_player_movement,
    // for HL2, same as Collision_Group_Player, for / TF2, this filters out other players and CBaseObjects
    collision_group_npc,
    // generic NPC group
    collision_group_in_vehicle,
    // for any entity inside a vehicle
    collision_group_weapon,
    // for any weapons that need collision detection
    collision_group_vehicle_clip,
    // vehicle clip brush to restrict vehicle movement
    collision_group_projectile,
    // projectiles!
    collision_group_door_blocker,
    // blocks entities not permitted to get near moving doors
    collision_group_passable_door,
    // doors that the player shouldn't collide with
    collision_group_dissolving,
    // things that are dissolving are in this group
    collision_group_pushaway,
    // nonsolid on client and server, pushaway in player code
    collision_group_npc_actor,
    // used so NPCs in scripts ignore the player.
    collision_group_npc_scripted,
    // used for NPCs in scripts that should not collide with each other
    collision_group_pz_clip,
    collision_group_debris_block_projectile,
    // only collides with bullets
    last_shared_collision_group
};

#endif