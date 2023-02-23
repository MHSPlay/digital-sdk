#pragma once

#ifndef VALVE_CLIENT_NET
#define VALVE_CLIENT_NET

class c_client_unknown;
class c_client_class;

class c_bf_read;

class c_client_networkable {
public:
    virtual c_client_unknown* get_client_unknown( ) = 0;
    virtual void release( ) = 0;
    virtual c_client_class* get_client_class( ) = 0;
    virtual void notify_should_transmit( int state ) = 0;
    virtual void on_pre_data_changed( int update_type ) = 0;
    virtual void on_data_changed( int update_type ) = 0;
    virtual void pre_data_update( int update_type ) = 0;
    virtual void post_data_update( int update_type ) = 0;
    virtual void unknown0( ) = 0;
    virtual bool is_dormant( ) = 0;
    virtual int get_index( ) const = 0;
    virtual void receive_message( int class_id, c_bf_read& msg ) = 0;
    virtual void* get_data_table_base_ptr( ) = 0;
    virtual void set_destroyed_on_recreate_entities( ) = 0;
};

#endif