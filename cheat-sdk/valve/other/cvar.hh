#pragma once

#ifndef VALVE_CVAR
#define VALVE_CVAR

#include "../../utils/memory/memory.hh"

class i_convar;

class i_cvar {
public:
    VFUNC( i_convar* ( __thiscall* )( void*, const char* ),
           find_var( const char* name ), 16,
           name
        );
};

#endif