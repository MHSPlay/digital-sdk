#pragma once

#ifndef MEMORY_ADR
#define MEMORY_ADR

#include <cstddef>
#include <cstdint>

class c_address {
public:
    c_address( ) = default;
    c_address( const std::size_t address ) : m_address{ address } {}
    c_address( void* address ) : m_address{ reinterpret_cast< std::size_t >( address ) } {}

    operator std::size_t( ) const { return m_address; }
    operator void*( ) const { return reinterpret_cast< void* >( m_address ); }

    bool operator==( const c_address address ) const { return as< std::size_t >( ) == address.as< std::size_t >( ); }
    bool operator!=( const c_address address ) const { return as< std::size_t >( ) != address.as< std::size_t >( ); }

    [[nodiscard]] bool is_valid( ) const { return m_address && this; }

    template < typename T = c_address >
    [[nodiscard]] T to( ) const { return *( T* )m_address; }

    template < typename T = c_address >
    [[nodiscard]] T as( ) const { return m_address ? T( m_address ) : T( ); }

    template < typename T = c_address >
    [[nodiscard]] T at( const std::size_t offset ) const { return m_address ? *( T* )( m_address + offset ) : T( ); }

    template < typename T = c_address >
    [[nodiscard]] T add( const std::size_t offset ) const { return m_address ? T( m_address + offset ) : T( ); }

    template < typename T = c_address >
    [[nodiscard]] T sub( const std::size_t offset ) const { return m_address ? T( m_address - offset ) : T( ); }

    template < typename T = c_address >
    [[nodiscard]] T get( std::size_t dereferences = 1 ) const {
        if ( !m_address )
            return T( );

        std::size_t object = m_address;

        while ( dereferences-- ) {
            if ( !object )
                continue;

            object = *reinterpret_cast< std::size_t* >( object );
        }

        return ( T )object;
    }

    template < typename T = c_address >
    [[nodiscard]] T relative( const std::size_t offset = 0x1 ) const {
        if ( !m_address )
            return T( );

        std::size_t new_address = m_address + offset;
        std::int32_t relative_offset = *reinterpret_cast< std::int32_t* >( new_address );

        if ( !relative_offset )
            return T( );

        return ( T )( new_address + sizeof( std::size_t ) + relative_offset );
    }

    template < typename T = std::size_t >
    void set( const T& value ) const {
        if ( !m_address )
            return;

        *( T* )m_address = value;
    }
private:
    std::size_t m_address{ };
};

#endif