#pragma once

#ifndef VALVE_TIER1_INTERFACES
#define VALVE_TIER1_INTERFACES

using create_interface_fn = void* ( *)( const char*, int* );
using instantiate_interface_fn = void* ( *)( );

class c_interface_reg {
public:
    c_interface_reg( instantiate_interface_fn fn, const char* name );
    instantiate_interface_fn m_create_fn{ };
    const char* m_name{ };
    c_interface_reg* m_next{ };
};

#endif