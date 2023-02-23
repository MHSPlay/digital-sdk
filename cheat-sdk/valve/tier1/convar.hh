#pragma once

#ifndef VALVE_TIER1_CONVAR
#define VALVE_TIER1_CONVAR

#include "../../utils/math/utl.hh"
#include "../../utils/memory/memory.hh"

class i_convar;
using fn_change_callback_t = void ( * )( i_convar*, const char*, float );

class i_convar {
public:
    VFUNC( const char*( __thiscall* ) ( void* ), get_str( ), 11 );
    VFUNC( float( __thiscall* )( void* ), get_float( ), 12 );
    VFUNC( int( __thiscall* )( void* ), get_int( ), 13 );
    VFUNC( void( __thiscall* )( void*, const char* ), set_value( const char* value ), 14, value );
    VFUNC( void( __thiscall* )( void*, float ), set_value( const float value ), 15, value );
    VFUNC( void( __thiscall* )( void*, int ), set_value( const int value ), 16, value );
private:
    void* dword0{ };
public:
    void* m_next{ };
    bool m_registered{ };
    const char* m_name{ };
    const char* m_help_string{ };
    int m_flags{ };
private:
    void* dword18{ };
public:
    i_convar* m_parent{ };
    const char* m_default_value{ };
private:
    char gap24[ 48 ]{ };
    void* dword54{ };
    char gap58[ 8 ]{ };
public:
    c_utl_vector< fn_change_callback_t > m_fn_change_callbacks{ };
};

#endif