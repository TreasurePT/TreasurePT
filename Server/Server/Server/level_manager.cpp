#include "stdafx.h"
#include "level_manager.h"
#include "packets.h"

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
	m_Aux = 0;
	m_Level.clear( );
	m_Level.resize( LEVEL_CAP + 2 );
	m_Level[ 0 ] = 0;
	m_Level[ 1 ] = LEVEL_BASE_EXP;
	for( int i = 2; i <= LEVEL_CAP; i++ )
	{
		m_Aux = ( int64 )( m_Level[ i - 1 ] * LEVEL_MULTIPLIER );
		m_Level[ i ] = m_Aux + LEVEL_BASE_EXP;
	};
	m_Level[ LEVEL_CAP + 1 ] = -1;
};

void CLevelManager::WriteLevels( )
{
	LPVOID LevelData = VirtualAlloc( nullptr, m_Level.size( ) * sizeof( int64 ) + 8,
									 MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
	*( int64* )( 0x0A00090009 );
	memcpy_s( ( LPVOID )( ( int )LevelData + 8 ), m_Level.size( ) * sizeof( int64 ),
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

void CLevelManager::GetSoloExp( int MonsterInfo, int CharInfo )
{
	std::shared_ptr<CPackets> lpPacket = std::make_shared<CPackets>( );
	struct s_AddExp
	{
		int size;
		int opCode;
		int64 exp;
		int members;
		int checksum;
		int player;
	} AddExp;
	AddExp.size = sizeof( s_AddExp );
	AddExp.opCode = 0x48470031;
	AddExp.exp = GetTotalExp( *( int* )( MonsterInfo + 0x3ABC ),
							  *( int* )( MonsterInfo + 0x3944 ) - *( int* )( CharInfo + 0x15C ) );
	AddExp.members = 0;
	AddExp.player = *( int* )( MonsterInfo + 0x10 );
	AddExp.checksum = AddExp.player - ( int )( AddExp.exp & 0xFFFFFFFF );
	*( int* )( CharInfo + 0xAF14 ) += ( int )( AddExp.exp & 0xFFFFFFFF );
	lpPacket->SendPacket( ( char* )( &AddExp ), CharInfo, true );
};

void __cdecl _GetSoloExp( int MonsterInfo, int CharInfo )
{
	std::shared_ptr<CLevelManager> lpLevel = std::make_shared<CLevelManager>( );
	lpLevel->GetSoloExp( MonsterInfo, CharInfo );
};

int CLevelManager::GetTotalExp( int Exp, int Level )
{
	if( Level < 0 )
		Level *= -1;

	if( Level >= 50 )
	{
		return 0;
	}
	else if( Level >= 40 )
	{
		return ( int )( Exp * 0.25 );
	}
	else if( Level >= 30 )
	{
		return ( int )( Exp * 0.50 );
	}
	else if( Level >= 20 )
	{
		return ( int )( Exp * 0.75 );
	}
	else if( Level < 20 )
	{
		return ( int )( Exp );
	};
	return 0;
};

int __cdecl _GetTotalExp( int Exp, int Level )
{
	std::shared_ptr<CLevelManager> lpLevel = std::make_shared<CLevelManager>( );
	return lpLevel->GetTotalExp( Exp, Level );
};