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
};

void CServer::Main( )
{
	_SetTexts( );
	_BuildItems( );

	*( int* )( PDATA + 0 ) = ( int )( &_CheckExpGained );
};






void Main( )
{
	std::shared_ptr<CServer> lpServer = std::make_shared<CServer>( );
	return lpServer->Main( );
};