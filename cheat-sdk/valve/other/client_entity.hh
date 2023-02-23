#pragma once

#ifndef VALVE_CLIENT_ENTITY
#define VALVE_CLIENT_ENTITY

#include "client_networkable.hh"
#include "client_unknown.hh"

struct model_t;
class c_vec3;

class c_client_thinkable {
public:
    virtual c_client_unknown* get_client_unknown( ) = 0;
    virtual void client_think( ) = 0;
    virtual void* get_think_handle( ) = 0;
    virtual void set_think_handle( void* think ) = 0;
    virtual void release( ) = 0;
};

class c_client_renderable {
public:
    virtual c_client_unknown* get_client_unknown( ) = 0;
    virtual c_vec3& get_render_origin( ) = 0;
    virtual const c_vec3& get_render_angles( ) = 0;
    virtual bool should_draw( ) = 0;
    virtual int get_render_flags( ) = 0;
    virtual void unknown0( ) const = 0;
    virtual std::uint16_t get_shadow_handle( ) const = 0;
    virtual std::uint16_t& get_render_handle( ) = 0;
    virtual const model_t* get_model( ) const = 0;
    virtual int draw_model( int flags, uint8_t alpha ) = 0;
    virtual int get_body( ) = 0;
    virtual void get_color_modulation( float* color ) = 0;
    virtual bool lod_test( ) = 0;
    virtual bool setup_bones( matrix_t* bones, int max, int mask, float time ) = 0;
    virtual void setup_weights( const matrix_t* bones, int count, float* weights, float* delayed_weights ) = 0;
    virtual void do_animation_events( ) = 0;
    virtual void* get_pvs_notify_interface( ) = 0;
    virtual void get_render_bounds( c_vec3& mins, c_vec3& maxs ) = 0;
    virtual void get_render_bounds_worldspace( c_vec3& mins, c_vec3& maxs ) = 0;
    virtual void get_shadow_render_bounds( c_vec3& mins, c_vec3& maxs, int type ) = 0;
    virtual bool should_receive_projected_textures( int flags ) = 0;
    virtual bool get_shadow_cast_distance( float* dist, int type ) const = 0;
    virtual bool get_shadow_cast_direction( c_vec3* direction, int type ) const = 0;
    virtual bool is_shadow_dirty( ) = 0;
    virtual void mark_shadow_dirty( bool dirty ) = 0;
    virtual c_client_renderable* get_shadow_parent( ) = 0;
    virtual c_client_renderable* first_shadow_child( ) = 0;
    virtual c_client_renderable* next_shadow_peer( ) = 0;
    virtual int shadow_cast_type( ) = 0;
    virtual void create_model_instance( ) = 0;
    virtual std::uint16_t get_model_instance( ) = 0;
    virtual const matrix_t& renderable_to_world_transform( ) = 0;
    virtual int lookup_attachment( const char* name ) = 0;
    virtual bool get_attachment( int index, c_vec3& origin, c_vec3& angles ) = 0;
    virtual bool get_attachment( int index, matrix_t& matrix ) = 0;
    virtual float* get_render_clip_plane( ) = 0;
    virtual int get_skin( ) = 0;
    virtual void on_threaded_draw_setup( ) = 0;
    virtual bool uses_flex_delayed_weights( ) = 0;
    virtual void record_tool_message( ) = 0;
    virtual bool should_draw_for_split_screen_user( int slot ) = 0;
    virtual std::uint8_t override_alpha_modulation( uint8_t alpha ) = 0;
    virtual std::uint8_t override_shadow_alpha_modulation( uint8_t alpha ) = 0;
};

class c_client_entity
    : public c_client_unknown
    , public c_client_renderable
    , public c_client_networkable
    , public c_client_thinkable {
public:
    void release( void ) override = 0;
    virtual const c_vec3& get_abs_origin( void ) const = 0;
    virtual const c_vec3& get_abs_angles( void ) const = 0;
};

#endif