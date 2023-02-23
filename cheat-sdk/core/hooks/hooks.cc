#include "hooks.hh"

void c_hooks::init( ) const {
    m_client.init( );
    m_engine.init( );
    m_client_ent_list.init( );
    m_direct_device.init( );
    m_surface.init( );
    m_model_render.init( );
}