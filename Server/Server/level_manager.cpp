#include "stdafx.h"
#include "level_manager.h"

std::vector<INT64> LevelManager::Level( 0 );
void* LevelManager::LevelData = nullptr;

void LevelManager::Fill( )
{
	INT64 Aux = 0;
	Level.clear( );
	Level.resize( LEVEL_CAP + 2 );
	Level[ 0 ] = 0;
	Level[ 1 ] = LEVEL_EXP_BASE;
	for( int i = 2; i < LEVEL_CAP + 2; i++ )
	{
		Aux = ( INT64 )( Level[ i - 1 ] * LEVEL_MULTIPLIER );
		Level[ i ] = Aux + LEVEL_EXP_BASE;
	};
};

void LevelManager::AllocMemory( )
{
	LevelData = VirtualAlloc( nullptr, ( LEVEL_CAP + 3 ) * sizeof( INT64 ), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
};

void LevelManager::WriteTable( )
{
	*( INT64* )( LevelData ) = 0x0A00090009;

	memcpy_s( ( void* )( ( int )LevelData + 8 ), Level.size( ) * sizeof( INT64 ),
			  &Level[ 0 ], Level.size( ) * sizeof( INT64 ) );

	WriteMemory( 0x00443A02 + 3, ( int )LevelData + 0 );
	WriteMemory( 0x00443B05 + 3, ( int )LevelData + 0 );
	WriteMemory( 0x0044A26C + 3, ( int )LevelData + 0 );
	WriteMemory( 0x0044A3A6 + 3, ( int )LevelData + 0 );
	WriteMemory( 0x0047DD57 + 3, ( int )LevelData + 0 );
	WriteMemory( 0x0047DD92 + 3, ( int )LevelData + 0 );
	WriteMemory( 0x0047DDB3 + 3, ( int )LevelData + 0 );
	WriteMemory( 0x0047DDFC + 3, ( int )LevelData + 0 );
	WriteMemory( 0x0048052C + 3, ( int )LevelData + 0 );
	WriteMemory( 0x004439F3 + 3, ( int )LevelData + 4 );
	WriteMemory( 0x00443B0D + 3, ( int )LevelData + 4 );
	WriteMemory( 0x0044A274 + 3, ( int )LevelData + 4 );
	WriteMemory( 0x0044A3AF + 3, ( int )LevelData + 4 );
	WriteMemory( 0x0047DD42 + 3, ( int )LevelData + 4 );
	WriteMemory( 0x0047DD9E + 3, ( int )LevelData + 4 );
	WriteMemory( 0x0047DE08 + 3, ( int )LevelData + 4 );
	WriteMemory( 0x00480525 + 3, ( int )LevelData + 4 );
	






















































	/*
	WriteMemory( 0x00443B05 + 3, ( int )LevelData );
	WriteMemory( 0x0044A26C + 3, ( int )LevelData );
	WriteMemory( 0x0044A3A6 + 3, ( int )LevelData );
	WriteMemory( 0x0047DD57 + 3, ( int )LevelData );
	WriteMemory( 0x0047DD92 + 3, ( int )LevelData );
	WriteMemory( 0x0047DDB3 + 3, ( int )LevelData );
	WriteMemory( 0x0047DDFC + 3, ( int )LevelData );
	WriteMemory( 0x0048052C + 3, ( int )LevelData );
	WriteMemory( 0x00443B0D + 3, ( int )LevelData + 4 );
	WriteMemory( 0x0044A274 + 3, ( int )LevelData + 4 );
	WriteMemory( 0x0044A3AF + 3, ( int )LevelData + 4 );
	WriteMemory( 0x0047DD42 + 3, ( int )LevelData + 4 );
	WriteMemory( 0x0047DD9E + 3, ( int )LevelData + 4 );
	WriteMemory( 0x0047DE08 + 3, ( int )LevelData + 4 );
	WriteMemory( 0x00480525 + 3, ( int )LevelData + 4 );
	WriteMemory( 0x00443B2F + 3, ( int )LevelData + 8 );
	WriteMemory( 0x00443B94 + 3, ( int )LevelData + 8 );
	WriteMemory( 0x0044A185 + 3, ( int )LevelData + 8 );
	WriteMemory( 0x0044A27D + 3, ( int )LevelData + 8 );
	WriteMemory( 0x0044A397 + 3, ( int )LevelData + 8 );
	WriteMemory( 0x0047DD5E + 3, ( int )LevelData + 8 );
	WriteMemory( 0x0047DDBA + 3, ( int )LevelData + 8 );
	WriteMemory( 0x004431CC + 1, ( int )LevelData + 10 );
	WriteMemory( 0x00443B38 + 3, ( int )LevelData + 12 );
	WriteMemory( 0x00443B9B + 3, ( int )LevelData + 12 );
	WriteMemory( 0x0044A17C + 3, ( int )LevelData + 12 );
	WriteMemory( 0x0044A284 + 3, ( int )LevelData + 12 );
	WriteMemory( 0x0044A39E + 3, ( int )LevelData + 12 );
	WriteMemory( 0x0047DD67 + 3, ( int )LevelData + 12 );
	WriteMemory( 0x0047DDC3 + 3, ( int )LevelData + 12 );
	WriteMemory( 0x0044A1D7 + 3, ( int )LevelData + 16 );
	*/

	WriteMemory( 0x08B72010 + 6, LEVEL_CAP );
	WriteMemory( 0x004439E8 + 1, LEVEL_CAP );
};