
template< typename T >
static T& configs::impl::get( std::uint32_t hash )
{
	const auto value = variable_map.find( hash );

	if ( !value._Ptr )
		return *( T* )nullptr;

	switch ( value._Ptr->_Myval.second.variable_type ) {
	case variable_type_t::TYPE_BOOL:
		return *( T* )&value._Ptr->_Myval.second.bvalue;
	case variable_type_t::TYPE_INT:
		return *( T* )&value._Ptr->_Myval.second.ivalue;
	case variable_type_t::TYPE_FLOAT:
		return *( T* )&value._Ptr->_Myval.second.fvalue;
	case variable_type_t::TYPE_COLOR:
		return *( T* )&value._Ptr->_Myval.second.cvalue;
	case variable_type_t::TYPE_MAX:
		return *( T* )nullptr;
	}

	console::print< console::log_level::FATAL >( "Config '{}' failed - [ hash {} ]", __func__, hash );

	return nullptr;
}