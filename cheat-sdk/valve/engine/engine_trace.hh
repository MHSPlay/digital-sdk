#pragma once

#ifndef VALVE_ENGINE_TRACE
#define VALVE_ENGINE_TRACE

#include "../other/bsp_flags.hh"
#include "../other/cmodel.hh"
#include "../other/game_trace.hh"
#include "collideable.hh"

enum trace_type_t {
    trace_everything = 0,
    trace_world_only,
    trace_entities_only,
    trace_everything_filter_props,
};

class i_trace_filter {
public:
    virtual bool should_hit_entity( void* entity, int contents_mask ) = 0;
    virtual trace_type_t get_trace_type( ) const = 0;
};

class c_trace_filter : public i_trace_filter {
public:
    [[nodiscard]] trace_type_t get_trace_type( ) const override { return trace_everything; }
};

class i_engine_trace {
public:
    virtual int get_point_contents( const c_vec3& abs_position, int contents_mask = mask_all,
                                    c_handle_entity** entity = nullptr ) = 0;
    virtual int get_point_contents_world_only( const c_vec3& abs_position, int contents_mask = mask_all ) = 0;
    virtual int get_point_contents_collideable( c_collideable* collide, const c_vec3& abs_position ) = 0;
    virtual void clip_ray_to_entity( const ray_t& ray, unsigned int mask, c_handle_entity* ent,
                                     c_game_trace* trace ) = 0;
    virtual void clip_ray_to_collideable( const ray_t& ray, unsigned int mask, c_collideable* collide,
                                          c_game_trace* trace ) = 0;
    virtual void trace_ray( const ray_t& ray, unsigned int mask, i_trace_filter* trace_filter,
                            c_game_trace* trace ) = 0;
};

#endif