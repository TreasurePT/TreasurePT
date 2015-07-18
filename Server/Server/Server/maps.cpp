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
	if( lpSql->Select( Maps, "SELECT * FROM ServerDB.dbo.Maps" ) )
	{ 
		INT TotalMaps = Maps.size( );
		for( int i = 0; i < TotalMaps + 1; i++ )
		{
			*( UINT* )( MapAddress + i * 0xEA8 ) = i;
		};

		int c = 0;

		for( int i = 0; i < TotalMaps; i++ )
		{
			lstrcpyA( ( char* )( MapAddress + 4 ), Maps[ i ][ 2 ].c_str( ) );
			*( UINT* )( MapAddress + 0xC4 ) = FieldType( Maps[ i ][ 3 ].c_str( ) );
			*( UINT* )( MapAddress + 0xCB4 ) = atoi( Maps[ i ][ 4 ].c_str( ) );

			MapAddress += 0xEA8;
			c++;
		};

		if( c > 0 )
		{
			UINT LoopField = 0x0075B340;
			while( c > 0 )
			{
				if( *( UINT* )( LoopField ) == 3 )
					*( UINT* )( LoopField ) = 2;
				LoopField += 938;
				c--;
			};
		};

	};
};

void __cdecl _Field( )
{
	std::shared_ptr<CMaps> lpMap = std::make_shared<CMaps>( );
	lpMap->CreateMaps( );
};