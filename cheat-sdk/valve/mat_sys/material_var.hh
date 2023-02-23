#pragma once

#ifndef VALVE_MAT_VAR
#define VALVE_MAT_VAR

#include "../../utils/memory/memory.hh"
#include "../../utils/math/vector.hh"

struct matrix_t;
enum e_material_var_indexes : int {
    set_vector_internal = 10,
    set_float = 4,
    set_int = 5,
    set_string = 6,
    set_matrix = 6,
    set_vector_component = 26,
    set_vector_internal_xyz = 11
};

class i_material_var {
    VFUNC( void( __thiscall* )( void*, float, float ), set_vector_internal( const float x, const float y ), 10, x, y );
public:
    VFUNC( void( __thiscall* )( void*, float ), set_float( const float val ), 4, val );
    VFUNC( void( __thiscall* )( void*, int ), set_int( const int val ), 5, val );
    VFUNC( void( __thiscall* )( void*, char const* ), set_string( char const* val ), 6, val );
    VFUNC( void( __thiscall* )( void*, float, float, float ),
           set_vector_internal( const float x, const float y, const float z ), 11, x, y, z );
    VFUNC( void( __thiscall* )( void*, float, int ), set_vector_component( const float val, const int comp ), 26, val,
           comp );

	void set_vector( const c_vec2& vector ) { return set_vector_internal( vector.x, vector.y ); }
	void set_vector( const c_vec3& vector ) { return set_vector_internal( vector.x, vector.y, vector.z ); }
};

#endif