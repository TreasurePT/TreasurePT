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
		SetTexts( );
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
	Translate( 0x005A94FD, "Vers�o: " );
	Translate( 0x009F2C88, "Estabelecendo a conex�o..." );
	Translate( 0x009F2C8C, "Imposs�vel conectar" );
	Translate( 0x009F2C90, "Conta incorreta" );
	Translate( 0x009F2C94, "Senha incorreta" );
	Translate( 0x009F2C98, "Conta banida" );
	Translate( 0x009F2C9C, "Esta conta j� est� logada" );
	Translate( 0x009F2CA4, "O servidor est� cheio" );

	//Char Select
	Translate( 0x009F2CF0, "Voc� tem certeza que deseja deletar esse personagem?" );
	Translate( 0x009F2CF4, "Voc� deseja continuar esta aventura?" );
	Translate( 0x009F2CF8, "Cada conta s� pode ter no m�ximo 5 personagens" );
	Translate( 0x009F2CFC, "Voc� tem certeza que deseja este nome para o seu personagem?" );
	Translate( 0x009F2D00, "Digite um nome para o seu personagem" );
	Translate( 0x009F2D04, "J� existe um personagem com este nome. Por favor, escolha outro" );
	Translate( 0x009F2D08, "Escolha um personagem" );
	Translate( 0x009F2D0C, "Escolha uma tribo" );
	Translate( 0x009F2D10, "Escolha uma classe" );
	Translate( 0x009F2D18, "Este personagem faz parte de um Cl� e por isso n�o pode ser deletado" );
	Translate( 0x009F2D50, "Tempskron" );
	Translate( 0x009F2D34, "Morion" );

	//Classes
	Translate( 0x00837EC4, "Mec�nico" );
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
	Translate( 0x004ACF1C, "GM: N�vel alterado com sucesso" );

	//Itens
	Translate( 0x0098E230, "Ataque:        \r" );
	Translate( 0x0098E234, "Vel. da Arma:  \r" );
	Translate( 0x0098E238, "Alcance:       \r" );
	Translate( 0x0098E23C, "Cr�tico:       \r" );
	Translate( 0x0098E240, "Defesa:        \r" );
	Translate( 0x0098E244, "Precis�o:      \r" );
	Translate( 0x0098E248, "Absor��o:      \r" );
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
	Translate( 0x0098E29C, "Po��es:        \r" );
	Translate( 0x0098E2A0, "N�vel:         \r" );
	Translate( 0x0098E2A4, "For�a:         \r" );
	Translate( 0x0098E2A8, "Intelig�ncia:  \r" );
	Translate( 0x0098E2AC, "Talento:       \r" );
	Translate( 0x0098E2B0, "Agilidade:     \r" );
	Translate( 0x0098E2B4, "Vitalidade:    \r" );
	Translate( 0x0098E3C0, "Spec %%s\r" );
	Translate( 0x0098E2F8, "Vel. da Arma:  \r" );
	Translate( 0x0098E2FC, "Cr�tico:       \r" );
	Translate( 0x0098E300, "Defesa:        \r" );
	Translate( 0x0098E304, "Absor��o:      \r" );
	Translate( 0x0098E308, "Bloqueio:      \r" );
	Translate( 0x0098E30C, "B�nus M�gico:  \r" );
	Translate( 0x0098E310, "Velocidade:    \r" );
	Translate( 0x0098E334, "Ataque:        \r" );
	Translate( 0x004CDB06, "NV/%%d\r" );
	Translate( 0x0098E338, "Precis�o:      \r" );
	Translate( 0x004CDB51, "NV/%%d\r" );
	Translate( 0x0098E33C, "Alcance:       \r" );
	Translate( 0x0098E360, "Vida:          \r" );
	Translate( 0x004CDE4F, "NV/%%d\r" );
	Translate( 0x0098E364, "Mana:          \r" );
	Translate( 0x004CDE9A, "NV/%%d\r" );
	Translate( 0x0098E368, "Reg. Vida:     \r" );
	Translate( 0x0098E36C, "Reg. Mana:     \r" );
	Translate( 0x0098E370, "Reg. Estamina: \r" );
	Translate( 0x0098E374, "Pre�o:         \r" );
	Translate( 0x0098E378, "Pre�o:         \r" );

	//Monstros
	Translate( 0x0098E5C0, "Mec�nico" );
	Translate( 0x0098E5C4, "Dem�nio" );
	Translate( 0x0098E5BC, "Mutante" );
	Translate( 0x0098E5CC, "Morto-Vivo" );

	//Habilidades
	std::shared_ptr<CSkillTranslate> lpSkillTranslate = std::make_shared<CSkillTranslate>( );
	Translate( 0x0098E3D0, "Ataque Padr�o\r" );
	Translate( 0x0098E3D4, "%%s (N�vel Necess�rio: %%d)\r" );
	Translate( 0x0098E3D8, "Itens Compat�veis\r" );
	Translate( 0x0098E3CC, "Pr�ximo N�vel\r" );
	Translate( 0x0098E3F8, "Bloqueio:            \r" );
	Translate( 0x0098E3FC, "Dura��o:             \r" );
	Translate( 0x004F757A, "%%d segundos\r" );
	Translate( 0x0098E410, " segundos" );
	Translate( 0x0098E400, "Mana:                \r" );
	Translate( 0x0098E45C, "Estamina:            \r" );
	Translate( 0x0098E404, "Ataque:              \r" );
	Translate( 0x0098E408, "Alcance:             \r" );
	Translate( 0x004F6F0A, "(%%s, %%s - %%d%%s %%s" );
	Translate( 0x0098E5D0, "Ataque B�nus)\r" );
	Translate( 0x0098E3DC, "Res. a Veneno:       \r" );
	Translate( 0x0098E40C, "Absor��o:            \r" );
	Translate( 0x0098E450, "Precis�o:            \r" );
	Translate( 0x0098E538, "Ataque M�ximo:       \r" );
	Translate( 0x0098E3F0, "Ataque:              \r" );
	Translate( 0x0098E3EC, "Ataque M�ximo:       \r" );
	Translate( 0x0098E3F4, "Vel. da Arma:        \r" );
	Translate( 0x0098E3E4, "�rea:                \r" );
	Translate( 0x004F799D, "%%d-%%d+(NV)\r" );
	Translate( 0x004F6ED8, "(%%s - %%d%%s %%s" );
	Translate( 0x004F7043, "(%%s - %%d%%s %%s" );
	Translate( 0x004F718F, "(%%s - %%d%%s %%s" );
	Translate( 0x0098E668, "Defesa:              \r" );
	Translate( 0x0098E71C, ")\r" );
	Translate( 0x0098E724, "Absor��o F�sica" );
	Translate( 0x004F6FBF, "(%%s %%d%%s%%s" );
	Translate( 0x004F7129, "(%%s %%d%%s%%s" );
	Translate( 0x004F71BA, "(%%s %%d%%s%%s" );
	Translate( 0x004F7277, "(%%s %%d%%s%%s" );
	Translate( 0x0098E7C0, "Dano Refletido:      \r" );
	Translate( 0x0098E5F4, "Defesa:              \r" );
	Translate( 0x0098E680, "Ataque:              \r" );
	Translate( 0x0098E520, "Alcance:             \r" );
	Translate( 0x0098E684, "N�mero de Ataques:   \r" );
	Translate( 0x0098E688, "Absor��o:            \r" );
	Translate( 0x0098E68C, "�rea:                \r" );
	Translate( 0x0098E690, "Ataque:              \r" );
	Translate( 0x0098E408, "Alcance:             \r" );
	Translate( 0x0098E65C, "Intervalo de Ataque: \r" );
	Translate( 0x0098ECDC, "Tipo de Ataque:      \r" );
	Translate( 0x0098ECE4, "Autom�tico\r" );
	Translate( 0x0098ECE0, "Manual\r" );
	Translate( 0x0098E6C0, "Precis�o:            \r" );
	Translate( 0x0098E694, "Vida:                \r" );
	Translate( 0x0098E6C4, "Defesa:              \r" );
	Translate( 0x0098E514, "Alcance:             \r" );
	Translate( 0x0098E3E0, "Res. a Fogo:         \r" );
	Translate( 0x0098E41C, "N�mero de Ataques:   \r" );
	Translate( 0x0098E420, "Redu��o de Vida:     \r" );
	Translate( 0x0098E424, "Precis�o:            \r" );
	Translate( 0x0098E428, "Cr�tico:             \r" );
	Translate( 0x0098E4D8, "�rea:                \r" );
	Translate( 0x0098E430, "Dano por Fogo:       \r" );
	Translate( 0x0098E730, "Precis�o:            \r" );
	Translate( 0x0098E72C, "Girada Brutal - Cr�tico" );
	Translate( 0x0098E4E8, "Precis�o:            \r" );
	Translate( 0x0098E5F8, "B�nus vs Dem�nio:    \r" );
	Translate( 0x0098E418, "Ataque:              \r" );
	Translate( 0x0098E698, "Absor��o:            \r" );
	Translate( 0x0098E69C, "B�nus de Ataque:     \r" );
	Translate( 0x0098E6A0, "N�mero de Ataques:   \r" );
	Translate( 0x0098E6A4, "Vida:                \r" );

	//Translate( 0x00, "" );
};

void CSkillTranslate::SetTexts( )
{
	Name( "Escudo Extremo" );
	Description( " Aumenta o Bloqueio do Escudo  temporariamente" );
	Name( "Bomba Mec�nica" );
	Description( "Joga uma bomba que explode nos inimigos ao redor" );
	Name( "Resist�ncia a Veneno" );
	Description( "Aumenta a Resist�ncia a Veneno permanentemente" );
	Name( "Absor��o F�sica" );
	Description( "        Aumenta a Absor��o     temporariamente" );
	Name( "Golpe Grande" );
	Description( " Carrega e desfere um poderoso golpe nos inimigos ao redor" );
	Name( "Maximizar" );
	Description( "Aumenta temporariamente o Poder    de Ataque M�ximo da Arma   equipada" );
	Name( "Automa��o" );
	Description( "  Aperfei�oa o uso de Lan�as e   Arcos, aumentando o Poder de Ataque e a Velocidade do Ataquetemporariamente" );
	Name( "Spark" );
	Description( "   Cria uma esfera de energia       concentrada e lan�a nos   inimigos" );
	Name( "Armadura Met�lica" );
	Description( "    Aumenta temporariamente a   Defesa se a armadura equipada possuir Spec Mec�nico" );
	Name( "Golpe Grandioso" );
	Description( "      Ataca o inimigo com dois  poderosos ataques com Taxa de       Ataque e Poder de Ataque adicionais" );
	Name( "Mestre das Armas Mec�nicas" );
	Description( "Aumenta permanentemente o Poder      de Ataque das armas que  possu�rem Spec Mec�nico" );
	Name( "Escudo Spark" );
	Description( " Cria um escudo de energia que      enviar� todos os ataques     bloqueados de volta para o  inimigo" );
	Name( "Impulso" );
	Description( "Cria um corrente de sparks que      atacar� v�rios inimigos aomesmo tempo" );
	Name( "Implos�o" );
	Description( " Cria um campo magn�tico que       atrai os inimigos ao redor       e aumenta a Absor��o     temporariamente" );
	Name( "Esferas Magn�ticas" );
	Description( " Cria 3 esferas magn�ticas que     atacar�o os inimigos mais  pr�ximos" );
	Name( "Golem de Metal" );
	Description( " Cria um Golem de Metal gigante      que ajudar� atacando os  inimigos" );
	Name( "T5_1_MS" );
	Description( "T5_1_MS" );
	Name( "T5_2_MS" );
	Description( "T5_2_MS" );
	Name( "T5_3_MS" );
	Description( "T5_3_MS" );
	Name( "T5_4_MS" );
	Description( "T5_4_MS" );
	Name( "Mestre das Armas" );
	Description( "    Aumenta o Poder de Ataque  permanentemente" );
	Name( "Resist�ncia a Fogo" );
	Description( "  Aumenta a Resist�ncia a Fogo permanentemente" );
	Name( "Raiva" );
	Description( "Ataca v�rias vezes com Poder de Ataque adicional, por�m perde parte da pr�pria Vida" );
	Name( "Impacto" );
	Description( "Aumenta o Poder de Ataque e a  Taxa de Ataque para derrubar o inimigo" );
	Name( "Impacto Triplo" );
	Description( "    Uma vers�o mais forte do   Impacto" );
	Name( "Girada Brutal" );
	Description( "Desfere um forte e fatal ataqueno oponente" );
	Name( "Rugido" );
	Description( "  Libera um grande rugido para       atordoar e confundir os  inimigos temporariamente" );
	Name( "F�ria de Zecram" );
	Description( "Ataca utilizando as habilidadesdo lend�rio her�i Zecram" );
	Name( "Concentra��o" );
	Description( "    Aumenta a Taxa de Ataque   temporariamente" );
	Name( "Golpe da Vingan�a" );
	Description( "   Vinga-se do inimigo com um  ataque poderoso" );
	Name( "Machado Veloz" );
	Description( "Aumenta a Velocidade do Machadotemporariamente" );
	Name( "Quebra Ossos" );
	Description( "   Derruba o oponente com um   poderoso ataque" );
	Name( "Destroyer" );
	Description( " Acerta o inimigo 3 vezes com opoder de um Destroyer" );
	Name( "F�ria" );
	Description( "   Aumenta o Poder de Ataque   sacrificando parte da Absor��o" );
	Name( "Golpe Girat�rio" );
	Description( "    Cria um ciclone para abaterv�rios inimigos ao mesmo tempo" );
	Name( "B�nus de Vida" );
	Description( "Aumenta a Vida permanentemente" );
	Name( "T5_1_FS" );
	Description( "T5_1_FS" );
	Name( "T5_2_FS" );
	Description( "T5_2_FS" );
	Name( "T5_3_FS" );
	Description( "T5_3_FS" );
	Name( "T5_4_FS" );
	Description( "T5_4_FS" );
	Name( "Sopro Afiado" );
	Description( "Cria um vento circular com sua foice, afastando os inimigos" );
	Name( "Resist�ncia a Gelo" );
	Description( "  Aumenta a Resist�ncia a Gelo permanentemente" );
	Name( "Ataque Cr�tico" );
	Description( "    Acerta os pontos fracos do inimigo causando danos cr�ticos" );
	Name( "Pulo Fatal" );
	Description( "  Com um salto, ataca com um   golpe concentrado" );
	Name( "Espinhos de Gelo" );
	Description( "     Enfia a foice no ch�o para         congelar e paralisar   temporariamente os inimigos ao redor" );
	Name( "Tornado" );
	Description( " Gira a foice como um tornado,   acertando v�rios inimigos ao mesmo tempo" );
	Name( "Mestre da Defesa" );
	Description( "         Aumenta o Bloqueio    permanentemente, quando estiverusando armas de duas m�os" );
	Name( "Expans�o" );
	Description( "Aumenta o tamanho da arma para atacar com mais Poder de Ataque" );
	Name( "Lan�as Venenosas" );
	Description( "     Enfia a foice no ch�o para  envenenar temporariamente os inimigos ao redor" );
	Name( "Desaparecer" );
	Description( "Desaparece temporariamente" );
	Name( "Mestre do Cr�tico" );
	Description( "           Aumenta o Cr�tico   permanentemente" );
	Name( "Foice de A�o" );
	Description( "Salta e ataca o oponente com umcombo triplo" );
	Name( "Olho Assassino" );
	Description( "Torna o inimigo mais vulner�vela ataques cr�ticos" );
	Name( "Golpe Carregado" );
	Description( "Concentra-se para desferir um  golpe triplo letal" );
	Name( "Furtivo" );
	Description( "         Aumenta a Esquiva     temporariamente" );
	Name( "Mestre das Sombras" );
	Description( "Com o poder das sombra, ataca  o inimigo v�rias vezes" );
	Name( "T5_1_PS" );
	Description( "T5_1_PS" );
	Name( "T5_2_PS" );
	Description( "T5_2_PS" );
	Name( "T5_3_PS" );
	Description( "T5_3_PS" );
	Name( "T5_4_PS" );
	Description( "T5_4_PS" );
	Name( "Falc�o Vigia" );
	Description( " Invoca um Falc�o para vigiar a   �rea e aumentar a Taxa de   Ataque temporariamente" );
	Name( "Mestra do Tiro" );
	Description( "   Aumenta o Poder de Ataque   permanentemente" );
	Name( "Flecha de Vento" );
	Description( "Dispara uma flecha de vento commais Velocidade" );
	Name( "Mira Perfeita" );
	Description( "   Atira uma flecha perfeita no    alvo, com Taxa de Ataque   adicional" );
	Name( "Olho de Dion" );
	Description( " Treina a pontaria aumentando aTaxa de Ataque permanentemente" );
	Name( "Falc�o" );
	Description( "Invoca um Falc�o para ajudar a atacar o inimigo" );
	Name( "Flecha da F�ria" );
	Description( "    Lan�a no ar uma rajada de  flechas que explode e acerta osinimigos ao redor" );
	Name( "Avalanche" );
	Description( "Atira uma sequ�ncia de flechas perfurantes no inimigo" );
	Name( "Tiro Elemental" );
	Description( "Dispara um tiro de fogo ou raiocausando dano nos inimigos ao  redor" );
	Name( "Falc�o Dourado" );
	Description( "Invoca um Falc�o Dourado para      ajudar a atacar o inimigo e  aumentar sua Regenera��o de  Vida temporariamente" );
	Name( "Tiro Explosivo" );
	Description( "  Atira duas flechas explosivas causando dano nos inimigos ao  edor" );
	Name( "Perfura��o" );
	Description( "    Atira uma flecha precisa e poderosa que atravessa todos osinimigos no alcance do ataque" );
	Name( "Wolverine" );
	Description( "Invoca um Wolverine para ajudara atacar o inimigo" );
	Name( "Mestra da Esquiva" );
	Description( "         Aumenta a Esquiva     permanentemente" );
	Name( "Tiro F�nix" );
	Description( "Atira uma flecha encantada com as penas da lend�ria F�nix" );
	Name( "For�a da Natureza" );
	Description( " Aumenta seu Poder de Ataque e  Taxa de Ataque usando a For�a da Natureza" );
	Name( "T5_1_AS" );
	Description( "T5_1_AS" );
	Name( "T5_2_AS" );
	Description( "T5_2_AS" );
	Name( "T5_3_AS" );
	Description( "T5_3_AS" );
	Name( "T5_4_AS" );
	Description( "T5_4_AS" );
	Name( "Rajada Sagrada" );
	Description( "Carrega sua espada com a for�a   divina e lan�a uma rajada nosoponentes" );
	Name( "Corpo Sagrado" );
	Description( "Recebe uma energia sagrada para    aumentar a Absor��o contra          monstros Morto-Vivo   temporariamente" );
	Name( "Treinamento F�sico" );
	Description( " Treina o corpo para aumentar aEstamina permanentemente" );
	Name( "Golpe Duplo" );
	Description( " Um ataque duplo, veloz e letalcom altas chances de Cr�tico" );
	Name( "Valor Sagrado" );
	Description( "Aumenta temporariamente o Poder     de Ataque do grupo contra monstros Morto-Vivo" );
	Name( "Brandish" );
	Description( "    Com um salto, corta o ch�o causando dano em �rea" );
	Name( "Piercing" );
	Description( " Carrega sua espada desferindo     um golpe que atravessa os  inimigos no alcance do ataque" );
	Name( "Esp�rito Dr�stico" );
	Description( "      Concentra o esp�rito do      Cavaleiro para aumentar a  Defesa temporariamente" );
	Name( "Mestre da Espada" );
	Description( "  Treina o uso de Espadas para    aumentar o Poder de Ataque  permanentemente" );
	Name( "Escudo Divino" );
	Description( "         Aumenta o Bloqueio        temporariamente e converte ataques bloqueados de monstros  Morto-Vivo em Vida" );
	Name( "Encantamento Sagrado" );
	Description( "       Lan�a um feiti�o para    escravizar monstros Morto-Vivo       para ajudar na batalha  temporariamente" );
	Name( "Grande Cruzada" );
	Description( "Uma cruzada sagrada poderosa,  veloz e cont�nua" );
	Name( "Piercing Divino" );
	Description( "     Utilizando a for�a divina, desfere uma sequ�ncia letal degolpes no inimigo" );
	Name( "Escudo dos Deuses" );
	Description( "    Usa o Escudo dos Deuses,        aumentando a Absor��o     temporariamente" );
	Name( "B�n��o Divina" );
	Description( " Com o poder da B�n��o Divina  dos Deuses, aumenta o Poder de Ataque temporariamente" );
	Name( "Espada Justiceira" );
	Description( "   Ataca o ch�o com a espada       criando uma onda de fogo        sagrado para destruir os  inimigos" );
	Name( "T5_1_KS" );
	Description( "T5_1_KS" );
	Name( "T5_2_KS" );
	Description( "T5_2_KS" );
	Name( "T5_3_KS" );
	Description( "T5_3_KS" );
	Name( "T5_4_KS" );
	Description( "T5_4_KS" );
	Name( "Golpe do Escudo" );
	Description( "Ataca o inimigo com o escudo" );
	Name( "Farina" );
	Description( "       Atira a lan�a com mais  Velocidade e Taxa de Ataque" );
	Name( "Mestra do Arremesso" );
	Description( "  Aumenta a profici�ncia no usoda lan�a, aumentando o Poder deAtaque permanentemente" );
	Name( "Lan�a Gigante" );
	Description( "   Atira no inimigo uma lan�a  gigante" );
	Name( "Windy" );
	Description( "Adiciona a propriedade do vento para aumentar a Taxa de Ataque       e o Alcance do Ataque   temporariamente" );
	Name( "Lan�a Girat�ria" );
	Description( " Atira uma lan�a girat�ria paraderrubar os inimigos" );
	Name( "Ladr�o de Almas" );
	Description( "Usa o escudo para absorver Vidados inimigos" );
	Name( "Lan�a de Fogo" );
	Description( "   Atira uma lan�a de fogo paraqueimar o oponente" );
	Name( "Lan�a Partida" );
	Description( "    Atira uma lan�a no ar que     separa em v�rias caindo e   atingindo o alvo em cheio" );
	Name( "Triunfo de Valhala" );
	Description( "   Com os poderes de Valhala,     aumenta o Poder de Ataque   M�ximo temporariamente" );
	Name( "Lan�a de Raios" );
	Description( "       Atira uma lan�a com     propriedades de raio" );
	Name( "Chuva de Lan�as" );
	Description( "       Arremessa duas lan�as    devastadoras criando uma chuvaque destr�i tudo em seu caminho" );
	Name( "Inferno de Valhala" );
	Description( "         Aumenta a Esquiva     temporariamente, al�m de ativar     os efeitos do Triunfo de  Valhala" );
	Name( "F�ria X" );
	Description( "   Pula no ar e atira 3 lan�as  explosivas, atingindo todos osinimigos ao redor do ataque" );
	Name( "Lan�a de Gelo" );
	Description( "  Encanta todas as lan�as com  propriedades do gelo, reduzindoa Velocidade dos inimigos" );
	Name( "Vingan�a" );
	Description( "Arremessa duas lan�as com muitafor�a, decapitando o alvo" );
	Name( "T5_1_ATS" );
	Description( "T5_1_ATS" );
	Name( "T5_2_ATS" );
	Description( "T5_2_ATS" );
	Name( "T5_3_ATS" );
	Description( "T5_3_ATS" );
	Name( "T5_4_ATS" );
	Description( "T5_4_ATS" );
	Name( "Cura" );
	Description( "  Com o poder divino, recupera sua Vida ou de seu aliado" );
	Name( "Fagulha Sagrada" );
	Description( "Atira uma fagulha com energia  divina para desintegrar o alvo" );
	Name( "Espinhos M�ltiplos" );
	Description( "   Dispara um ataque m�ltiplo econcentrado em um �nico alvo" );
	Name( "Feiti�o Divino" );
	Description( " Encanta o inimigo, reduzindo o       Poder de Ataque dele    temporariamente" );
	Name( "Medita��o" );
	Description( "Com poderes sagrados, aumenta a        Regenera��o de Mana    permanentemente" );
	Name( "Raios Divinos" );
	Description( "     Invoca uma chuva de raios     divinos para atingir v�riosinimigos ao mesmo tempo" );
	Name( "Reflex�o Divina" );
	Description( "Cria um escudo para refletir osataques dos monstros Morto-Vivo" );
	Name( "Cura M�xima" );
	Description( "Recupera parte da Vida de todos os membros do grupo dentro do alcance" );
	Name( "Esferas de Vigor" );
	Description( "Dispara duas esferas luminosas e letais contra o oponente" );
	Name( "Ressurei��o" );
	Description( "  Com poderes sagrados, tenta    trazer um membro do grupo de volta � Vida" );
	Name( "Extin��o" );
	Description( " Lan�a um feiti�o para reduzir    parte da Vida de monstros   Morto-Vivo" );
	Name( "Vida Virtual" );
	Description( "Aumenta a Vida temporariamente" );
	Name( "Espinhos Glaciais" );
	Description( "     L�minas afiadas de gelo     projetam do ch�o atacando e  congelando os inimigos" );
	Name( "Campo de Regenera��o" );
	Description( " Cria um campo para aumentar a  Regenera��o de Vida e Mana de todos dentro do alcance" );
	Name( "Raios Cont�nuos" );
	Description( "   Cria uma corrente de ataques      el�tricos atacando v�riosinimigos ao mesmo tempo" );
	Name( "Muspell" );
	Description( "  Invoca um anjo celestial para     atacar e proteger contra  monstros Morto-Vivo" );
	Name( "T5_1_PRS" );
	Description( "T5_1_PRS" );
	Name( "T5_2_PRS" );
	Description( "T5_2_PRS" );
	Name( "T5_3_PRS" );
	Description( "T5_3_PRS" );
	Name( "T5_4_PRS" );
	Description( "T5_4_PRS" );
	Name( "Agonia" );
	Description( "Sacrifica parte da pr�pria Vidapara recuperar parte da Mana" );
	Name( "Fagulha" );
	Description( "Dispara uma pequena fagulha de fogo para ferir o inimigo" );
	Name( "Zenith" );
	Description( " Aumenta temporariamente as      Resist�ncias para todos os   tipos de elementos" );
	Name( "Bola de Fogo" );
	Description( "Lan�a uma bola de fogo gigante para abater o alvo" );
	Name( "Mestre da Mente" );
	Description( "Aumenta a Mana permanentemente" );
	Name( "Tornado de �gua" );
	Description( "   Cria um poderoso tornado de �gua que explode nos inimigos" );
	Name( "Encanto" );
	Description( " Encanta a arma com fogo, gelo, ou raio, aumentando o Poder deAtaque termporariamente" );
	Name( "Raio da Morte" );
	Description( "    Atira um poderoso raio de  energia pura para desintegrar oalvo" );
	Name( "Escudo Energ�tico" );
	Description( " Cria um escudo de energia que  absorve temporariamente parte        dos ataques recebidos   consumindo Mana" );
	Name( "Terremoto" );
	Description( " Cria um terremoto devastador,  atingindo todos os inimigos aoredor" );
	Name( "Esp�rito Elemental" );
	Description( "       Invoca um esp�rito para    aumentar o Poder de Ataque  temporariamente" );
	Name( "Espada Dan�ante" );
	Description( "Invoca uma espada m�gica para  atacar os inimigos ao redor compoderes de fogo ou gelo" );
	Name( "Chama Elemental" );
	Description( "    Invoca o poderoso Chama       Elemental para ajudar nas   batalhas" );
	Name( "Onda de Fogo" );
	Description( "Cria uma onda de fogo gigante, atingindo todos os inimigos na �rea do ataque" );
	Name( "Distor��o" );
	Description( "  Gera um pulso de energia que  reduz temporariamente o Poder   de Ataque e a Velocidade do   Ataque dos oponentes ao redor" );
	Name( "Meteoro" );
	Description( "Convoca uma chuva de meteoros  que caem do c�u, atingindo todosos inimigos em volta" );
	Name( "T5_1_MGS" );
	Description( "T5_1_MGS" );
	Name( "T5_2_MGS" );
	Description( "T5_2_MGS" );
	Name( "T5_3_MGS" );
	Description( "T5_3_MGS" );
	Name( "T5_4_MGS" );
	Description( "T5_4_MGS" );
};

void __cdecl _SetTexts( )
{
	std::shared_ptr<CTranslate> lpTrans = std::make_shared<CTranslate>( );
	lpTrans->SetTexts( );
};