#include "../../menu/menu.hh"
#include "../hooks.hh"

void c_hooks::surface_t::init( ) {
    g_modules->m_vguimatsurface_dll.hook_function( _( "CMatSystemSurface::LockCursor" ), &lock_cursor );
}

void __fastcall c_hooks::surface_t::lock_cursor( i_surface* surface, void* edx ) {
    static const auto og = g_modules->m_vguimatsurface_dll.get<decltype( &lock_cursor )>( _( "CMatSystemSurface::LockCursor" ) );
    return g_menu->opened( ) ? surface->unlock_cursor( ) : og( surface, edx );
}