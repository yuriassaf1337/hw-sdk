#include "groupbox.h"
#include "../includes/includes.h"
#include "../utils/ui_utils.h"

void gui::groupbox::impl::invoke_groupbox( const std::string& name, const math::vec2< int >& pos, const math::vec2< int > size )
{
	// get groupbox id
	const auto my_id = gui::helpers::hash( name );
	m_id             = my_id;
}
