#pragma once

#ifndef VALVE_INTERFACES
#define VALVE_INTERFACES

#include "../modules/modules.hh"
#include "../other/client_entity_list.hh"
#include "../client/client.hh"
#include "../data_cache/data_cache.hh"
#include "../engine/engine.hh"
#include "../server/server.hh"
#include "../tier1/tier1.hh"
#include "../shared/shared.hh"
#include "../steam/steam.hh"
#include "../other/phys_props.hh"
#include "../vgui/vgui.hh"
#include "../mat_sys/mat_sys.hh"
#include "../vstdlib/vstdlib.hh"

class c_interfaces final {
    template < typename T >
    T get( const c_module_info& the_module, std::string_view interface_name );
public:
    i_base_client_dll* m_client{ };
    i_client_entity_list* m_entity_list{ };
    i_move_helper* m_move_helper{ };
    i_game_movement* m_game_movement{ };
    i_engine_client* m_engine{ };
    c_global_vars* m_globals{ };
    i_engine_trace* m_trace{ };
    c_client_state* m_client_state{ };
    c_move_data* m_move_data{ };
    i_input* m_input{ };
    i_prediction* m_prediction{ };
    i_client_mode* m_client_mode{ };
    h_steam_user m_steam_user{ };
    h_steam_pipe m_steam_pipe{ };
    i_steam_client* m_steam_client{ };
    i_steam_screenshots* m_steam_screenshots{ };
    i_cvar* m_cvar{ };
    i_phys_surface_props* m_phys_surface_props{ };
    IDirect3DDevice9* m_device{ };
    i_surface* m_surface{ };
    c_engine_vgui* m_engine_vgui{ };
    i_material_system* m_material_system{ };
    c_key_values_system* m_key_values_system{ };
    i_model_render* m_model_render{ };

    void init( );
};

inline const std::unique_ptr< c_interfaces > g_interfaces{ new c_interfaces( ) };

#endif