#include "stdafx.h"
#include "level_manager.h"

int CLevelManager::CheckExpGained( int Exp, CPlayerInfo* Player )
{
	if( Player->GetPrivilege( ) == 4 )
		return true;

	if( Player->GetLevel( ) <= 10 )
	{
		//TODO: Estabelecer comparação com a EXP.
		// return true = permitir exp, return false = negar exp ( banir );

	};

	return true;
};

int __cdecl _CheckExpGained( int Exp, CPlayerInfo* Player )
{
	std::shared_ptr<CLevelManager> lpLv = std::make_shared<CLevelManager>( );
	Player->SetAddress( ( int )Player );
	return lpLv->CheckExpGained( Exp, Player );
};