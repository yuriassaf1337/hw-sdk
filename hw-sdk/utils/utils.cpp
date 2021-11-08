#include "utils.h"

void utils::sleep( std::uint32_t time )
{
	::std::this_thread::sleep_for( ::chr::milliseconds( time ) );
}

BOOL utils::cheat_create_thread( DWORD WINAPI function( void* ), void* param )
{
	HANDLE handle = LI_FN( CreateThread )( nullptr, 0, function, param, 0, nullptr );
	if ( !handle )
		return FALSE;

	LI_FN( CloseHandle )( handle );

	return TRUE;
}

DWORD utils::find_signature( const char* module_name, const char* signature )
{
	auto FindPattern = [](const DWORD& dwAddress, const DWORD& dwLength, const char* signature) -> DWORD
	{
		auto szPat = signature;
		DWORD dwFirstMatch = 0x0;

		for (auto pCur = dwAddress; pCur < dwLength; pCur++)
		{
			if (!*szPat)
				return dwFirstMatch;

			const auto pCurByte = *(BYTE*)pCur;
			const auto pBytePatt = *(BYTE*)szPat;

			if (pBytePatt == '\?' || pCurByte == GetBytes(szPat))
			{
				if (!dwFirstMatch)
					dwFirstMatch = pCur;

				if (!szPat[2])
					return dwFirstMatch;

				szPat += (pBytePatt == '\?\?' || pBytePatt != '\?') ? 3 : 2;
			}

			else
			{
				szPat = signature;
				dwFirstMatch = 0x0;
			}
		}

		return 0x0;
	};
	auto GetModuleHandleSafe = [](const char* module_name) -> HMODULE
	{
		HMODULE hModule = nullptr;

		while (!hModule)
		{
			hModule = GetModuleHandleA(module_name);
			Sleep(1);
		}

		return hModule;
	};

	if (const auto hMod = reinterpret_cast<DWORD>(GetModuleHandleSafe(module_name)))
	{
		if (const auto pNT = reinterpret_cast<PIMAGE_NT_HEADERS>(hMod + reinterpret_cast<PIMAGE_DOS_HEADER>(hMod)->e_lfanew))
		{
			DWORD Pattern = FindPattern(hMod + pNT->OptionalHeader.BaseOfCode, hMod + pNT->OptionalHeader.SizeOfCode, signature);

			if (Pattern)
			{
				const auto message = fmt::format( _("found signature %x [%s -> %s]"), reinterpret_cast<void*>(Pattern), signature, module_name );
				console::print< console::log_level::NORMAL >(message);

				return Pattern;
			}
		}
	}

	return 0x0;
}
