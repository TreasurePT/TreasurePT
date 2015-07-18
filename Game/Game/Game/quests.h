#pragma once
#include "UI_templates.h"

#define ActiveQuestPointer ( int* )0x035F38E8


class CQuests : public CUITemplates
{
private:
	typedef int( __thiscall* t_HasActiveQuest )( int* ClassPointer );
	t_HasActiveQuest HasActiveQuest = ( t_HasActiveQuest )0x00490290;
	typedef int( __cdecl* t_CheckActiveQuest )( int QuestID );
	t_CheckActiveQuest CheckActiveQuest = ( t_CheckActiveQuest )0x004E0F90;
	struct s_Quest
	{
		int Code;
		int State;
	};
	//POINT QuestBox = { 50, 45 };
	//POINT QuestDim = { 9, 10 };
public:
	CQuests( ) { Clear( m_QuestPath, 512 ); };
	typedef CUITemplates UI;
	void SetQuestPath( const char* SinName );
	void ShowQuestInfo( DWORD QuestState );
	void QuestManager( DWORD NpcCode );
private:
	enum Quest
	{

	};
	enum Npc
	{

	};
	enum Monster
	{
		Coelho = 42,
		Hopi = 41,
		Duende_Macabro = 44,
		Duende_Selvagem = 43,
		Esqueleto = 46,
		Esqueleto_do_Mal = 45,
		Cíclope = 47,
		Bargon = 1,
		Besouro_Blindado = 4,
		Patrulheiro_do_Mal = 5,
		Titã = 6,
		Decapitador = 3,
		Guerreiro_do_Mal = 2,
		Múmia = 19,
		Cavaleiro_do_Mal = 16,
		Figon = 21,
		Cavaleiro_Fantasma = 28,
		Centauro_L = 26,
		Abelha_Selvagem = 8,
		Gigante_de_Pedra = 22,
		Caramujo_Rijo = 17,
		Muffin = 7,
		Abelha_do_Mal = 27,
		Caramujo_Espinhoso = 18,
		Bruxa = 30,
		Pesadelo = 29,
		Duende_Guerreiro = 31,
		Guardião_Maldito = 20,
		Golem_de_Pedra = 23,
		Lorde_Centauro = 38,
		Dawlin = 32,
		Dusk = 39,
		Stygian = 33,
		Espectro_Negro = 36,
		Incubus = 34,
		Ratoo = 10,
		Tiphoon = 9,
		Golem_de_Aço = 35,
		Ogro_Mecânico = 40,
		Guardião_de_Aço = 24,
		Centauro_Arqueira = 25,
		Metron = 37,
		Grotesco = 11,
		Montanha = 15,
		Máquina_D = 14,
		Omega = 13,
		Punhos_de_Aço = 12
	};
	char m_QuestPath[ 512 ];
};