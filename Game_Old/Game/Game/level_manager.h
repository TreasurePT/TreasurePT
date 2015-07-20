#pragma once
#include <vector>
class CLevelManager
{
public:
	struct s_AddExp
	{
		int Size;
		int OpCode;
		int64 Experience;
		int Members;
		int CheckSum;
		int PlayerSerial;
	};
	void ReadLevels( int Cap, float Multiplier, int BaseExp );
	void WriteLevels( );
	int CheckLevelExp( int Level, int64 Exp );
	int GetLevelFromExp( int64 Exp );
	int AddExperience( int64 Exp );
	int AddExpSystem( int Packet );
private:
	static std::vector<int64> m_Level;
	int64 m_Aux;
};