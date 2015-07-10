#include "stdafx.h"
#include "quests.h"

void CQuests::Teste( DWORD MonsterCode )
{
	typedef void( __cdecl* t_AddChatMsg )( LPCSTR, INT );
	t_AddChatMsg AddChatMsg = ( t_AddChatMsg )0x0062DEB0;

	AddChatMsg( Format( "> Você matou o monstro com código: %d.", MonsterCode ), 9 );
};