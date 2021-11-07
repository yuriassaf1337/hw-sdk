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
