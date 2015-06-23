#include "stdafx.h"
#include "file_manager.h"

extern void __cdecl _SetTexts( );
extern long __cdecl _CheckExpGained( long Exp, long Player );
extern void __cdecl _BuildItems( );

class CServer
{
public:
	void Main( );
	void ReadVersion( );
};

void CServer::Main( )
{
	_SetTexts( );
	_BuildItems( );


	*( long* )( PDATA + 0 ) = ( long )( &_CheckExpGained );
};

void CServer::ReadVersion( )
{
	std::shared_ptr<CFileManager> lpFile = std::make_shared<CFileManager>( "hotuk.ini" );

};





void Main( )
{
	std::shared_ptr<CServer> lpServer = std::make_shared<CServer>( );
	return lpServer->Main( );
};