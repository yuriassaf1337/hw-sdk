#pragma once

#include <iostream>

#include "../../../dependencies/hash/hash.h"
#include "../../../dependencies/xor/xor.h"
#include "../../../globals/macros/macros.h"

#include "../structs/dt_recv.h"
#include "../structs/i_client_class.h"
#include "c_base_entity.h"
#include "i_handle_entity.h"

namespace sdk
{
	struct bf_read;
	struct i_client_entity;
	struct i_client_unknown;
	struct client_think_handle_pointer;
	typedef client_think_handle_pointer* client_think_handle;

	struct i_client_renderable {
	};

	struct i_client_networkable {
	public:
		virtual i_client_unknown* get_i_client_unknown( )   = 0;
		virtual void release( )                             = 0;
		virtual client_class* get_client_class( )           = 0;
		virtual void notify_should_transmit( int state )    = 0;
		virtual void on_pre_data_changed( int update_type ) = 0;
		virtual void on_data_changed( int update_type )     = 0;
		virtual void pre_data_update( int update_type )     = 0;
		virtual void post_data_update( int update_type )    = 0;

		PAD( 0x4 );

		virtual void is_dormant( )                                     = 0;
		virtual int entity_index( )                                    = 0;
		virtual void receive_message( int class_id, bf_read& message ) = 0;
		virtual void* get_data_table_base_pointer( )                   = 0;
		virtual void set_destroyed_on_recreate_entities( )             = 0;
	};

	struct i_client_thinkable {
	public:
		virtual i_client_unknown* get_i_client_unknown( )                 = 0;
		virtual void client_think( )                                      = 0;
		virtual client_think_handle get_think_handle( )                   = 0;
		virtual void set_think_handle( client_think_handle think_handle ) = 0;
		virtual void release( )                                           = 0;
	};

	struct i_client_unknown : public i_handle_entity {
	public:
		virtual std::uintptr_t* get_collideable( )              = 0;
		virtual i_client_networkable* get_client_networkable( ) = 0;
		virtual i_client_renderable* get_client_renderable( )   = 0;
		virtual i_client_entity* get_i_client_entity( )         = 0;
		virtual c_base_entity* get_base_entity( )               = 0;
		virtual i_client_thinkable* get_client_thinkable( )     = 0;
		virtual std::uintptr_t* get_client_alpha_property( )    = 0;
	};

	struct i_client_entity : public i_client_unknown, public i_client_renderable, public i_client_networkable, public i_client_thinkable {
	};
} // namespace sdk
