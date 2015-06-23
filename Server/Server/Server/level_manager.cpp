#include "stdafx.h"
#include "level_manager.h"

long CLevelManager::CheckExpGained( long Exp, long Player )
{
	m_Player_GmLevel = *( long* )( Player + 0x6E1C );
	m_Player_Level = *( long* )( Player + 0xC8 );

	if( m_Player_GmLevel == 4 )
		return true;

	if( m_Player_Level <= 10 )
	{
		//TODO: Estabelecer comparação com a EXP.
		// return true = permitir exp, return false = negar exp ( banir );

	};

	return true;
};

long __cdecl _CheckExpGained( long Exp, long Player )
{
	std::shared_ptr<CLevelManager> lpLv = std::make_shared<CLevelManager>( );
	return lpLv->CheckExpGained( Exp, Player );
};