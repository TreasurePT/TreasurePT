#pragma once
#include <vector>
class CLevelManager
{
public:
	void ReadLevels( int Cap, float Multiplier, int BaseExp );
	void WriteLevels( );
	int CheckLevelExp( int Level, int64 Exp );
	int GetLevelFromExp( int64 Exp );
	int AddExp( int64 Exp );

private:
	static std::vector<int64> m_Level;
	int64 m_Aux;
};