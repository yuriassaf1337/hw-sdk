#pragma once

#include <iostream>

#include "../console/console.h"
#include "../../globals/macros/macros.h"
#include "../../dependencies/minhook/include/MinHook.h"

template <class T>
class hook_helper
{
private:
	std::uintptr_t source = nullptr;
	std::uintptr_t original = nullptr;

public:
	template <typename S, typename D>
	void create(S source, D destination, const char* name = _("undefined"))
	{
		MH_CreateHook(reinterpret_cast<void*>(source), reinterpret_cast<void*>(destination), &original);

		MH_EnableHook(reinterpret_cast<void*>(source));

		auto message = tfm::format( _( "hooked %s [%x => %x]" ), name, source, destination );
		console::print< console::log_level::NORMAL >( message );
	}

	void disable() 
	{
		MH_DisableHook(source);
	}

	T* get_original() 
	{ 
		return reinterpret_cast<T*>(original);
	}

	template <typename R, typename... A>
	R call_original(A... arguments)
	{
		return reinterpret_cast<T*>(original)(arguments...);
	}
};