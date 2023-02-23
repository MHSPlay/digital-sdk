#pragma once

#ifndef VALVE_ENGINE_VGUI
#define VALVE_ENGINE_VGUI

#include "../../utils/memory/memory.hh"

class c_engine_vgui {
public:
    VFUNC( void( __thiscall* )( void*, int ), paint( int mode ), 14, mode );
private:
    char gap0[ 36 ]{ };
public:
    void* m_static_panel{ };
private:
    void* pppfunc28{ };
    void* pppfunc2C{ };
    char gap44[ 4 ]{ };
public:
    void* m_static_trans_panel{ };
private:
    char gap4C[ 56 ]{ };
public:
    int m_unk_mode{ };
};

#endif