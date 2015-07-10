#pragma once
#include <vector>
class CLevelManager
{
public:
	struct s_AddExp
	{
		int size;
		int opCode;
		int64 exp;
		int members;
		int checksum;
		int player;
	};
	void ReadLevels( int Cap, float Multiplier, int BaseExp );
	void WriteLevels( );
	int CheckLevelExp( int Level, int64 Exp );
	int GetLevelFromExp( int64 Exp );
	int AddExperience( int64 Exp );
	void AddExpSystem( int Packet );
private:
	static std::vector<int64> m_Level;
	int64 m_Aux;
};