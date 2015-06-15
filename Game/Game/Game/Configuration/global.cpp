#include "stdafx.h"
#include "global.h"

void _WriteMemory( long Address, long Value, long NumberOfBytes )
{
	DWORD Old_Protect = 0, New_Protect = 0;
	VirtualProtect( ( void* )( Address ), 4, PAGE_EXECUTE_READWRITE, &Old_Protect );
	New_Protect = Old_Protect;
	switch( NumberOfBytes )
	{
		case 1:
			*( char* )( Address ) = ( char )( Value );
			break;
		case 2:
			*( short* )( Address ) = ( short )( Value );
			break;
		case 4:
			*( long* )( Address ) = ( long )( Value );
			break;
	}
	VirtualProtect( ( void* )( Address ), 4, New_Protect, &Old_Protect );
};