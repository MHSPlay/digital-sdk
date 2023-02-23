#pragma once

#ifndef VALVE_CLIENT_UNK
#define VALVE_CLIENT_UNK

#include "handle_entity.hh"

class c_client_entity;
class c_collideable;
class c_client_renderable;
class c_client_networkable;
class c_entity;
class c_client_thinkable;
class c_client_alpha_property;

class c_client_unknown : public c_handle_entity {
public:
    virtual c_collideable* get_collideable( ) = 0;
    virtual c_client_networkable* get_client_networkable( ) = 0;
    virtual c_client_renderable* get_client_renderable( ) = 0;
    virtual c_client_entity* get_iclient_entity( ) = 0;
    virtual c_entity* get_base_entity( ) = 0;
    virtual c_client_thinkable* get_client_thinkable( ) = 0;
    virtual c_client_alpha_property* get_client_alpha_property( ) = 0;
};

#endif