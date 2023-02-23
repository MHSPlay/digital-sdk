#pragma once

#ifndef VALVE_CDLL_INIT
#define VALVE_CDLL_INIT

#include "../engine/client_state.hh"
#include "../steam/steam_api.hh"

struct player_info_t {
    std::int64_t m_something{ };
    union {
        std::int64_t m_steam_id64{ };
        struct {
            std::int32_t m_xuid_low;
            std::int32_t m_xuid_high;
        };
    };

    char m_name[ 128 ]{ };
    int m_user_id{ };
    char m_steam_id[ 20 ]{ };
    char pad_0x00A8[ 0x10 ]{ };
    unsigned long m_un_steam_id{ };
    char m_friends_name[ 128 ]{ };
    bool m_is_bot{ };
    bool m_is_hltv{ };
    unsigned int m_custom_files[ 4 ]{ };
    unsigned char m_files_downloaded{ };
};

enum client_frame_stage_t {
    frame_undefined = -1,
    frame_start,
    frame_net_update_start,
    frame_net_update_postdataupdate_start,
    frame_net_update_postdataupdate_end,
    frame_net_update_end,
    frame_render_start,
    frame_render_end,
    frame_net_full_frame_update_on_remove
};

class i_engine_client {
public:
    VFUNC( bool( __thiscall* )( void*, int, player_info_t* ), get_player_info( const int ent_num, player_info_t* info ),
           8, ent_num, info );
    VFUNC( bool( __thiscall* )( void* ), con_is_visible( ), 11 );
    VFUNC( int( __thiscall* )( void* ), get_local_player( ), 12 );
    VFUNC( void( __thiscall* )( void*, c_vec3& ), get_view_angles( c_vec3& angle ), 18, angle );
    VFUNC( void( __thiscall* )( void*, c_vec3& ), set_view_angles( c_vec3& angle ), 19, angle );
    VFUNC( bool( __thiscall* )( void* ), is_in_game( ), 26 );
    VFUNC( bool( __thiscall* )( void* ), is_connected( ), 27 );
    VFUNC( const v_matrix&( __thiscall* ) ( void* ), world_to_screen_matrix( ), 37 );
    VFUNC( std::uintptr_t*( __thiscall* ) ( void* ), get_bsp_tree_query( ), 43 );
    VFUNC( void( __thiscall* )( void* ), fire_events( ), 59 );
    VFUNC( i_net_channel*( __thiscall* ) ( void* ), get_net_channel( ), 78 );
    VFUNC( c_steam_api_context*( __thiscall* ) ( void* ), get_steam_api_context( ), 185 );

    matrix_t& get_view_matrix( ) const {
        static auto view_matrix = *g_modules->m_client_dll.get_address( _( "CEngineClient::ScreenMatrix" ) ).add( 0x3 ).as< std::uintptr_t* >( );
        static auto ptr = view_matrix + 176;
        return *reinterpret_cast< matrix_t* >( ptr );
    };
};

#endif