#include "stdafx.h"
#include "translate.h"

long CTranslate::m_Address_Text = 0;
long CTranslate::m_Spacements = 0;

CTranslate::CTranslate( )
{
	if( !m_Address_Text )
	{
		m_Address_Text = ( long )( VirtualAlloc(
			nullptr,
			TOTAL_TEXT_TRANSLATED * 100,
			MEM_COMMIT | MEM_RESERVE,
			PAGE_READWRITE ) );
		m_Spacements = 0;
	};
};

void CTranslate::Translate( long Address, const char* Text, ... )
{
	char Buffer[ 1024 ] = { 0 };

	va_list Args = { 0 };
	va_start( Args, Text );

	if( StringCbVPrintfA( Buffer, 1024, Text, Args ) >= 0 )
	{
		DWORD Old_Protect = 0, New_Protect = 0;
		VirtualProtect( ( void* )( Address ), 4, PAGE_READWRITE, &Old_Protect );
		lstrcpyA( ( char* )( m_Address_Text + m_Spacements ), Buffer );
		*( long* )( Address ) = ( m_Address_Text + m_Spacements );
		New_Protect = Old_Protect;
		VirtualProtect( ( void* )( Address ), 4, New_Protect, &Old_Protect );
		m_Spacements += lstrlenA( Buffer ) + 1;

		goto End;
	};

End:
	va_end( Args );
	return;
};

void CTranslate::SetTexts( )
{
	//Translate( 0x00, "" );
};

void __cdecl _SetTexts( )
{
	std::shared_ptr<CTranslate> lpTrans = std::make_shared<CTranslate>( );
	lpTrans->SetTexts( );
};