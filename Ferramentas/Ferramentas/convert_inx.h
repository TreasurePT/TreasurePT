#pragma once

class ConvertInx
{
private:
	struct s_Inx
	{
		char FullPath[ 512 ];
		char FileName[ 256 ];
	};
public:
	ConvertInx( );
	void ConvertMonster( const char* Directory );
	void ConvertNpc( const char* Directory );
	void Convert( s_Inx* InxFile );
private:
	WIN32_FIND_DATA DirAttr, FileAttr;
	HANDLE hFile, hDirectory;
};