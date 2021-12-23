#pragma once

#include "../../dependencies/hash/hash.h"
#include "../../dependencies/xor/xor.h"

#define HASH( s ) fnv::hash( s )

#ifdef _DEBUG
#	define _( s ) ( s )
#else
#	define _( s ) ( __xor_string( s ) )
#endif

#define xf( n ) ::__xor::xor_float::convert( n )

// [#] game-dlls

#define CLIENT_DLL              _( "client.dll" )
#define ENGINE_DLL              _( "engine.dll" )
#define LOCALIZE_DLL            _( "localize.dll" )
#define MATERIALSYSTEM_DLL      _( "materialsystem.dll" )
#define VGUI_DLL                _( "vguimatsurface.dll" )
#define VGUI2_DLL               _( "vgui2.dll" )
#define SHADERAPIDX9_DLL        _( "shaderapidx9.dll" )
#define GAMEOVERLAYRENDERER_DLL _( "gameoverlayrenderer.dll" )
#define PHYSICS_DLL             _( "vphysics.dll" )
#define VSTDLIB_DLL             _( "vstdlib.dll" )
#define TIER0_DLL               _( "tier0.dll" )
#define INPUTSYSTEM_DLL         _( "inputsystem.dll" )
#define STUDIORENDER_DLL        _( "studiorender.dll" )
#define DATACACHE_DLL           _( "datacache.dll" )
#define STEAM_API_DLL           _( "steam_api.dll" )
#define MATCHMAKING_DLL         _( "matchmaking.dll" )
#define SERVER_DLL              _( "server.dll" )
#define SERVERBROWSER_DLL       _( "serverbrowser.dll" )

// [#] interface-versions

#define VENGINE_CLIENT_INTERFACE_VERSION      _( "VEngineClient014" )
#define VCLIENT_INTERFACE_VERSION             _( "VClient018" )
#define VCLIENTENTITYLIST_INTERFACE_VERSION   _( "VClientEntityList003" )
#define VCLIENTPREDICTION_INTERFACE_VERSION   _( "VClientPrediction001" )
#define VCLIENTGAMEMOVEMENT_INTERFACE_VERSION _( "GameMovement001" )
#define VENGINE_CLIENT_TRACE_VERSION          _( "EngineTraceClient004" )
#define VENGINE_SOUND_CLIENT_VERSION          _( "IEngineSoundClient003" )
#define VSTUDIO_RENDER_VERSION                _( "VStudioRender026" )
#define VENGINE_DEBUG_OVERLAY_VERSION         _( "VDebugOverlay004" )
#define VMATERIAL_SYSTEM_CLIENT_VERSION       _( "VMaterialSystem080" )
#define VGUI_PANEL_CLIENT_VERSION             _( "VGUI_Panel009" )
#define LOCALIZE_LOCALIZE_VERSION             _( "Localize_001" )
#define VENGINE_MODEL_VERSION                 _( "VEngineModel016" )

// [#] utils

#define COMBINE( lhs, rhs ) lhs##rhs
#define CONCAT( lhs, rhs )  COMBINE( lhs, rhs )
#define PAD( size )                                                                                                                                  \
private:                                                                                                                                             \
	std::uint8_t CONCAT( pad, __COUNTER__ )[ size ];                                                                                                 \
                                                                                                                                                     \
public:

#define INRANGE( x, a, b ) ( x >= a && x <= b )
#define GETBITS( x )       ( INRANGE( ( x & ( ~0x20 ) ), 'A', 'F' ) ? ( ( x & ( ~0x20 ) ) - 'A' + 0xA ) : ( INRANGE( x, '0', '9' ) ? x - '0' : 0 ) )
#define GETBYTES( x )      ( GETBITS( x[ 0 ] ) << 4 | GETBITS( x[ 1 ] ) )

// [#] hooking utils

#define CREATE_HOOK_HELPER( name, args ) inline hook_helper< args > name;

// [#] netvar helper

#define NETVAR( name, type, table, var )                                                                                                             \
	[[nodiscard]] type& name( )                                                                                                                      \
	{                                                                                                                                                \
		static std::uintptr_t offset = netvar::get_table( _( table ), _( var ) );                                                                    \
		return *reinterpret_cast< type* >( reinterpret_cast< std::uintptr_t >( this ) + offset );                                                    \
	}

// [#] offsets

// grab variable value
#define OFFSET( type, name, value )                                                                                                                  \
	[[nodiscard]] std::add_lvalue_reference_t< type > name( )                                                                                        \
	{                                                                                                                                                \
		return *( std::add_pointer_t< type > )( reinterpret_cast< std::uintptr_t >( this ) + value );                                                \
	}

// grab variable pointer
#define PTR_OFFSET( type, name, value )                                                                                                              \
	[[nodiscard]] std::add_pointer_t< type > name( )                                                                                                 \
	{                                                                                                                                                \
		return ( std::add_pointer_t< type > )( reinterpret_cast< std::uintptr_t >( this ) + value );                                                 \
	}

#define ROUND_UP( value ) static_cast< int >( static_cast< float >( value ) + 0.5f )
