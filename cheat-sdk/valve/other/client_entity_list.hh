#pragma once

#ifndef VALVE_CLIENT_ENTITY_LIST
#define VALVE_CLIENT_ENTITY_LIST

#include "base_handle.hh"
#include "client_entity.hh"
#include "../../utils/memory/memory.hh"

class i_client_entity_list {
public:
    VFUNC( c_client_entity* ( __thiscall* )( void*, int ),
           get_client_entity( const int entity_number ), 3,
           entity_number
        );

    VFUNC( void* ( __thiscall* )( void*, c_base_handle ),
           get_client_entity_from_handle( const c_base_handle& entity ), 4,
           entity
        );
};

#endif