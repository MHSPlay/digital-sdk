#pragma once

#ifndef VALVE_OTHER_STUDIO
#define VALVE_OTHER_STUDIO

#include "../../utils/math/matrix.hh"
#include "../../utils/math/vector.hh"

using mdl_handle_t = unsigned short;

struct mstudiobone_t {
    int m_name_index{ };
    char* psz_name( ) const { return ( char* ) this + m_name_index; }
    int m_parent{ };
    int m_bone_controller[ 6 ]{ }; // bone controller index, -1 == none
    c_vec3 m_pos{ };
    float m_quat[ 4 ]{ };
    float m_rot[ 3 ]{ };
    // compression scale
    c_vec3 m_pos_scale{ };
    c_vec3 m_rot_scale{ };

    matrix_t m_pose_to_bone{ };
    float m_alignment[ 4 ]{ };
    int m_flags{ };
    int m_proc_type{ };
    int m_proc_index{ };
    mutable int m_physics_bone{ };
    int m_surface_prop_idx{ };

    int m_contents{ };
    int m_surface_prop_lookup{ };
    int m_pad01[ 7 ]{ };

    char* psz_surface_prop( ) const { return ( char* ) ( this + m_surface_prop_idx ); }
    int get_surface_prop( ) const { return m_surface_prop_lookup; }

    mstudiobone_t( ) {}
private:
    // No copy constructors allowed
    mstudiobone_t( const mstudiobone_t& other );
};

struct mstudiobbox_t {
    int m_bone{ };
    int m_group{ };
    c_vec3 m_mins{ };
    c_vec3 m_maxs{ };
    int m_hitbox_name_index{ };
    c_vec3 m_rotation{ };
    float m_radius{ };
    int pad2[ 4 ]{ };

    const char* get_name( ) {
        return !m_hitbox_name_index
            ? nullptr
            : reinterpret_cast< const char* >( reinterpret_cast< uint8_t* >( this ) + m_hitbox_name_index );
    }
};

struct mstudiohitboxset_t {
    int m_name_index{ };
    int m_num_hitboxes{ };
    int m_hitbox_index{ };

    const char* get_name( ) {
        return !m_name_index
            ? nullptr
            : reinterpret_cast< const char* >( reinterpret_cast< std::uint8_t* >( this ) + m_name_index );
    }

    mstudiobbox_t* get_hitbox( const int i ) {
        return i > m_num_hitboxes
            ? nullptr
            : reinterpret_cast< mstudiobbox_t* >( reinterpret_cast< std::uint8_t* >( this ) + m_hitbox_index ) + i;
    }
};

struct studio_hdr_t {
    int m_id{ };
    int m_version{ };
    long m_checksum{ };
    char m_sz_name[ 64 ]{ };
    int m_length{ };
    c_vec3 m_eye_pos{ };
    c_vec3 m_illum_pos{ };
    c_vec3 m_hull_min{ };
    c_vec3 m_hull_max{ };
    c_vec3 m_bb_min{ };
    c_vec3 m_bb_max{ };
    int m_flags{ };
    int m_num_bones{ };
    int m_bone_index{ };
    int m_num_bone_controllers{ };
    int m_bone_controller_index{ };
    int m_num_hitbox_sets{ };
    int m_hitbox_set_index{ };
    int m_num_local_anim{ };
    int m_local_anim_index{ };
    int m_num_local_seq{ };
    int m_local_seq_index{ };
    int m_activity_list_version{ };
    int m_events_indexed{ };
    int m_num_textures{ };
    int m_texture_index{ };

    mstudiohitboxset_t* get_hitbox_set( const int i ) {
        return i > m_num_hitbox_sets
            ? nullptr
            : reinterpret_cast< mstudiohitboxset_t* >( reinterpret_cast< std::uint8_t* >( this ) + m_hitbox_set_index )
                + i;
    }

    mstudiobone_t* get_bone( const int i ) {
        return i > m_num_bones
            ? nullptr
            : reinterpret_cast< mstudiobone_t* >( reinterpret_cast< std::uint8_t* >( this ) + m_bone_index ) + i;
    }
};

#endif