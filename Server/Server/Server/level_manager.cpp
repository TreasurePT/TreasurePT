#include "stdafx.h"
#include "level_manager.h"
#include "file_manager.h"

std::vector<__int64> CLevelManager::m_Level( 0 );

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
	std::shared_ptr<CFileManager> lpFile = std::make_shared<CFileManager>( "Level.ini" );
	lpFile->GetInt( "Level", "Capacidade", m_Level_Size );
	m_Level.clear( );
	m_Level.resize( m_Level_Size + 2 );
	m_Level[ 0 ] = 0;
	SecureZeroMemory( m_Level_Buffer, 256 );
	char* EndPtr = nullptr;
	for( int i = 1; i < m_Level_Size + 1; i++ )
	{
		lpFile->GetString( "Level",
						   lpFile->Format( "Level[ %d ]", i ),
						   m_Level_Buffer );
		m_Level[ i ] = strtoll( m_Level_Buffer, &EndPtr, 10 );
	};
	m_Level[ m_Level_Size + 2 ] = -1;
};

void CLevelManager::WriteLevels( )
{
	LPVOID LevelData = VirtualAlloc( nullptr, m_Level.size( ) * sizeof( __int64 ),
									 MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
	memcpy_s( LevelData, m_Level.size( ) * sizeof( __int64 ),
			  &m_Level, m_Level.size( ) * sizeof( __int64 ) );
};

void __cdecl _SetLevels( )
{
	std::shared_ptr<CLevelManager> lpLevel = std::make_shared<CLevelManager>( );
	lpLevel->ReadLevels( );
	lpLevel->WriteLevels( );
};