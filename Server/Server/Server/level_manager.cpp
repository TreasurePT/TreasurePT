#include "stdafx.h"
#include "level_manager.h"
#include "file_manager.h"

#define LEVEL_CAP ( int )( m_Level.size( ) - 2 )

std::vector<int64> CLevelManager::m_Level( 0 );

int CLevelManager::CheckExpGained( int Exp, int Player )
{
	//if( Player->GetPrivilege( ) == 4 )
	return true;

	//if( Player->GetLevel( ) <= 10 )
	{
		//TODO: Estabelecer comparação com a EXP.
		// return true = permitir exp, return false = negar exp ( banir );

	};

	return true;
};

int __cdecl _CheckExpGained( int Exp, int Player )
{
	std::shared_ptr<CLevelManager> lpLv = std::make_shared<CLevelManager>( );
	//Player->SetAddress( ( int )Player );
	return lpLv->CheckExpGained( Exp, Player );
};

void CLevelManager::ReadLevels( )
{
	std::shared_ptr<CFileManager> lpFile = std::make_shared<CFileManager>( "level.ini" );
	lpFile->GetInt( "Level", "Capacidade", m_Level_Size );
	m_Level.clear( );
	m_Level.resize( m_Level_Size + 2 );
	m_Level[ 0 ] = 0;
	SecureZeroMemory( m_Level_Buffer, 256 );
	char* EndPtr = nullptr;
	for( int i = 1; i <= m_Level_Size; i++ )
	{
		lpFile->GetString( "Level",
						   lpFile->Format( "Level[ %d ]", i ),
						   m_Level_Buffer );
		m_Level[ i ] = strtoll( m_Level_Buffer, &EndPtr, 10 );
	};
	m_Level[ m_Level_Size + 1 ] = -1;
};

void CLevelManager::WriteLevels( )
{
	LPVOID LevelData = VirtualAlloc( nullptr, m_Level.size( ) * sizeof( int64 ),
									 MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
	memcpy_s( LevelData, m_Level.size( ) * sizeof( int64 ),
			  &m_Level[ 0 ], m_Level.size( ) * sizeof( int64 ) );

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
};

void __cdecl _SetLevels( )
{
	std::shared_ptr<CLevelManager> lpLevel = std::make_shared<CLevelManager>( );
	lpLevel->ReadLevels( );
	lpLevel->WriteLevels( );
};

int CLevelManager::CheckLevelExp( int Level, int64 Exp )
{
	if( Level > 0 && Level <= LEVEL_CAP )
	{
		if( Exp >= m_Level[ Level - 1 ] && Exp <= m_Level[ Level ] )
			return TRUE;
	};
	return FALSE;
};

int __cdecl _CheckLevelExp( int Level, int64 Exp )
{
	std::shared_ptr<CLevelManager> lpLevel = std::make_shared<CLevelManager>( );
	return lpLevel->CheckLevelExp( Level, Exp );
};

int CLevelManager::GetLevelFromExp( int64 Exp )
{
	for( int i = 0; i < LEVEL_CAP; i++ )
	{
		if( Exp >= m_Level[ i ] && Exp < m_Level[ i + 1 ] )
		{
			return i + 1;
		};
	};
	return 0;
};

int __cdecl _GetLevelFromExp( int64 Exp )
{
	std::shared_ptr<CLevelManager> lpLevel = std::make_shared<CLevelManager>( );
	return lpLevel->GetLevelFromExp( Exp );
};

int CLevelManager::CheckPlayerLevel( int Player )
{
	if( *( int* )( Player + 0xC8 ) > LEVEL_CAP )
		return TRUE;
	return FALSE;
};

int __cdecl _CheckPlayerLevel( int Player )
{
	std::shared_ptr<CLevelManager> lpLevel = std::make_shared<CLevelManager>( );
	return lpLevel->CheckPlayerLevel( Player );
};