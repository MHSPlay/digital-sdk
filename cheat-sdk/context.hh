#pragma once

#ifndef CTX_H
#define CTX_H

#include <Windows.h>
#include <cmath>
#include <vector>
#include <array>
#include <cstdint>
#include <deque>
#include <memory>
#include <string>
#include <thread>
#include <map>
#include <stdexcept>
#include <functional>
#include <ranges>

#include "deps/xor/xor.hh"
#include "utils/utils.hh"
#include "valve/valve.hh"
#include "core/ent_list/ent_list.hh"

#include <d3d9.h>
#pragma comment( lib, "d3d9.lib" )

class c_ctx final {
public:
    struct dllmain_t {
        static bool create_thread( DWORD WINAPI function( void* ), void* parameter );
        static DWORD WINAPI load( void* param );
        static void unload( HMODULE base_module );
        bool m_unload{ };
    } m_dllmain;

    HWND m_hwnd{ };
    bool m_in_move{ }, m_send_packet{ };
    c_user_cmd* m_cmd{ };
};

inline const std::unique_ptr< c_ctx > g_ctx{ new c_ctx( ) };

#endif