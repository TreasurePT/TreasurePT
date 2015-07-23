#pragma once

class LevelManager
{
public:
	void Fill( );
	void AllocMemory( );
	void WriteTable( );
private:
	static std::vector<INT64> Level;
	static void* LevelData;
};