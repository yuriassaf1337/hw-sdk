#include <string.h>

#include "interfaces.h"

void interfaces::init( ) 
{
	device = **reinterpret_cast<IDirect3DDevice9***>(utils::find_signature(_("shaderapidx9.dll"), _("A1 ? ? ? ? 50 8B 08 FF 51 0C")) + 0x1);
}

void interfaces::unload( ) { }
