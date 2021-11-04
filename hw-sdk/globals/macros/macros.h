#pragma once

#include "../../dependencies/hash/hash.h"
#include "../../dependencies/xor/xor.h"

#define HASH( s ) fnv::hash( s )

#ifdef _DEBUG
#	define x( s ) ( s )
#else
#	define x( s ) ( __xor_string( s ) )
#endif

#define xf( n ) ::__xor::xor_float::convert( n )

#define CLIENT_DLL              HASH( "client.dll" )
#define ENGINE_DLL              HASH( "engine.dll" )
#define LOCALIZE_DLL            HASH( "localize.dll" )
#define MATERIALSYSTEM_DLL      HASH( "materialsystem.dll" )
#define VGUI_DLL                HASH( "vguimatsurface.dll" )
#define VGUI2_DLL               HASH( "vgui2.dll" )
#define SHADERAPIDX9_DLL        HASH( "shaderapidx9.dll" )
#define GAMEOVERLAYRENDERER_DLL HASH( "gameoverlayrenderer.dll" )
#define PHYSICS_DLL             HASH( "vphysics.dll" )
#define VSTDLIB_DLL             HASH( "vstdlib.dll" )
#define TIER0_DLL               HASH( "tier0.dll" )
#define INPUTSYSTEM_DLL         HASH( "inputsystem.dll" )
#define STUDIORENDER_DLL        HASH( "studiorender.dll" )
#define DATACACHE_DLL           HASH( "datacache.dll" )
#define STEAM_API_DLL           HASH( "steam_api.dll" )
#define MATCHMAKING_DLL         HASH( "matchmaking.dll" )
#define SERVER_DLL              HASH( "server.dll" )
#define SERVERBROWSER_DLL       HASH( "serverbrowser.dll" )
