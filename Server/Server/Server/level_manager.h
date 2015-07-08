#pragma once
#include <vector>

class CLevelManager
{
public:
	int CheckPlayerLevel( int Player );
	int GetLevelFromExp( int64 Exp );
	int CheckLevelExp( int Level, int64 Exp );
	int CheckExpGained( int Exp, int Player );
	void ReadLevels( );
	void WriteLevels( );
private:
	static std::vector<int64> m_Level;
	char m_Level_Buffer[ 256 ];
	int m_Level_Size;
};