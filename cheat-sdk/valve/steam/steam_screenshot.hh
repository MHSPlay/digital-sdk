#pragma once

#ifndef VALVE_STEAM_SC
#define VALVE_STEAM_SC

#include  "../../utils/memory/memory.hh"

class i_steam_screenshots {
public:
    VFUNC( std::uint32_t( __thiscall* )( void*, void*, std::uint32_t, int, int ),
           write_screenshot( void* pub_rgb, const std::uint32_t cub_rgb, const int width, const int height ), 0,
           pub_rgb, cub_rgb, width, height
        );
};

#endif