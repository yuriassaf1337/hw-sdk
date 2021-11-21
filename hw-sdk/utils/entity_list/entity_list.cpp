#include "entity_list.h"

void entity_list::update( ) 
{
	for (int i = 0; i < g_interfaces.entity_list->get_highest_entity_index(); i++)
		entities.push_back(g_interfaces.entity_list->get_client_entity(i));
}
