#include "csgo.h"
#include "../dependencies/mocking_bird/mocking_bird.h"
#include "../utils/console/console.h"

bool csgo::init( )
{
	MOCKING_TRY;

	MOCK console::init( );

	console::print< console::log_level::SUCCESS >( _( "Console initialized" ) );

	MOCKING_CATCH( return false );

	return true;
}
