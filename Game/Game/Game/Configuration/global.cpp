#include "stdafx.h"
#include "global.h"

void _WriteMemory( int Address, int Value, int NumberOfBytes )
{
	DWORD VP = 0;
	VirtualProtect( ( void* )( Address ), 4, PAGE_EXECUTE_READWRITE, &VP );
	switch( NumberOfBytes )
	{
		case 1:
			*( char* )( Address ) = ( char )( Value );
			break;
		case 2:
			*( short* )( Address ) = ( short )( Value );
			break;
		case 4:
			*( int* )( Address ) = ( int )( Value );
			break;
	}
	VirtualProtect( ( void* )( Address ), 4, VP, &VP );
};

const char* _Format( const char* String, ... )
{
	static char Aux[ 256 ] = { 0 };
	va_list Args = { 0 };
	va_start( Args, String );
	StringCbVPrintfA( Aux, 256, String, Args );
	return Aux;
};

void _Clear( char* String, size_t Size )
{
	for( int i = 0; i < ( int )Size; i++ )
	{
		String[ i ] = 0;
	};
};