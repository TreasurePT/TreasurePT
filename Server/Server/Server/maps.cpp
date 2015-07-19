#include "stdafx.h"
#include "maps.h"
#include "sql_api.h"

int CMaps::FieldType( const char* Type )
{
	if( lstrcmpA( Type, "City" ) == 0 )
		return 0x100;
	else if( lstrcmpA( Type, "Forest" ) == 0 )
		return 0x200;
	else if( lstrcmpA( Type, "Desert" ) == 0 )
		return 0x300;
	else if( lstrcmpA( Type, "Ruins" ) == 0 )
		return 0x400;
	else if( lstrcmpA( Type, "Dungeon" ) == 0 )
		return 0x500;
	else if( lstrcmpA( Type, "Iron" ) == 0 )
		return 0x600;
	else if( lstrcmpA( Type, "Unused" ) == 0 )
		return 0x700;
	else if( lstrcmpA( Type, "Office" ) == 0 )
		return 0x800;
	else if( lstrcmpA( Type, "Ice" ) == 0 )
		return 0x900;
	else if( lstrcmpA( Type, "Castle" ) == 0 )
		return 0xA00;
	else if( lstrcmpA( Type, "Mini-Game" ) == 0 )
		return 0xB00;
	else return 0;
};

void CMaps::CreateMaps( )
{
	std::shared_ptr<CSQLApi> lpSql = std::make_shared<CSQLApi>( );
	SQLPTR Maps;
	INT MapAddress = 0x0075B038;

	Clear( ( char* )( 0x0075B038 ), 0x3AA00 );
	
	for( int i = 0; i < 256; i++ )
	{
		*( int* )( 0x0075BE94 + i * 3752 ) = i;
	};

	if( lpSql->Select( Maps, "SELECT * FROM ServerDB.dbo.Maps" ) )
	{ 
		INT TotalMaps = Maps.size( );

		int c = 0;

		for( int i = 0; i < TotalMaps; i++ )
		{
			lstrcpyA( ( char* )( MapAddress + 4 ), Maps[ i ][ 2 ].c_str( ) );
			*( UINT* )( MapAddress + 196 ) = FieldType( Maps[ i ][ 3 ].c_str( ) );
			*( UINT* )( MapAddress + 3256 ) = atoi( Maps[ i ][ 4 ].c_str( ) );

			MapAddress += 3752;
			c++;
		};
	};

};

void __cdecl _Field( )
{
	std::shared_ptr<CMaps> lpMap = std::make_shared<CMaps>( );
	lpMap->CreateMaps( );
};