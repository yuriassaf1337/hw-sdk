#pragma once
#include "../structs/color.h"
#include "i_app_system.h"

struct c_var_dll_identifier;
struct con_command_base;
struct con_var;
struct con_command;
struct i_con_var;
struct i_console_display_func;
struct i_cvar_query;

using fn_change_callback = void ( * )( i_con_var* var, const char* pOldValue, float flOldValue );

namespace sdk
{
	struct i_cvar : public i_app_system {
	public:
		virtual c_var_dll_identifier allocate_dll_indentifier( )                                      = 0;
		virtual void register_con_command( con_command_base* base )                                   = 0;
		virtual void unregister_con_command( con_command_base* base )                                 = 0;
		virtual void unregister_con_commands( c_var_dll_identifier id )                               = 0;
		virtual const char* get_command_line_value( const char* name )                                = 0;
		virtual con_command_base* find_command_base( const char* name )                               = 0;
		virtual const con_command_base* find_command_base( const char* name ) const                   = 0;
		virtual con_var* FindVar( const char* var_name )                                              = 0;
		virtual const con_var* FindVar( const char* var_name ) const                                  = 0;
		virtual con_command* find_command( const char* name )                                         = 0;
		virtual const con_command* find_command( const char* name ) const                             = 0;
		virtual void install_global_change_callback( fn_change_callback callback )                    = 0;
		virtual void remove_global_change_callback( fn_change_callback callback )                     = 0;
		virtual void call_global_change_callbacks( con_var* var, const char* old_str, float old_val ) = 0;
		virtual void install_console_display_func( i_console_display_func* func )                     = 0;
		virtual void remove_console_display_func( i_console_display_func* func )                      = 0;
		virtual void console_color_printf( const color& clr, const char* format, ... ) const          = 0;
		virtual void console_printf( const char* format, ... ) const                                  = 0;
		virtual void dconsole_dprintf( const char* format, ... ) const                                = 0;
		virtual void rever_flagged_convars( int flag )                                                = 0;
	};
} // namespace sdk
