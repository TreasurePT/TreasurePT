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
	char* Buffer = new char[ lstrlenA( Text ) + 1 ]( );

	va_list Args = { 0 };
	va_start( Args, Text );

	if( StringCbVPrintfA( Buffer, 512, Text, Args ) >= 0 )
	{
		lstrcpyA( ( char* )( Address + m_Spacements ), Buffer );
		m_Spacements += lstrlenA( Buffer ) + 1;

		goto End;
	};

End:
	va_end( Args );
	delete[ ] Buffer;
	return;
};

void CTranslate::SetTexts( )
{
	Translate( 0x005EDA28, "Prova: %s",
			   "Titulo traduzido" );
};

void __cdecl _SetTexts( )
{
	std::shared_ptr<CTranslate> lpTrans = std::make_shared<CTranslate>( );
	lpTrans->SetTexts( );
};