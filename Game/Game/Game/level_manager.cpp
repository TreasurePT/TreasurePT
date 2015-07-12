#include "stdafx.h"
#include "level_manager.h"
#include "quests.h"


std::vector<int64> CLevelManager::m_Level( 0 );

#define LEVEL_CAP ( int )( m_Level.size( ) - 2 )

int CLevelManager::AddExpSystem( int Packet )
{
	std::shared_ptr<CQuests> lpQuest = std::make_shared<CQuests>( );
	typedef DWORD( __cdecl* t_FindAutoPlayer ) ( DWORD );
	t_FindAutoPlayer FindAutoPlayer = ( t_FindAutoPlayer )0x0062D820;
	typedef void( __cdecl* t_AddChatMsg )( LPCSTR, INT );
	t_AddChatMsg AddChatMsg = ( t_AddChatMsg )0x0062DEB0;

	s_AddExp* AddExp = ( s_AddExp* )Packet;
	
	DWORD Char = FindAutoPlayer( AddExp->PlayerSerial );

	if( Char )
	{
		if( AddExp->PlayerSerial - ( AddExp->Experience & 0xFFFFFFFF ) != AddExp->CheckSum )
			return FALSE;

		//TODO: CheckServerExp

		INT64 GainedExp = AddExp->Experience;
		DWORD Monster_Code = *( DWORD* )( Char + 0x3A74 );

		if( *( int* )( Packet + 24 ) - ( int )( ( *( int64* )( Packet + 8 ) & 0xFFFFFFFF ) ) != *( int* )( Packet + 20 ) )
			return FALSE;

		DWORD LowBitExp = AddExperience( GainedExp );
		std::string strExp( Format( "%d", LowBitExp ) );

		for( int i = strExp.size( ) - 3; i > 0; i -= 3 )
		{
			strExp.insert( strExp.begin( ) + i, ',' );
		}

		if( AddExp->OpCode == 0x48470031 )
		{
			AddChatMsg( Format( "> Ganhou: %s de Experiência->", strExp.c_str( ) ), 9 );
			lpQuest->Teste( Monster_Code );
		}
		else
		{
			AddChatMsg( Format( "> Ganhou: %s de Experiência em Grupo[ %d% / %d ]->",
				strExp.c_str( ), ( AddExp->Members - 1 ) * 40 + 100,
				AddExp->Members ), 9 );
			//TODO: Quest Party.
		};

		*( DWORD* )( Char + 0x2B0 ) += LowBitExp;
	};

	return TRUE;
};



void CLevelManager::ReadLevels( int Cap, float Multiplier, int BaseExp )
{
	if( Cap <= 1 )
		return;
	if( BaseExp < 1 )
		return;
	if( Multiplier <= 1.0f )
		return;

	m_Aux = 0;
	m_Level.clear( );
	m_Level.resize( Cap + 2 );
	m_Level[ 0 ] = 0;
	m_Level[ 1 ] = BaseExp;
	for( int i = 2; i <= Cap; i++ )
	{
		m_Aux = ( int64 )( m_Level[ i - 1 ] * Multiplier );
		m_Level[ i ] = m_Aux + BaseExp;
	};
	m_Level[ Cap + 1 ] = -1;
};

void CLevelManager::WriteLevels( )
{
	LPVOID LevelData = VirtualAlloc( nullptr, m_Level.size( ) * sizeof( int64 ) + 8,
									 MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
	*( int64* )( 0x0A00090009 );
	memcpy_s( ( LPVOID )( ( int )LevelData + 8 ), m_Level.size( ) * sizeof( int64 ),
			  &m_Level[ 0 ], m_Level.size( ) * sizeof( int64 ) );

	WriteMemory( 0x0045B1C5 + 3, ( int )LevelData );
	WriteMemory( 0x00461FBC + 3, ( int )LevelData );
	WriteMemory( 0x004620D6 + 3, ( int )LevelData );
	WriteMemory( 0x004A9A57 + 3, ( int )LevelData );
	WriteMemory( 0x004A9A92 + 3, ( int )LevelData );
	WriteMemory( 0x004A9AB3 + 3, ( int )LevelData );
	WriteMemory( 0x004A9AFC + 3, ( int )LevelData );
	WriteMemory( 0x004ACF02 + 3, ( int )LevelData );

	WriteMemory( 0x0045B1CD + 3, ( int )LevelData + 4 );
	WriteMemory( 0x00461FC4 + 3, ( int )LevelData + 4 );
	WriteMemory( 0x004620DF + 3, ( int )LevelData + 4 );
	WriteMemory( 0x004A9A42 + 3, ( int )LevelData + 4 );
	WriteMemory( 0x004A9A9E + 3, ( int )LevelData + 4 );
	WriteMemory( 0x004A9B08 + 3, ( int )LevelData + 4 );
	WriteMemory( 0x004ACEFB + 3, ( int )LevelData + 4 );

	WriteMemory( 0x0045B1EF + 3, ( int )LevelData + 8 );
	WriteMemory( 0x0045B254 + 3, ( int )LevelData + 8 );
	WriteMemory( 0x00461FCD + 3, ( int )LevelData + 8 );
	WriteMemory( 0x004620C7 + 3, ( int )LevelData + 8 );
	WriteMemory( 0x004A9A5E + 3, ( int )LevelData + 8 );
	WriteMemory( 0x004A9ABA + 3, ( int )LevelData + 8 );

	WriteMemory( 0x0045A5EC + 1, ( int )LevelData + 10 );

	WriteMemory( 0x0045B1F8 + 3, ( int )LevelData + 12 );
	WriteMemory( 0x0045B25B + 3, ( int )LevelData + 12 );
	WriteMemory( 0x00461FD4 + 3, ( int )LevelData + 12 );
	WriteMemory( 0x004620CE + 3, ( int )LevelData + 12 );
	WriteMemory( 0x004A9A67 + 3, ( int )LevelData + 12 );
	WriteMemory( 0x004A9AC3 + 3, ( int )LevelData + 12 );
};

int CLevelManager::AddExperience( int64 Exp )
{
	typedef int64( __cdecl* t_XorExp ) ( );
	t_XorExp XorExp = ( t_XorExp )0x0045AFE0;
	typedef void( __cdecl* t_SetExp ) ( int ClassPointer, int64 Exp );
	t_SetExp SetExp = ( t_SetExp )0x0045B190;
	typedef void( __cdecl* t_ReformChar )( );
	t_ReformChar ReformChar = ( t_ReformChar )0x0045D430;
	typedef void( __cdecl* t_StartEffect )( int, int, int, int, int );
	t_StartEffect StartEffect = ( t_StartEffect )0x00587240;
	typedef void( __cdecl* t_PlaySound )( int, int );
	t_PlaySound PlaySound = ( t_PlaySound )0x0054BE80;
	typedef void( __cdecl* t_SendPlayerUpdateInfo )( );
	t_SendPlayerUpdateInfo SendPlayerInfo = ( t_SendPlayerUpdateInfo )0x00636B20;
	typedef void( __cdecl* t_SaveGame )( );
	t_SaveGame SaveGame = ( t_SaveGame )0x00636770;

	int64 CharacterExp = XorExp( );
	CharacterExp += Exp;
	if( CharacterExp >= m_Level[ LEVEL_CAP ] )
		CharacterExp = m_Level[ LEVEL_CAP ] - 1;

	SetExp( *( int* )( 0x00D22894 ) + 0x3924, CharacterExp );

	XorExp( );

	ReformChar( );

	int CharLevel = *( int* )( *( int* )( 0x00D22894 ) + 0x39DC );
	int OldLevel = CharLevel;

	//TODO: CheckSum

	if( Exp && CharLevel < LEVEL_CAP )
	{
		while( true )
		{
			if( m_Level[ CharLevel ] > CharacterExp && CharacterExp <= m_Level[ CharLevel + 1 ] )
				break;
			CharLevel++;
			if( CharLevel >= LEVEL_CAP )
				break;
		};

		if( OldLevel == CharLevel )
			return ( int )( Exp & 0xFFFFFFFF );

		*( int* )( *( int* )( 0x00D22894 ) + 0x39DC ) = CharLevel;
		*( int* )( *( int* )( 0x00D22894 ) + 0x3A64 ) = ( int )( m_Level[ CharLevel + 1 ] & 0xFFFFFFFF );

		StartEffect( *( int* )( *( int* )( 0x00D22894 ) + 0x1E0 ),
					 *( int* )( *( int* )( 0x00D22894 ) + 0x1E4 ) + 8192,
					 *( int* )( *( int* )( 0x00D22894 ) + 0x1E8 ),
					 300, 1 );
		PlaySound( 7, 400 );
		ReformChar( );
		SendPlayerInfo( );
		SaveGame( );
	};

	return ( int )( Exp & 0xFFFFFFFF );
};

int __cdecl _AddExp( int64 Exp )
{
	std::shared_ptr<CLevelManager> lpLevel = std::make_shared<CLevelManager>( );
	return lpLevel->AddExperience( Exp );
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