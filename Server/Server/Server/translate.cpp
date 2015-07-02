#include "stdafx.h"
#include "translate.h"

int CTranslate::m_Address_Text = 0;
int CTranslate::m_Spacements = 0;

CTranslate::CTranslate( )
{
	if( !m_Address_Text )
	{
		m_Address_Text = ( int )( VirtualAlloc(
			nullptr,
			TOTAL_TEXT_TRANSLATED * 100,
			MEM_COMMIT | MEM_RESERVE,
			PAGE_READWRITE ) );
		m_Spacements = 0;
	};
};

void CTranslate::Translate( int Address, const char* Text, ... )
{
	char Buffer[ 1024 ] = { 0 };

	va_list Args = { 0 };
	va_start( Args, Text );

	if( StringCbVPrintfA( Buffer, 1024, Text, Args ) >= 0 )
	{
		DWORD Old_Protect = 0, New_Protect = 0;
		VirtualProtect( ( void* )( Address ), 4, PAGE_READWRITE, &Old_Protect );
		lstrcpyA( ( char* )( m_Address_Text + m_Spacements ), Buffer );
		*( int* )( Address ) = ( m_Address_Text + m_Spacements );
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
	//Mensagem ao logar
	Translate( 0x006E2A1C, "> Seja Bem Vindo ao Treasure Priston Tale > Qualquer dúvida, acesse nosso site:      > www.treasurept.com.br" );
	
	//Mensagens
	Translate( 0x006E29F8, "Você recebeu um item: %%s" );

	//Interface
	Translate( 0x0055C30F, "[%s]\r\n%s: %%d\r\n%s: %%s\r\n%s: %%09d\r\n%s: %%d\r\n%s: %%d\r\n%s: %%d\r\n%s: %%d",
			   "Configuração",
			   "Código do Servidor",
			   "Nome do Servidor",
			   "Versão",
			   "Contagem de Códigos Seguros",
			   "Contagem de CheckSum's",
			   "Monstros",
			   "Items" );

	//Cristais, Summon, Navisco
	Translate( 0x006E2A2C, "Zumbi" );

	//Grupo
	Translate( 0x006E26B4, "A diferença de níveis é muito grande" );
	Translate( 0x006E26A8, "%%s já está em outro grupo" );
	Translate( 0x006E26AC, "%%s já está em outro grupo" );
	Translate( 0x006E26B0, "%%s já está em outro grupo" );
	Translate( 0x006E26A4, "Você enviou um pedido de grupo para %%s" );
	Translate( 0x006E2704, "%%s é o novo líder do grupo" );
	Translate( 0x006E4E08, "%%s é o novo líder do grupo" );
	Translate( 0x006E26A0, "%%s decidirá se %%s entrará no grupo" );
	Translate( 0x006E26F4, "Você saiu do grupo" );
	Translate( 0x006E4E18, "%%s saiu do grupo" );
	Translate( 0x006E26F8, "%%s foi removido do grupo" );
	Translate( 0x006E2700, "O grupo foi desfeito" );
	Translate( 0x006E4E0C, "O grupo foi desfeito" );

	//Mensagem Pessoal
	Translate( 0x006E26BC, "%%s não existe ou está desconectado" );
	Translate( 0x0056F1B8, "Para> %%s: %%s" );
	Translate( 0x00552E18, "De> %%s: %%s" );
	Translate( 0x0056F149, "De> %%s: %%s" );
	Translate( 0x0056F218, "De> %%s: %%s" );
	Translate( 0x006E2724, "O jogador desativou as mensagens pessoais" );
	Translate( 0x006E2728, "Mensagem Pessoal desativada" );
	Translate( 0x006E272C, "Mensagem Pessoal ativada" );

	//Comandos Player
	Translate( 0x00414105, "/troca %s" );
	Translate( 0x004140E5, "/clan %s" );
	Translate( 0x0056BEA6, "/grupo" );
	Translate( 0x0056BE94, "/GRUPO" );
	Translate( 0x0056BDF2, "/troca " );
	Translate( 0x0056C25E, "/clan " );
	Translate( 0x0056C1C5, "/desligamensagem" );
	Translate( 0x0056C209, "/ligamensagem" );
	Translate( 0x0056C16E, "%%s: %%s" );
	Translate( 0x0056C2A9, "%%s: %%s" );
	Translate( 0x0047B01B, "%%s: %%s" );
	Translate( 0x00488196, "%%s: %%s" );
	Translate( 0x0048E00B, "%%s: %%s" );
	Translate( 0x004A1137, "%%s: %%s" );
	Translate( 0x0056BE4D, "%%s: %%s" );

	//Translate( 0x00, "" );
};

void __cdecl _SetTexts( )
{
	std::shared_ptr<CTranslate> lpTrans = std::make_shared<CTranslate>( );
	lpTrans->SetTexts( );
};