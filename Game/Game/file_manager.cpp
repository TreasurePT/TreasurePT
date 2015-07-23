#include "stdafx.h"
#include "file_manager.h"


FileManager::FileManager( )
{
	SecureZeroMemory( &File, sizeof( s_File ) );
};

FileManager::FileManager( const char* FileName )
{
	SecureZeroMemory( &File, sizeof( s_File ) );
	SetName( FileName );
};

void FileManager::SetName( const char* FileName )
{
	StringCbCopyA( File.Name, 256, FileName );
	GetCurrentDirectoryA( 512, File.Directory );
	StringCbPrintfA( File.FullPath, 512 + 256, "%s\\%s", File.Directory, File.Name );
};

int FileManager::ReadInt( const char* Section, const char* Key )
{
	char Buffer[ 256 ] = { 0 };
	GetPrivateProfileStringA( Section, Key, 0, Buffer, sizeof( Buffer ), File.FullPath );
	return atoi( Buffer );
};

void FileManager::ReadString( const char* Section, const char* Key, char* Buffer )
{
	GetPrivateProfileStringA( Section, Key, 0, Buffer, 256, File.FullPath );
};

bool FileManager::FileExists( )
{
	FILE* FileExists = nullptr;
	fopen_s( &FileExists, File.FullPath, "r" );
	if( FileExists )
	{
		fclose( FileExists );
		return true;
	};
	return false;
};

void FileManager::Write( const char* Section, const char* Key, const char* String )
{
	WritePrivateProfileStringA( Section, Key, String, File.FullPath );
};