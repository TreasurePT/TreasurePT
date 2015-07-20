#include "stdafx.h"
#include "file_manager.h"

CFileManager::CFileManager( const char* FileName )
{
	StringCbCopyA( File.Name, 256, FileName );
	GetCurrentDirectoryA( 512, File.Directory );
	StringCbPrintfA( File.FullPath, 512 + 256, "%s\\%s", File.Directory, File.Name );
}

void CFileManager::GetString( const char* Section, const char* Key, char* Buffer )
{
	GetPrivateProfileStringA( Section, Key, 0, Buffer, 256, File.FullPath );
};

void CFileManager::SetString( const char* Section, const char* Key, const char* String )
{
	WritePrivateProfileStringA( Section, Key, String, File.FullPath );
};