#include "render.hh"

void c_render::init( IDirect3DDevice9* const device ) {
    ImGui::CreateContext( );

    if ( !ImGui_ImplDX9_Init( device ) || !ImGui_ImplWin32_Init( g_ctx->m_hwnd ) )
        return;

    auto& io = ImGui::GetIO( );
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    ImGui::StyleColorsDark( );

    auto& style = ImGui::GetStyle( );
    style.ScrollbarSize = 13.0f;
    style.WindowTitleAlign = ImVec2{ 0.5f, 0.5f };
    style.WindowRounding = 6.f;

    ImFontConfig cfg;
    cfg.PixelSnapH = false;
    cfg.OversampleH = 5;
    cfg.OversampleV = 5;
    cfg.RasterizerMultiply = 1.2f;

    m_fonts.m_esp = io.Fonts->AddFontFromFileTTF( _( "C:/windows/fonts/verdana.ttf" ), 13, &cfg,
                                                  io.Fonts->GetGlyphRangesCyrillic( ) );

    ImGui::GetIO( ).Fonts->AddFontDefault( );
}

void c_render::line( const float x1, const float y1, const float x2, const float y2, c_color clr,
                     const float thickness ) const {
    m_draw_list->AddLine( ImVec2( x1, y1 ), ImVec2( x2, y2 ), clr.u32( ), thickness );
}

void c_render::rect( const float x, const float y, const float w, const float h, c_color clr,
                     const float rounding ) const {
    m_draw_list->AddRect( ImVec2( x, y ), ImVec2( x + w, y + h ), clr.u32( ), rounding );
}

void c_render::filled_rect( const float x, const float y, const float w, const float h, c_color color,
                            const float rounding, const int flags ) const {
    m_draw_list->AddRectFilled( ImVec2( x, y ), ImVec2( x + w, y + h ), color.u32( ), rounding, flags );
}

void c_render::filled_rect_gradient( const float x, const float y, const float w, const float h, c_color col_upr_left,
                                     c_color col_upr_right, c_color col_bot_right, c_color col_bot_left ) const {
    m_draw_list->AddRectFilledMultiColor( ImVec2( x, y ), ImVec2( x + w, y + h ), col_upr_left.u32( ),
                                          col_upr_right.u32( ), col_bot_right.u32( ), col_bot_left.u32( ) );
}

void c_render::triangle( const float x1, const float y1, const float x2, const float y2, const float x3, const float y3,
                         c_color clr, const float thickness ) const {
    m_draw_list->AddTriangle( ImVec2( x1, y1 ), ImVec2( x2, y2 ), ImVec2( x3, y3 ), clr.u32( ), thickness );
}

void c_render::triangle_filled( const float x1, const float y1, const float x2, const float y2, const float x3,
                                const float y3, c_color clr ) const {
    m_draw_list->AddTriangleFilled( ImVec2( x1, y1 ), ImVec2( x2, y2 ), ImVec2( x3, y3 ), clr.u32( ) );
}

void c_render::circle( const float x1, const float y1, const float radius, c_color col, const int segments ) const {
    m_draw_list->AddCircle( ImVec2( x1, y1 ), radius, col.u32( ), segments );
}

void c_render::circle_filled( const float x1, const float y1, const float radius, c_color col,
                              const int segments ) const {
    m_draw_list->AddCircleFilled( ImVec2( x1, y1 ), radius, col.u32( ), segments );
}

void c_render::text( const float x, const float y, c_color color, const int flags, ImFont* font, const char* message,
                     ... ) const {
    char output[ 4096 ]{ };
    va_list args;
    va_start( args, message );
    vsnprintf_s( output, sizeof( output ), _TRUNCATE, message, args );
    va_end( args );

    m_draw_list->PushTextureID( font->ContainerAtlas->TexID );

    const auto size = font->CalcTextSizeA( font->FontSize, FLT_MAX, 0.0f, output );
    const auto pos = ImVec2( x - size.x / 2.0f, y );
    auto outline_clr = c_color( 0, 0, 0, static_cast< int >( color.a( ) * 0.3f ) );

    if ( flags & drop_shadow )
        m_draw_list->AddText( ImVec2( pos.x + 1, pos.y + 1 ), outline_clr.u32( ), output );

    if ( flags & outline ) {
        constexpr std::array< ImVec2, 8 > offsets = {
            { { 1, -1 }, { -1, 1 }, { -1, -1 }, { 1, 1 }, { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }
        };

        for ( const auto& offset : offsets )
            m_draw_list->AddText( font, font->FontSize, pos + offset, outline_clr.u32( ), output );
    }

    m_draw_list->AddText( font, font->FontSize, pos, color.u32( ), output );
}

bool c_render::world_to_screen( const c_vec3& in, c_vec2& out ) {
    const auto& matrix = g_interfaces->m_engine->get_view_matrix( );
    out.x = matrix[ 0 ][ 0 ] * in.x + matrix[ 0 ][ 1 ] * in.y + matrix[ 0 ][ 2 ] * in.z + matrix[ 0 ][ 3 ];
    out.y = matrix[ 1 ][ 0 ] * in.x + matrix[ 1 ][ 1 ] * in.y + matrix[ 1 ][ 2 ] * in.z + matrix[ 1 ][ 3 ];

    const auto w = matrix[ 3 ][ 0 ] * in.x + matrix[ 3 ][ 1 ] * in.y + matrix[ 3 ][ 2 ] * in.z + matrix[ 3 ][ 3 ];
    if ( w < 0.001f ) {
        out *= 100000.f;
        return false;
    }

    out /= w;

    auto& io = ImGui::GetIO( );
    const auto screen_width = io.DisplaySize.x, screen_height = io.DisplaySize.y;

    out.x = screen_width / 2.f + out.x * screen_width / 2.f;
    out.y = screen_height / 2.f - out.y * screen_height / 2.f;

    return true;
}