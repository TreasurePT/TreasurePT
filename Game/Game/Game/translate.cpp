#include "stdafx.h"
#include "translate.h"

long CTranslate::m_Address_Text = 0;
long CTranslate::m_Spacements = 0;

long CSkillTranslate::m_Address_Text = 0;
long CSkillTranslate::m_Spacements = 0;

void CSkillTranslate::Name( const char* Text, ... )
{
	char Buffer[ 1024 ] = { 0 };

	va_list Args = { 0 };
	va_start( Args, Text );

	if( StringCbVPrintfA( Buffer, 1024, Text, Args ) >= 0 )
	{
		DWORD Old_Protect = 0, New_Protect = 0;
		VirtualProtect( ( void* )( m_Address_Text + m_Spacements ), 0x12C, PAGE_READWRITE, &Old_Protect );
		lstrcpyA( ( char* )( m_Address_Text + m_Spacements ), Buffer );
		New_Protect = Old_Protect;
		VirtualProtect( ( void* )( m_Address_Text + m_Spacements ), 0x12C, New_Protect, &Old_Protect );

		goto End;
	};

End:
	va_end( Args );
	return;
};

void CSkillTranslate::Description( const char* Text, ... )
{
	char Buffer[ 1024 ] = { 0 };

	va_list Args = { 0 };
	va_start( Args, Text );

	if( StringCbVPrintfA( Buffer, 1024, Text, Args ) >= 0 )
	{
		DWORD Old_Protect = 0, New_Protect = 0;
		VirtualProtect( ( void* )( m_Address_Text + m_Spacements + 64 ), 0x12C, PAGE_READWRITE, &Old_Protect );
		lstrcpyA( ( char* )( m_Address_Text + m_Spacements + 64 ), Buffer );
		New_Protect = Old_Protect;
		VirtualProtect( ( void* )( m_Address_Text + m_Spacements + 64 ), 0x12C, New_Protect, &Old_Protect );
		m_Spacements += 0x12C;

		goto End;
	};

End:
	va_end( Args );
	return;
};

CSkillTranslate::CSkillTranslate( )
{
	if( !m_Address_Text )
	{
		m_Address_Text = ( long )( 0x0098F668 );
		m_Spacements = 0;
	};
};

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

	//Menu D
	Translate( 0x009F2D5C, "Ignorados: %%d / %%d" );
	Translate( 0x009F2D58, "Amigos: %%d / %%d" );
	Translate( 0x009F2D54, "Recentes" );

	//Comandos
	Translate( 0x004ACEB4, "/nivel" );
	Translate( 0x004ACF1C, "GM: Nível alterado com sucesso" );

	//Itens
	Translate( 0x0098E230, "Ataque:        \r" );
	Translate( 0x0098E234, "Vel. da Arma:  \r" );
	Translate( 0x0098E238, "Alcance:       \r" );
	Translate( 0x0098E23C, "Crítico:       \r" );
	Translate( 0x0098E240, "Defesa:        \r" );
	Translate( 0x0098E244, "Precisão:      \r" );
	Translate( 0x0098E248, "Absorção:      \r" );
	Translate( 0x0098E24C, "Bloqueio:      \r" );
	Translate( 0x0098E250, "Velocidade:    \r" );
	Translate( 0x0098E254, "Integridade:   \r" );
	Translate( 0x0098E258, "Rec. Mana:     \r" );
	Translate( 0x0098E25C, "Rec. de Vida:  \r" );
	Translate( 0x0098E260, "Rec. Estamina: \r" );
	Translate( 0x0098E264, "Res. a Terra:  \r" );
	Translate( 0x0098E26C, "Res. a Fogo:   \r" );
	Translate( 0x0098E270, "Res. a Gelo:   \r" );
	Translate( 0x0098E274, "Res. a Raio:   \r" );
	Translate( 0x0098E278, "Res. a Veneno: \r" );
	Translate( 0x0098E284, "Reg. Vida:     \r" );
	Translate( 0x0098E288, "Reg. Mana:     \r" );
	Translate( 0x0098E28C, "Reg. Estamina: \r" );
	Translate( 0x0098E290, "Vida:          \r" );
	Translate( 0x0098E294, "Mana:          \r" );
	Translate( 0x0098E298, "Estamina:      \r" );
	Translate( 0x0098E29C, "Poções:        \r" );
	Translate( 0x0098E2A0, "Nível:         \r" );
	Translate( 0x0098E2A4, "Força:         \r" );
	Translate( 0x0098E2A8, "Inteligência:  \r" );
	Translate( 0x0098E2AC, "Talento:       \r" );
	Translate( 0x0098E2B0, "Agilidade:     \r" );
	Translate( 0x0098E2B4, "Vitalidade:    \r" );
	Translate( 0x0098E3C0, "Spec %%s\r" );
	Translate( 0x0098E2F8, "Vel. da Arma:  \r" );
	Translate( 0x0098E2FC, "Crítico:       \r" );
	Translate( 0x0098E300, "Defesa:        \r" );
	Translate( 0x0098E304, "Absorção:      \r" );
	Translate( 0x0098E308, "Bloqueio:      \r" );
	Translate( 0x0098E30C, "Bônus Mágico:  \r" );
	Translate( 0x0098E310, "Velocidade:    \r" );
	Translate( 0x0098E334, "Ataque:        \r" );
	Translate( 0x004CDB06, "NV/%%d\r" );
	Translate( 0x0098E338, "Precisão:      \r" );
	Translate( 0x004CDB51, "NV/%%d\r" );
	Translate( 0x0098E33C, "Alcance:       \r" );
	Translate( 0x0098E360, "Vida:          \r" );
	Translate( 0x004CDE4F, "NV/%%d\r" );
	Translate( 0x0098E364, "Mana:          \r" );
	Translate( 0x004CDE9A, "NV/%%d\r" );
	Translate( 0x0098E368, "Reg. Vida:     \r" );
	Translate( 0x0098E36C, "Reg. Mana:     \r" );
	Translate( 0x0098E370, "Reg. Estamina: \r" );
	Translate( 0x0098E374, "Preço:         \r" );
	Translate( 0x0098E378, "Preço:         \r" );

	//Habilidades
	std::shared_ptr<CSkillTranslate> lpSkillTranslate = std::make_shared<CSkillTranslate>( );
	Translate( 0x0098E3D0, "Ataque Padrão\r" );
	Translate( 0x0098E3D4, "%%s (Nível Necessário: %%d)\r" );
	Translate( 0x0098E3D8, "Itens Compatíveis\r" );
	Translate( 0x0098E3CC, "Próximo Nível\r" );
	Translate( 0x0098E3F8, "Bloqueio:            \r" );
	Translate( 0x0098E3FC, "Duração:             \r" );
	Translate( 0x004F757A, "%%d segundos\r" );
	Translate( 0x0098E410, " segundos\r" );

	lpSkillTranslate->Name( "Escudo Extremo" );
	lpSkillTranslate->Description( "Defende! Pronto foda-se." );
	lpSkillTranslate->Name( "Bomba Mecânica" );
	lpSkillTranslate->Description( "Ataca! Pronto foda-se." );
	//Translate( 0x00, "" );
};

void __cdecl _SetTexts( )
{
	std::shared_ptr<CTranslate> lpTrans = std::make_shared<CTranslate>( );
	lpTrans->SetTexts( );
};