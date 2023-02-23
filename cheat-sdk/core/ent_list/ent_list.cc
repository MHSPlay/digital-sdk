#include "ent_list.hh"

void c_ent_list::add( c_entity* const player ) {
    if ( !c_player::get_local( ) || !player || player == c_player::get_local( ) )
        return;

    const auto it = std::ranges::find( m_players, player );
    if ( it != m_players.cend( ) )
        return;

    const auto index = player->get_index( );
    if ( index < 1 || index > 64 )
        return;

    m_players.push_back( player );
}

void c_ent_list::remove( c_entity* const player ) {
    if ( !player )
        return;

    const auto it = std::ranges::find( m_players, player );
    if ( it == m_players.cend( ) )
        return;

    m_players.erase( it );
}

void c_ent_list::loop( const std::function< void( c_entity* ) >& fn ) const {
    for ( const auto& pl : m_players ) {
        if ( !c_player::get_local( ) || !pl || pl == c_player::get_local( ) )
            continue;

        fn( pl );
    }
}