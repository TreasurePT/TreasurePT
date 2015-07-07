#pragma once
#include <vector>

class CLevelManager
{
public:
	int CheckExpGained( int Exp, int Player );
	void ReadLevels( );
	void WriteLevels( );
private:
	static std::vector<__int64> m_Level;
	char m_Level_Buffer[ 256 ];
	int m_Level_Size;
};