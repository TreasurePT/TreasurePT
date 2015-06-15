#include "stdafx.h"

extern void __cdecl _SetTexts( );

class CServer
{
public:
	void Main( );
};

void Main( )
{
	std::shared_ptr<CServer> lpServer = std::make_shared<CServer>( );
	return lpServer->Main( );
};

void CServer::Main( )
{
	_SetTexts( );
};