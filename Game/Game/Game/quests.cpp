#include "stdafx.h"
#include "quests.h"
#include <d3dtypes.h>

const char* QuestPath = "game\\quests\\UI";

void CQuests::SetQuestPath( const char* SinName )
{
	StringCbPrintfA( m_QuestPath, 512, "%s\\%s", QuestPath, SinName );
};

void CQuests::ShowQuestInfo( DWORD QuestState )
{
	switch( QuestState )
	{
		case 0:
			//Iniciar o desafio.
			//UI::ShowHelp( Quest::Teste, QuestBox.x, QuestBox.y, QuestDim.x, QuestDim.y,
			//			  RGBA_MAKE( 0, 15, 128, 125 ), m_QuestPath );
			break;
		case 1:
			//Desafio em andamento.
			break;
		case 2:
			//Terminou o desafio.
			break;
	};
};

void CQuests::QuestManager( DWORD NpcCode )
{
	static s_Quest Quest[ 10 ] = { 0 };
	switch( NpcCode )
	{
		case 1:
			if( HasActiveQuest( ActiveQuestPointer ) )
			{
			};
			//TODO: Checar nível
			//TODO: Checar se já foi feito o desafio
			//TODO: Checar se tem desafio em andamento
			//TODO: Criar um novo código de desafios ( 0x2015 + )
			//TODO: Mostrar as informações
			//TODO: Ativar andamento
			//Quest[ 0 ].ID = 0x2015;
			//Quest[ 0 ].State = 0;
			break;
	};
};