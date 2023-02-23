#pragma once

#ifndef VALVE_BASE_PLAYER
#define VALVE_BASE_PLAYER

#include "../../context.hh"
#include "../modules/modules.hh"
#include "../net_vars/net_vars.hh"
#include "base_entity.hh"

class c_weapon;

class c_player : public c_entity {
public:
    NETVAR( int, health, _( "DT_BasePlayer->m_iHealth" ) );
    NETVAR( int, tick_base, _( "DT_BasePlayer->m_nTickBase" ) );
    NETVAR( int, flags, _( "DT_BasePlayer->m_fFlags" ) );
    NETVAR( int, life_state, _( "DT_BasePlayer->m_lifeState" ) );
    NETVAR( int, armor_value, _( "DT_CSPlayer->m_ArmorValue" ) );
    NETVAR( bool, is_helmet, _( "DT_CSPlayer->m_bHasHelmet" ) );
    NETVAR( bool, is_heavy_armor, _( "DT_CSPlayer->m_bHasHeavyArmor" ) );
    NETVAR( bool, is_immune, _( "DT_CSPlayer->m_bGunGameImmunity" ) );
    NETVAR( float, duck_amount, _( "DT_BasePlayer->m_flDuckAmount" ) );
    NETVAR( float, duck_speed, _( "DT_BasePlayer->m_flDuckSpeed" ) );
    NETVAR( c_handle< c_weapon >, active_weapon_handle, _( "DT_BaseCombatCharacter->m_hActiveWeapon" ) );

    OFFSET( int, button_released, 0x3204 );
    OFFSET( int, button_pressed, 0x3200 );
    OFFSET( int, buttons, 0x3208 );
    OFFSET( int, button_last, 0x31FC );
    OFFSET( int, button_forced, 0x3344 );
    OFFSET( int, button_disabled, 0x3340 );
    OFFSET( int, impulse, 0x320C );
    OFFSET( bool, unk_awol_thing, 0x9AE1 );
    OFFSET( c_user_cmd*, current_cmd, 0x3348 );
    OFFSET( c_user_cmd*, last_cmd, 0x3298 );
    OFFSET( int, next_think_tick, 0xFC );

    VFUNC( void( __thiscall* )( void* ), think( ), 139 );
    VFUNC( void( __thiscall* )( void* ), pre_think( ), 318 );
    VFUNC( void( __thiscall* )( void* ), post_think( ), 319 );
    VFUNC( bool( __thiscall* )( void* ), is_alive( ), 156 );
    VFUNC( bool( __thiscall* )( void* ), is_player( ), 158 );

    [[nodiscard]] bool is_armored( const int hitgroup ) const {
        switch ( hitgroup ) {
            case hitgroup_head:
                return this->is_helmet( );
            case hitgroup_generic:
            case hitgroup_chest:
            case hitgroup_stomach:
            case hitgroup_leftarm:
            case hitgroup_rightarm:
                return true;
            default:
                return false;
        }
    }

    void update_button_state( const int user_cmd_button_mask ) const {
        button_last( ) = buttons( );
        buttons( ) = user_cmd_button_mask;

        const auto& buttons_changed = button_last( ) ^ buttons( );
        button_pressed( ) = buttons_changed & buttons( );
        button_released( ) = buttons_changed & ~buttons( );
    }

    [[nodiscard]] c_weapon* active_weapon( ) const {
        const auto& handle = active_weapon_handle( );
        return handle ? handle.get( ) : nullptr;
    }

    static c_player* get_local( ) {
        auto sig = g_modules->m_client_dll.get_address( _( "C_BasePlayer::GetLocalPlayer" ) ).add( 2 ).get< c_player* >( 2 );
        return sig;
    }
};

#endif