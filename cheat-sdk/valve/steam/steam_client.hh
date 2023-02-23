#pragma once

#ifndef VALVE_STEAM_CLIENT
#define VALVE_STEAM_CLIENT

#include "../../utils/memory/memory.hh"
#include "steam_client.hh"

using h_steam_pipe = int;
using h_steam_user = int;

#define ARGS h_steam_user steam_user, h_steam_pipe steam_pipe, const char *version

class i_steam_client {
public:
    VFUNC( h_steam_pipe( __thiscall* )( void* ), create_steam_pipe( ), 0 );
    VFUNC( void*( __thiscall* )( void*, ARGS ), 
           get_steam_generic_interface( ARGS ), 12, steam_user, steam_pipe,
           version );
};

#endif