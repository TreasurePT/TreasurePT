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
	//Login
	Translate( 0x008368F0, "TreasurePT" );
	Translate( 0x009F2A7C, "http://www.treasurept.com.br" );
	Translate( 0x005A94FD, "Versão: " );
	Translate( 0x009F2C88, "Estabelecendo a conexão..." );
	Translate( 0x009F2C8C, "Impossível conectar" );
	Translate( 0x009F2C90, "Conta incorreta" );
	Translate( 0x009F2C94, "Senha incorreta" );
	Translate( 0x009F2C98, "Conta banida" );
	Translate( 0x009F2C9C, "Esta conta já está logada" );
	Translate( 0x009F2CA4, "O servidor está cheio" );
	
	//Char Select
	Translate( 0x009F2CF0, "Você tem certeza que deseja deletar esse personagem?" );
	Translate( 0x009F2CF4, "Você deseja continuar esta aventura?" );
	Translate( 0x009F2CF8, "Cada conta só pode ter no máximo 5 personagens" );
	Translate( 0x009F2CFC, "Você tem certeza que deseja este nome para o seu personagem?" );
	Translate( 0x009F2D00, "Digite um nome para o seu personagem" );
	Translate( 0x009F2D04, "Já existe um personagem com este nome. Por favor, escolha outro" );
	Translate( 0x009F2D08, "Escolha um personagem" );
	Translate( 0x009F2D0C, "Escolha uma tribo" );
	Translate( 0x009F2D10, "Escolha uma classe" );
	Translate( 0x009F2D18, "Este personagem faz parte de um Clã e por isso não pode ser deletado" );
	Translate( 0x009F2D50, "Tempskron" );
	Translate( 0x009F2D34, "Morion" );

	//Classes
	Translate( 0x00837EC4, "Mecânico" );
	Translate( 0x00837EF0, "Lutador" );
	Translate( 0x00837F1C, "Pike" );
	Translate( 0x00837F48, "Arqueira" );	
	Translate( 0x00838310, "Cavaleiro" );
	Translate( 0x0083833C, "Atalanta" );
	Translate( 0x00838368, "Sacerdotisa" );
	Translate( 0x00838394, "Mago" );

	//Ajuda e Guia
	Translate( 0x0098E524, "    Ajuda" );
	Translate( 0x0064FFF6, "> Abrir Guia" );
	Translate( 0x00650015, "> Abrir Guia" );

	//Comandos
	Translate( 0x004ACEB4, "/nivel" );
	Translate( 0x004ACF1C, "GM: Nível alterado com sucesso" );

	//Translate( 0x00, "" );
};

void __cdecl _SetTexts( )
{
	std::shared_ptr<CTranslate> lpTrans = std::make_shared<CTranslate>( );
	lpTrans->SetTexts( );
};