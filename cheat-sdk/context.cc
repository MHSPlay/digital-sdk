#include "context.hh"
#include "core/hooks/hooks.hh"
#include "core/render/render.hh"
#include "core/features/chams/chams.hh"

extern "C" BOOL WINAPI _CRT_INIT( HMODULE moduleHandle, DWORD reason, LPVOID reserved );

DWORD c_ctx::dllmain_t::load( void* param ) {
    const auto module = static_cast< HMODULE >( param );
    while ( !( g_ctx->m_hwnd = FindWindowA( _( "Valve001" ), nullptr ) ) )
        std::this_thread::sleep_for( std::chrono::seconds( 2 ) );

#if DEBUG_CONSOLE
    g_console->attach( );
#endif
    log_print( "hello user!" );

    if ( !g_pe->init( ) )
        throw std::runtime_error( "failed to init pe" );

    if ( !g_modules->init( ) )
        throw std::runtime_error( "failed to init modules" );

    g_interfaces->init( );
    g_net_vars->init( );
    g_chams->init_material( );
    g_hooks->set_wnd_proc( );
    g_hooks->init( );

    while ( !g_ctx->m_dllmain.m_unload ) // f11
        Sleep( 500 );

    unload( module );
    return 0;
}

// @note: soon in next upd...
void c_ctx::dllmain_t::unload( const HMODULE base_module ) {
    // unload cheat core.
    /*
     * console
     * hooks
     * etc
     */

    // unload cheat module from game.
    _CRT_INIT( base_module, DLL_PROCESS_DETACH, nullptr );
    FreeLibraryAndExitThread( base_module, 0 );
}

bool c_ctx::dllmain_t::create_thread( DWORD WINAPI function( void* ), void* parameter ) {
    HANDLE handle = CreateThread( nullptr, 0, function, parameter, 0, nullptr );

    if ( !handle )
        return false;

    CloseHandle( handle );
    return true;
}