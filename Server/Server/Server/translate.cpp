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

	//Comandos GM
	Translate( 0x0056EF64, "Autorizado: %%d - %%d" );
	Translate( 0x0056EEE9, "/autorizacao" );
	Translate( 0x0056EEA8, "Evento: %%d" );
	Translate( 0x0056EE84, "/evento" );
	Translate( 0x0056EE43, "ID: %%s - GPCode: %%s - PCRno: %%d - GPType: %%d" );
	Translate( 0x0056EE0A, "/desconhecido_get_guid" );
	Translate( 0x0056EDAD, "Ataque: %%d %%d %%d" );
	Translate( 0x0056ED70, "/ataque" );
	Translate( 0x0056ED5E, "Ouro: %%d - %%d" );
	Translate( 0x0056ED2E, "/servidor_ouro" );
	Translate( 0x0056ECFE, "Você está visível" );
	Translate( 0x0056ECDF, "/visivel" );
	Translate( 0x00587483, "/visivel" );
	Translate( 0x0056ECD7, "Você está invisível" );
	Translate( 0x0056ECB4, "/invisivel" );
	Translate( 0x005874B5, "/invisivel" );
	Translate( 0x0056ECAC, "Conta desbloqueada" );
	Translate( 0x0056EC6A, "/desbloquear_conta" );
	Translate( 0x0056EC54, "Todas as contas foram desbloqueadas" );
	Translate( 0x0056EC36, "/desbloquear_todas" );
	Translate( 0x005548B1, "Contas Bloqueadas: %%d" );
	Translate( 0x0056EBDC, "/listar_bloqueados" );
	Translate( 0x0056EBC1, "Clã: %%d - Taxa Atual: %%d - Próxima Taxa: %%d" );
	Translate( 0x0056EB8B, "/cs_taxa" );
	Translate( 0x0056EB80, "Fonte Sagrada resetada - Tempo: %%d" );
	Translate( 0x0056EB54, "/cs_resetar_fonte" );
	Translate( 0x0056EB25, "Fonte Sagrada - Poções Restantes: %%d - Último Usuário: %%d - Tempo Inicial: %%d - Tempo Final: %%d - Contagem: %%d" );
	Translate( 0x0056EADE, "/cs_fonte" );
	Translate( 0x0056EAC9, "Clã: %%d - Taxa Atual: %%d - Próxima Taxa: %%d - Clã: %%d / %%d - Modo: %%d" );
	Translate( 0x0056EA84, "/cs_info" );
	Translate( 0x0056EA36, "Novo Líder: %%d" );
	Translate( 0x0056E9B6, "/cs_lider" );
	Translate( 0x0056E93F, "/cs_tempo" );
	Translate( 0x0056E907, "/cs_facil" );
	Translate( 0x0056E8CC, "/cs_finalizar" );
	Translate( 0x0056E848, "/cs_iniciar" );
	Translate( 0x0056E7E7, "Bandeiras: %%d - Nasceram: %%d - Monstros: %%d - Total: %%d - Tempo Máximo: %%d" );
	Translate( 0x0056E675, "/info_mapa" );
	Translate( 0x0056E63E, "Evento - Monstro: %%s - Tempo Restante: %%d segundos - Quantidade: %%d" );
	Translate( 0x0056E5DF, "Evento - Monstro: %%s - Tempo: %%d minutos - Quantidade: %%d" );
	Translate( 0x0056E41E, "/monstro_evento" );
	Translate( 0x0056E2A4, "/monstro_cristal" );
	Translate( 0x0056E12F, "/monstro_invocar" );
	Translate( 0x0056E0F0, "/monstro_arena" );
	Translate( 0x0056E0E5, "Mapa: %%d - Usuários: %%d" );
	Translate( 0x0056DFC6, "/usuarios_mapa" );
	Translate( 0x0056DFA6, "Visão: Longe" );
	Translate( 0x0056DF87, "Visão: Perto" );
	Translate( 0x0056DF42, "/personagem_visao" );
	Translate( 0x0056DED7, "%%s - Absorção: %%d -> %%d" );
	Translate( 0x0056DE49, "/monstro_absorcao" );
	Translate( 0x00566F83, "/monstro_absorcao" );
	Translate( 0x0056DD7B, "/fala" );
	Translate( 0x00586F45, "/fala" );
	Translate( 0x0056DD4C, "/desconhecido_socket" );
	Translate( 0x0056DCEF, "/usuarios_conectados" );
	Translate( 0x0056DCC7, "Dropando %%d Ouro..." );
	Translate( 0x0056DB9D, "/ouro" );
	Translate( 0x0056DB64, "Experiência: %%d" );
	Translate( 0x0056DAD1, "/servidor_experiencia" );
	Translate( 0x0056D9CC, "/usuario_localizacao" );
	Translate( 0x0056D9BA, "/USUARIO_LOCALIZACAO" );
	Translate( 0x0056D8CE, "/usuario_chamar" );
	Translate( 0x0056D8BC, "/USUARIO_CHAMAR" );
	Translate( 0x0056D7D0, "/usuario_ir" );
	Translate( 0x0056D7BE, "/USUARIO_IR" );
	Translate( 0x0056D6FA, "/usuario_nome" );
	Translate( 0x0056D6E8, "/USUARIO_NOME" );
	Translate( 0x0056D644, "/usuario_conta" );
	Translate( 0x0056D632, "/USUARIO_CONTA" );
	Translate( 0x0056D584, "/grupo_sair" );
	Translate( 0x0056D521, "/grupo_separar" );
	Translate( 0x0056D468, "/grupo_convidar" );
	Translate( 0x0056D405, "/grupo_remover" );
	Translate( 0x0056D309, "/grupo_info" );
	Translate( 0x0056D1F2, "/inserir" );
	Translate( 0x0056D180, "/servidor_desligar" );
	Translate( 0x006E2828, "GM> Aviso!" );
	Translate( 0x006E282C, "GM> O servidor entrará em manutenção" );
	Translate( 0x006E2830, "GM> Por favor, desconecte-se imediatamente" );
	Translate( 0x006E2834, "GM> Mais informações no nosso site" );
	Translate( 0x006E2838, "GM> Obrigado por jogar no TreasurePT" );
	Translate( 0x006E29E0, "GM> O servidor desligará em %dmin%ds" );
	Translate( 0x0056D0A3, "/abrir_armazem" );
	Translate( 0x0056CFF9, "Você matou %%s" );
	Translate( 0x0056CF73, "/matar" );
	Translate( 0x0056CE76, "/desconectar" );
	Translate( 0x0056CDA1, "/desconhecido_codigo" );
	Translate( 0x0056CCEB, "/desconhecido_restricao" );
	Translate( 0x0056CCC8, "/conexao_info" );
	Translate( 0x0056CCB6, "/CONEXAO_INFO" );
	Translate( 0x0056CBC4, "Vida: %%d %%d %%d %%d - Mana: %%d %%d %%d - Estamina: %%d %%d %%d %%d" );
	Translate( 0x0056CB05, "/servidor_pocoes" );
	Translate( 0x0056C9E6, "/cabecao" );
	Translate( 0x0056C901, "/item_inventorio" );
	Translate( 0x0056C89C, "/item_chao" );
	Translate( 0x0056C834, "Ataque: %%d - Tempo Restante: 1 minuto" );
	Translate( 0x0056C7F9, "/desconhecido_item" );
	Translate( 0x0056C796, "Spec: %%d - Tempo Restante: 1 minuto" );
	Translate( 0x0056C756, "/desconhecido_spec" );
	Translate( 0x0056C723, "Mix: %%d - Aging: %%d - Pedra: %%d - Ataque: %%d %%d %%d - Força Orb: %%d - Armas: %%d - Habilidades: %%d - Atributos: %%d" );
	Translate( 0x0056C5E9, "Mix: %%d - Aging: %%d - Pedra: %%d - Ataque: %%d %%d %%d - Força Orb: %%d - Armas: %%d - Habilidades: %%d - Atributos: %%d" );
	Translate( 0x0056C532, "/servidor_infos" );
	Translate( 0x0056C503, "%%d> Força Orb - ID: %%d - Tempo Restante: %%d - Ataque: %%d" );
	Translate( 0x0056C4B9, "/forca_orb" );
	Translate( 0x0056C4A4, "%%d> Aparecimento dos Chefes: xx:%%d" );
	Translate( 0x0056C482, "/servidor_chefes" );
	Translate( 0x0056C453, "%%d> %%d/%%d/%%d - %%d:%%d:%%d" );
	Translate( 0x0056C3F3, "/servidor_horario" );
	Translate( 0x0056C3B7, "/bellatra_entrar" );
	Translate( 0x0056C38B, "/bellatra_info" );
	Translate( 0x0056C332, "/noticias" );

	//Comandos Player
	Translate( 0x00414105, "/troca %s" );
	Translate( 0x004140E5, "/clan %s" );
	Translate( 0x0056BEA6, "/grupo" );
	Translate( 0x0056BE94, "/GRUPO" );
	Translate( 0x0056BDF2, "/troca " );
	Translate( 0x0056C25E, "/clan " );
	Translate( 0x0056C1C5, "/desliga_mensagem" );
	Translate( 0x0056C209, "/liga_mensagem" );
	Translate( 0x0056C16E, "%%s: %%s" );
	Translate( 0x0056C2A9, "%%s: %%s" );
	Translate( 0x0047B01B, "%%s: %%s" );
	Translate( 0x00488196, "%%s: %%s" );
	Translate( 0x0048E00B, "%%s: %%s" );
	Translate( 0x004A1137, "%%s: %%s" );
	Translate( 0x0056BE4D, "%%s: %%s" );

	//Castelo Sagrado
	Translate( 0x006E29E8, "GM> A batalha pelo controle do Castelo Sagrado começou. Boa sorte a todos os Clãs." );
	Translate( 0x006E29EC, "GM> A batalha pelo controle do Castelo Sagrado terminou. Parabéns ao Clã vencedor." );

	//Translate( 0x00, "" );
};

void __cdecl _SetTexts( )
{
	std::shared_ptr<CTranslate> lpTrans = std::make_shared<CTranslate>( );
	lpTrans->SetTexts( );
};