#include "stdafx.h"
#include "UI_login.h"

CUILogin::CUILogin( )
{
	SecureZeroMemory( m_Buffer, 256 );
	SecureZeroMemory( m_Version, 256 );
};

int CUILogin::ShowVersion( HDC hDC )
{
	StringCbPrintfA( m_Buffer, 256, "%09d", VERSION );
	int c = 0;
	for( int i = 0; i < 9; i++ )
	{
		if( i == 2 || i == 4 || i == 8 )
		{
			m_Version[ i + c ] = '.';
			c++;
		}
		m_Version[ i + c ] = m_Buffer[ i ];
	};
	StringCbCopyA( m_Buffer, 256, m_Version );
	StringCbPrintfA( m_Version, 256, "Versão: %s", m_Buffer );
	return ShowTextA( hDC, ( *( int* )( 0x03AD4CA4 ) - 128 ), ( *( int* )( 0x03AD4CA8 ) - 58 ),
					  m_Version, lstrlenA( m_Version ) );
};

int __cdecl _ShowVersion( HDC hDC )
{
	std::shared_ptr<CUILogin> lpVer = std::make_shared<CUILogin>( );
	return lpVer->ShowVersion( hDC );
};