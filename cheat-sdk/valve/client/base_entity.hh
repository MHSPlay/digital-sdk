#pragma once

#ifndef VALVE_BASE_ENTITY
#define VALVE_BASE_ENTITY

#include "../net_vars/net_vars.hh"
#include "../other/other.hh"
#include "../shared/shareddefs.hh"
#include "../shared/user_cmd.hh"

class c_entity : public c_client_entity {
public:
    NETVAR( int, team, _( "DT_BaseEntity->m_iTeamNum" ) );
    NETVAR( c_vec3, origin, _( "DT_BaseEntity->m_vecOrigin" ) );
    NETVAR_OFFSET( e_move_type, move_type, _( "DT_BaseEntity->m_nRenderMode" ), 0x1 );

    OFFSET( int, take_damage, 0x280 );

    VFUNC( data_map_t*( __thiscall* ) ( void* ), get_data_desc_map( ), 15 );
    VFUNC( data_map_t*( __thiscall* ) ( void* ), get_pred_desc_map( ), 17 );

    static void set_pred_random_seed( const c_user_cmd* cmd ) {
        static const auto sig = g_modules->m_client_dll.get_address( _( "C_BaseEntity::PredictionRandomSeed" ) ).add( 0x5 ).to< int* >( );

        if ( !cmd || !cmd->m_random_seed ) {
            *sig = -1;
            return;
        }

        *sig = cmd->m_random_seed;
    }

    void set_pred_player( c_entity* player ) {
        static const auto sig = g_modules->m_client_dll.get_address( _( "C_BaseEntity::PredictionPlayer" ) ).add( 0x4 ).to< c_entity** >( );
        *sig = player;
    }

    bool physics_run_think( const int index = 0 /* THINK_FIRE_ALL_FUNCTIONS */ ) {
        static const auto sig = g_modules->m_client_dll.get_address( _( "C_BaseEntity::PhysicsRunThink" ) ).as< 
            bool( __thiscall* )( void*, int ) >( );
        return sig( this, index );
    }

    void unk_think_func( const int a1 ) {
        static const auto sig = g_modules->m_client_dll.get_address( _( "C_BaseEntity::UnkThinkFunc" ) ).as< 
            void( __thiscall* )( void*, int ) >( );
        return sig( this, a1 );
    }

    bool is_breakable( ) {
        static const auto is_breakable = g_modules->m_client_dll.get_address( _( "C_BaseEntity::IsBreakableEntity" ) ).as< 
            bool( __thiscall* )( void* ) >( );

        const auto backup_take_damage = take_damage( );

        const auto client_class = get_client_class( );
        const auto network_name = client_class->m_network_name;

        // CBreakableSurface -> func_breakable_surf
        // CBreakable -> func_breakable
        if ( !strcmp( network_name, _( "CBreakableSurface" ) ) || !strcmp( network_name, _( "CBreakable" ) ) ) {
            take_damage( ) = damage_yes;
        }

        bool result = is_breakable( this );

        take_damage( ) = backup_take_damage;

        return result;
    }

    // @ida: module: client.dll; sig: 56 8B F1 8B 06 FF 90 ?? ?? ?? ?? 83 F8 01 75 04
    // bool is_bsp_model( ) {
    //	if ( get_solid( ) == 1 )
    //		return true;

    //	static const auto index = static_cast< int >( reinterpret_cast< std::uintptr_t >( this ) + 0x258 );
    //	const auto v3 = g_interfaces->m_model_info->get_model( index );
    //	const auto v2 = g_interfaces->m_model_info->get_model_type( v3 );

    //	if ( get_solid( ) != 6 || v2 != 1 )
    //		return true;

    //	return false;
    //}
};

#endif