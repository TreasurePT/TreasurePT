#pragma once
#include <vector>

class CLevelManager
{
public:
	int CheckPlayerLevel( int Player );
	int GetLevelFromExp( int64 Exp );
	int CheckLevelExp( int Level, int64 Exp );
	int CheckExpGained( int Exp, int Player );
	int GetTotalExp( int Exp, int Level );
	void GetSoloExp( int MonsterInfo, int CharInfo, int Player );
	void ReadLevels( );
	void WriteLevels( );
private:
	static std::vector<int64> m_Level;
	int64 m_Aux;
	int m_Level_Size;
};