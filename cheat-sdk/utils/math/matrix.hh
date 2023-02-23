#pragma once

#ifndef MATH_MATRIX
#define MATH_MATRIX

#include "vector.hh"

struct matrix_t {
    matrix_t( ) = default;

    matrix_t( const float m00, const float m01, const float m02, const float m03, const float m10, const float m11,
              const float m12, const float m13, const float m20, const float m21, const float m22, const float m23 ) {
        m_mat_val[ 0 ][ 0 ] = m00;
        m_mat_val[ 0 ][ 1 ] = m01;
        m_mat_val[ 0 ][ 2 ] = m02;
        m_mat_val[ 0 ][ 3 ] = m03;
        m_mat_val[ 1 ][ 0 ] = m10;
        m_mat_val[ 1 ][ 1 ] = m11;
        m_mat_val[ 1 ][ 2 ] = m12;
        m_mat_val[ 1 ][ 3 ] = m13;
        m_mat_val[ 2 ][ 0 ] = m20;
        m_mat_val[ 2 ][ 1 ] = m21;
        m_mat_val[ 2 ][ 2 ] = m22;
        m_mat_val[ 2 ][ 3 ] = m23;
    }

    //-----------------------------------------------------------------------------
    // Creates a matrix where the x axis = forward
    // the y axis = left, and the z axis = up
    //-----------------------------------------------------------------------------
    void init( const c_vec3& x_axis, const c_vec3& y_axis, const c_vec3& z_axis, const c_vec3& origin ) {
        m_mat_val[ 0 ][ 0 ] = x_axis.x;
        m_mat_val[ 0 ][ 1 ] = y_axis.x;
        m_mat_val[ 0 ][ 2 ] = z_axis.x;
        m_mat_val[ 0 ][ 3 ] = origin.x;
        m_mat_val[ 1 ][ 0 ] = x_axis.y;
        m_mat_val[ 1 ][ 1 ] = y_axis.y;
        m_mat_val[ 1 ][ 2 ] = z_axis.y;
        m_mat_val[ 1 ][ 3 ] = origin.y;
        m_mat_val[ 2 ][ 0 ] = x_axis.z;
        m_mat_val[ 2 ][ 1 ] = y_axis.z;
        m_mat_val[ 2 ][ 2 ] = z_axis.z;
        m_mat_val[ 2 ][ 3 ] = origin.z;
    }

    //-----------------------------------------------------------------------------
    // Creates a matrix where the x axis = forward
    // the y axis = left, and the z axis = up
    //-----------------------------------------------------------------------------
    matrix_t( const c_vec3& x_axis, const c_vec3& y_axis, const c_vec3& z_axis, const c_vec3& origin ) {
        init( x_axis, y_axis, z_axis, origin );
    }

    constexpr void set_forward( const c_vec3& forward ) {
        this->m_mat_val[ 0 ][ 0 ] = forward.x;
        this->m_mat_val[ 1 ][ 0 ] = forward.y;
        this->m_mat_val[ 2 ][ 0 ] = forward.z;
    }

    constexpr void set_left( const c_vec3& left ) {
        this->m_mat_val[ 0 ][ 1 ] = left.x;
        this->m_mat_val[ 1 ][ 1 ] = left.y;
        this->m_mat_val[ 2 ][ 1 ] = left.z;
    }

    constexpr void set_up( const c_vec3& up ) {
        this->m_mat_val[ 0 ][ 2 ] = up.x;
        this->m_mat_val[ 1 ][ 2 ] = up.y;
        this->m_mat_val[ 2 ][ 2 ] = up.z;
    }

    constexpr void set_origin( const c_vec3& origin ) {
        this->m_mat_val[ 0 ][ 3 ] = origin.x;
        this->m_mat_val[ 1 ][ 3 ] = origin.y;
        this->m_mat_val[ 2 ][ 3 ] = origin.z;
    }

    void invalidate( ) {
        for ( int i = 0; i < 3; i++ ) {
            for ( int j = 0; j < 4; j++ ) { m_mat_val[ i ][ j ] = std::numeric_limits< float >::infinity( ); }
        }
    }

    __forceinline c_vec3 get_column( const int column ) const {
        return c_vec3( m_mat_val[ 0 ][ column ], m_mat_val[ 1 ][ column ], m_mat_val[ 2 ][ column ] );
    }

    __forceinline void set_column( const c_vec3& value, const int column ) {
        m_mat_val[ 0 ][ column ] = value.x;
        m_mat_val[ 1 ][ column ] = value.y;
        m_mat_val[ 2 ][ column ] = value.z;
    }

    __forceinline void scale( const int i, const float scale ) {
        m_mat_val[ i ][ 0 ] *= scale;
        m_mat_val[ i ][ 1 ] *= scale;
        m_mat_val[ i ][ 2 ] *= scale;
    }

    void multiply( const matrix_t& other ) {
        m_mat_val[ 0 ][ 0 ] = m_mat_val[ 0 ][ 0 ] * other.m_mat_val[ 0 ][ 0 ]
            + m_mat_val[ 0 ][ 1 ] * other.m_mat_val[ 1 ][ 0 ] + m_mat_val[ 0 ][ 2 ] * other.m_mat_val[ 2 ][ 0 ];
        m_mat_val[ 0 ][ 1 ] = m_mat_val[ 0 ][ 0 ] * other.m_mat_val[ 0 ][ 1 ]
            + m_mat_val[ 0 ][ 1 ] * other.m_mat_val[ 1 ][ 1 ] + m_mat_val[ 0 ][ 2 ] * other.m_mat_val[ 2 ][ 1 ];
        m_mat_val[ 0 ][ 2 ] = m_mat_val[ 0 ][ 0 ] * other.m_mat_val[ 0 ][ 2 ]
            + m_mat_val[ 0 ][ 1 ] * other.m_mat_val[ 1 ][ 2 ] + m_mat_val[ 0 ][ 2 ] * other.m_mat_val[ 2 ][ 2 ];
        m_mat_val[ 0 ][ 3 ] = m_mat_val[ 0 ][ 0 ] * other.m_mat_val[ 0 ][ 3 ]
            + m_mat_val[ 0 ][ 1 ] * other.m_mat_val[ 1 ][ 3 ] + m_mat_val[ 0 ][ 2 ] * other.m_mat_val[ 2 ][ 3 ]
            + m_mat_val[ 0 ][ 3 ];
        m_mat_val[ 1 ][ 0 ] = m_mat_val[ 1 ][ 0 ] * other.m_mat_val[ 0 ][ 0 ]
            + m_mat_val[ 1 ][ 1 ] * other.m_mat_val[ 1 ][ 0 ] + m_mat_val[ 1 ][ 2 ] * other.m_mat_val[ 2 ][ 0 ];
        m_mat_val[ 1 ][ 1 ] = m_mat_val[ 1 ][ 0 ] * other.m_mat_val[ 0 ][ 1 ]
            + m_mat_val[ 1 ][ 1 ] * other.m_mat_val[ 1 ][ 1 ] + m_mat_val[ 1 ][ 2 ] * other.m_mat_val[ 2 ][ 1 ];
        m_mat_val[ 1 ][ 2 ] = m_mat_val[ 1 ][ 0 ] * other.m_mat_val[ 0 ][ 2 ]
            + m_mat_val[ 1 ][ 1 ] * other.m_mat_val[ 1 ][ 2 ] + m_mat_val[ 1 ][ 2 ] * other.m_mat_val[ 2 ][ 2 ];
        m_mat_val[ 1 ][ 3 ] = m_mat_val[ 1 ][ 0 ] * other.m_mat_val[ 0 ][ 3 ]
            + m_mat_val[ 1 ][ 1 ] * other.m_mat_val[ 1 ][ 3 ] + m_mat_val[ 1 ][ 2 ] * other.m_mat_val[ 2 ][ 3 ]
            + m_mat_val[ 1 ][ 3 ];
        m_mat_val[ 2 ][ 0 ] = m_mat_val[ 2 ][ 0 ] * other.m_mat_val[ 0 ][ 0 ]
            + m_mat_val[ 2 ][ 1 ] * other.m_mat_val[ 1 ][ 0 ] + m_mat_val[ 2 ][ 2 ] * other.m_mat_val[ 2 ][ 0 ];
        m_mat_val[ 2 ][ 1 ] = m_mat_val[ 2 ][ 0 ] * other.m_mat_val[ 0 ][ 1 ]
            + m_mat_val[ 2 ][ 1 ] * other.m_mat_val[ 1 ][ 1 ] + m_mat_val[ 2 ][ 2 ] * other.m_mat_val[ 2 ][ 1 ];
        m_mat_val[ 2 ][ 2 ] = m_mat_val[ 2 ][ 0 ] * other.m_mat_val[ 0 ][ 2 ]
            + m_mat_val[ 2 ][ 1 ] * other.m_mat_val[ 1 ][ 2 ] + m_mat_val[ 2 ][ 2 ] * other.m_mat_val[ 2 ][ 2 ];
        m_mat_val[ 2 ][ 3 ] = m_mat_val[ 2 ][ 0 ] * other.m_mat_val[ 0 ][ 3 ]
            + m_mat_val[ 2 ][ 1 ] * other.m_mat_val[ 1 ][ 3 ] + m_mat_val[ 2 ][ 2 ] * other.m_mat_val[ 2 ][ 3 ]
            + m_mat_val[ 2 ][ 3 ];
    }

    void matrix_set_column( const c_vec3& in, const int column ) {
        m_mat_val[ 0 ][ column ] = in.x;
        m_mat_val[ 1 ][ column ] = in.y;
        m_mat_val[ 2 ][ column ] = in.z;
    }

    [[nodiscard]] c_vec3 get_x_axis( ) const { return at( 0 ); }

    [[nodiscard]] c_vec3 get_y_axis( ) const { return at( 1 ); }

    [[nodiscard]] c_vec3 get_z_axis( ) const { return at( 2 ); }

    [[nodiscard]] c_vec3 get_origin( ) const { return at( 3 ); }

    [[nodiscard]] c_vec3 at( const int i ) const {
        return c_vec3{ m_mat_val[ 0 ][ i ], m_mat_val[ 1 ][ i ], m_mat_val[ 2 ][ i ] };
    }

    float* operator[]( const int i ) { return m_mat_val[ i ]; }

    const float* operator[]( const int i ) const { return m_mat_val[ i ]; }

    float* base( ) { return &m_mat_val[ 0 ][ 0 ]; }

    [[nodiscard]] const float* base( ) const { return &m_mat_val[ 0 ][ 0 ]; }

    float m_mat_val[ 3 ][ 4 ]{ };
};

class v_matrix {
public:
    v_matrix( );
    v_matrix( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20,
              float m21, float m22, float m23, float m30, float m31, float m32, float m33 );

    // Creates a matrix where the x axis = forward
    // the y axis = left, and the z axis = up
    v_matrix( const c_vec3& forward, const c_vec3& left, const c_vec3& up );

    // Construct from a 3x4 matrix
    v_matrix( const matrix_t& matrix3x4 );

    // Set the values in the matrix.
    void init( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20,
               float m21, float m22, float m23, float m30, float m31, float m32, float m33 );

    // Initialize from a 3x4
    void init( const matrix_t& matrix3x4 );

    // array access
    float* operator[]( const int i ) { return m[ i ]; }

    const float* operator[]( const int i ) const { return m[ i ]; }

    // Get a pointer to m[ 0 ][ 0 ]
    float* base( ) { return &m[ 0 ][ 0 ]; }

    [[nodiscard]] const float* base( ) const { return &m[ 0 ][ 0 ]; }

    void set_left( const c_vec3& left );
    void set_up( const c_vec3& up );
    void set_forward( const c_vec3& forward );

    void get_basis_vectors( c_vec3& forward, c_vec3& left, c_vec3& up ) const;
    void set_basis_vectors( const c_vec3& forward, const c_vec3& left, const c_vec3& up );

    // Get/Set the translation.
    c_vec3& get_translation( c_vec3& trans ) const;
    void set_translation( const c_vec3& trans );

    void pre_translate( const c_vec3& trans );
    void post_translate( const c_vec3& trans );

    matrix_t& as3x4( );
    [[nodiscard]] const matrix_t& as3x4( ) const;
    void copy_from3x4( const matrix_t& m3x4 );
    void set3x4( matrix_t& matrix3x4 ) const;

    bool operator==( const v_matrix& src ) const;

    bool operator!=( const v_matrix& src ) const { return !( *this == src ); }

    // Access the basis vectors.
    [[nodiscard]] c_vec3 get_left( ) const;
    [[nodiscard]] c_vec3 get_up( ) const;
    [[nodiscard]] c_vec3 get_forward( ) const;
    [[nodiscard]] c_vec3 get_translation( ) const;

    // Multiply by a 3D Vector (same as operator*).
    void v3_mul( const c_vec3& in, c_vec3& out ) const;

    // Multiply by a 4D Vector.
    // void  V4Mul( const c_vec4 &in, c_vec4 &out ) const;

    // Applies the rotation (ignores translation in the matrix). (This just calls VMul3x3).
    [[nodiscard]] c_vec3 apply_rotation( const c_vec3& vec ) const;

    // Multiply by a Vector (divides by w, assumes input w is 1).
    c_vec3 operator*( const c_vec3& vec ) const;

    // Multiply by the upper 3x3 part of the matrix (ie: only apply rotation).
    [[nodiscard]] c_vec3 v_mul3x3( const c_vec3& vec ) const;

    // Apply the inverse (transposed) rotation (only works on pure rotation matrix)
    [[nodiscard]] c_vec3 v_mul3x3transpose( const c_vec3& vec ) const;

    // Multiply by the upper 3 rows.
    [[nodiscard]] c_vec3 v_mul4x3( const c_vec3& vec ) const;

    // Apply the inverse (transposed) transformation (only works on pure rotation/translation)
    [[nodiscard]] c_vec3 v_mul4x3_transpose( const c_vec3& vec ) const;

    // matrix->matrix operations.
    v_matrix& operator=( const v_matrix& other );

    // Add two matrices.
    const v_matrix& operator+=( const v_matrix& other );

    // Add/Subtract two matrices.
    v_matrix operator+( const v_matrix& other ) const;
    v_matrix operator-( const v_matrix& other ) const;

    // Negation.
    v_matrix operator-( ) const;

    // Return inverse matrix. Be careful because the results are undefined
    // if the matrix doesn't have an inverse (ie: InverseGeneral returns false).
    v_matrix operator~( ) const;

    // matrix operations.

    // Set to identity.
    void identity( );
    [[nodiscard]] bool is_identity( ) const;

    // The matrix.
    float m[ 4 ][ 4 ];
};

#endif