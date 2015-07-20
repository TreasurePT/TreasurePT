#pragma once
#include <vector>

class CLevelManager
{
private:
	struct s_AddExp
	{
		int Size;
		int OpCode;
		int64 Experience;
		int Members;
		int CheckSum;
		int PlayerSerial;
	};
	struct s_Player
	{
		DWORD Serial;
		DWORD PositionX;
		DWORD PositionZ;
	};
public:
	int CheckPlayerLevel( int Player );
	int GetLevelFromExp( int64 Exp );
	int CheckLevelExp( int Level, int64 Exp );
	int CheckExpGained( int Exp, int Player );
	int GetTotalExp( int Exp, int Level );
	void GetSoloExp( int MonsterInfo, int CharInfo );
	void GetPartyExp( int MonsterInfo, int PartyInfo );
	bool GetDistance( s_Player* Killer, s_Player* Player );
	void ReadLevels( );
	void WriteLevels( );
private:
	static std::vector<int64> m_Level;
	int64 m_Aux;
	int m_Level_Size;
};