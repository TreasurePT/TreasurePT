#include "stdafx.h"
#include "file_manager.h"

extern void __cdecl _SetTexts( );
extern long __cdecl _CheckExpGained( long Exp, long Player );
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

	*( long* )( PDATA + 0 ) = ( long )( &_CheckExpGained );
};






void Main( )
{
	std::shared_ptr<CServer> lpServer = std::make_shared<CServer>( );
	return lpServer->Main( );
};