#pragma once
#include "../../game/sdk/classes/i_cvar.h"
#include "../../globals/intefaces/interfaces.h"

namespace convars
{
	struct convar_t {
		// convar's hash id
		std::uint32_t hash{ };
		// convar's pointer
		sdk::con_var* cvar{ };
		// convar name
		const char* cvar_name{ };

		explicit convar_t( std::uint32_t cvar_hash, const char* name )
		{
			// set our convar hash
			hash = cvar_hash;
			// get convar pointer off of its name
			cvar = g_interfaces.convar->find_var( name );
			// set name
			cvar_name = name;
		}
	};

	struct impl {
	public:
		std::unordered_map< std::uint32_t, convars::convar_t > convar_map;

		void init( );

		sdk::con_var* get_pointer( std::uint32_t hash );
		template< class T = const char* >
		T get_name( std::uint32_t hash );
		// ex of usage(atleast i think its possible to do it)
		// returns convar pointer:
		//	g_convars[_("sv_autobunnyhopping")]
		// will set value of cvar:
		//  g_convars[_("sv_autobunnyhopping")]->set_bool(true);

		sdk::con_var* operator[]( std::uint32_t convar_hash )
		{
			return get_pointer( convar_hash );
		}
	};
} // namespace convars

inline convars::impl g_convars;

#include "convars.inl"
