#include "stdafx.h"
#include "file_manager.h"
#include "player_info.h"

extern void __cdecl _SetTexts( );
extern int __cdecl _CheckExpGained( int Exp, CPlayerInfo* Player );
extern void __cdecl _BuildItems( );

class CServer
{
public:
	void Main( );
	void ReadConfigs( );
private:
	char m_Buffer[ 256 ];
};

void CServer::Main( )
{
	//ReadConfigs( );
	_SetTexts( );
	_BuildItems( );

	*( int* )( PDATA + 0 ) = ( int )( &_CheckExpGained );
};
/*
void CServer::ReadConfigs( )
{
	SecureZeroMemory( m_Buffer, 256 );
	std::shared_ptr<CFileManager> lpFile = std::make_shared<CFileManager>( "hotuk.ini" );
	lpFile->GetString( "TreasurePT", "Versao", m_Buffer );
	*( int* )( 0x006E4F5C ) = atoi( lpFile->Format( "%09d", atoi( m_Buffer ) ) );
};*/


void Main( )
{
	std::shared_ptr<CServer> lpServer = std::make_shared<CServer>( );
	return lpServer->Main( );
};