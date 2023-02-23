#pragma once

#ifndef STEAM_API_H
#define STEAM_API_H

class i_steam_screenshots;
class i_steam_client;

class c_steam_api_context {
public:
    i_steam_client* m_steam_client{ };
    void* m_steam_user{ };
    void* m_steam_friends{ };
    void* m_steam_utils{ };
    void* m_steam_matchmaking{ };
    void* m_steam_game_search{ };
    void* m_steam_user_stats{ };
    void* m_steam_apps{ };
    void* m_steam_matchmaking_servers{ };
    void* m_steam_networking{ };
    void* m_steam_remote_storage{ };
    i_steam_screenshots* m_steam_steam_screenshots{ };
    void* m_steam_http{ };
    void* m_controller{ };
    void* m_steam_ugc{ };
    void* m_steam_app_list{ };
    void* m_steam_music{ };
    void* m_steam_music_remote{ };
    void* m_steam_html_surface{ };
    void* m_steam_inventory{ };
    void* m_steam_video{ };
    void* m_steam_parental_settings{ };
    void* m_steam_input{ };
};

#endif