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
	struct model_t;
	struct i_client_entity;
	struct i_client_unknown;
	struct client_think_handle_pointer;

	typedef client_think_handle_pointer* client_think_handle;
	typedef std::uintptr_t client_shadow_handle;
	typedef std::uintptr_t client_render_handle;
	typedef std::uintptr_t model_instance_handle;

	struct i_client_renderable {
	public:
		virtual i_client_unknown* get_i_client_unkown( ) = 0;
		virtual math::vec3& get_render_origin( )         = 0;
		virtual math::vec3& get_render_angles( )         = 0;
		virtual bool should_draw( )                      = 0;
		virtual int get_render_flags( )                  = 0;

	private:
		virtual void padding( ) = 0;

	public:
		virtual client_shadow_handle get_shadow_handle( )                                                                                    = 0;
		virtual client_render_handle get_render_handle( )                                                                                    = 0;
		virtual model_t* get_model( )                                                                                                        = 0;
		virtual int draw_model( int flags, std::uintptr_t& instance )                                                                        = 0;
		virtual int get_body( )                                                                                                              = 0;
		virtual void get_color_modulation( float* color )                                                                                    = 0;
		virtual bool lod_test( )                                                                                                             = 0;
		virtual bool setup_bones( math::matrix_3x4* bone_to_world_out, int max_bones, int bone_mask, float current_time )                    = 0;
		virtual void setup_weights( math::matrix_3x4* bone_to_world, int flex_weight_count, float flex_weights, float flex_delayed_weights ) = 0;
		virtual void do_animation_event( )                                                                                                   = 0;
		virtual std::uintptr_t* get_pvs_norify_interface( )                                                                                  = 0;
		virtual void get_render_bounds( math::vec3& minimum, math::vec3& maximum )                                                           = 0;
		virtual void get_render_bounds_worldspace( math::vec3& mins, math::vec3& maxs )                                                      = 0;
		virtual void get_shadow_render_bounds( math::vec3& mins, math::vec3& maxs, int shadow_type )                                         = 0;
		virtual bool should_receive_projected_textures( int flags )                                                                          = 0;
		virtual bool get_shadow_cast_distance( float* p_dist, int shadow_type ) const                                                        = 0;
		virtual bool get_shadow_cast_direction( math::vec3* p_direction, int shadow_type ) const                                             = 0;
		virtual bool is_shadow_dirty( )                                                                                                      = 0;
		virtual void mark_shadow_dirty( bool b_dirty )                                                                                       = 0;
		virtual i_client_renderable* get_shadow_parent( )                                                                                    = 0;
		virtual i_client_renderable* first_shadow_child( )                                                                                   = 0;
		virtual i_client_renderable* next_shadow_peer( )                                                                                     = 0;
		virtual int shadow_cast_type( )                                                                                                      = 0;
		virtual void create_model_instance( )                                                                                                = 0;
		virtual model_instance_handle get_model_instance( )                                                                                  = 0;
		virtual const math::matrix_3x4& renderable_to_world_transform( )                                                                     = 0;
		virtual int lookup_attachment( const char* p_attachment_name )                                                                       = 0;
		virtual bool get_attachment( int number, math::vec3& origin, math::vec3& angles )                                                    = 0;
		virtual bool get_attachment( int number, math::matrix_3x4& matrix )                                                                  = 0;
		virtual float* get_render_clip_plane( void )                                                                                         = 0;
		virtual int get_skin( )                                                                                                              = 0;
		virtual void on_threaded_draw_setup( )                                                                                               = 0;
		virtual bool uses_flex_delayed_weights( )                                                                                            = 0;
		virtual void record_tool_message( )                                                                                                  = 0;
		virtual bool should_draw_for_split_screen_user( int n_slot )                                                                         = 0;
		virtual std::uint8_t override_alpha_modulation( std::uint8_t n_alpha )                                                               = 0;
		virtual std::uint8_t override_shadow_alpha_modulation( std::uint8_t n_alpha )                                                        = 0;
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

	private:
		virtual void padding( ) = 0;

	public:
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
		virtual void release( ) = 0;
	};
} // namespace sdk
