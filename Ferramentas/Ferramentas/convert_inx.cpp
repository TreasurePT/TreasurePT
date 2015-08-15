#include "stdafx.h"
#include "convert_inx.h"

FILE* lpDbg = nullptr;

const char* ConvertInx::GetName( const char* FullPath )
{
	static char Name[ 512 ] = { 0 };
	StringCbCopyA( Name, 512, FullPath );

	for( int i = sizeof( Name ); i >= 0; i-- )
	{
		if( Name[ i ] == '.' )
		{
			SecureZeroMemory( &Name[ i ], sizeof( Name ) - i );
			break;
		};
	};

	return Name;
};

void ConvertInx::Convert( s_Inx* InxFile )
{
	FILE* oldInx = nullptr;
	FILE* bakInx = nullptr;
	FILE* newInx = nullptr;

	INT oldAddress = 0;
	INT newAddress = 0;

	fopen_s( &oldInx, InxFile->FullPath, "rb" );
	fopen_s( &bakInx, Format( "%s.bak", GetName( InxFile->FullPath ) ), "wb+" );

	if( !oldInx )
	{
		fclose( bakInx );
		fprintf( lpDbg, "[ ERROR ] : %s\n", InxFile->FullPath );
		return;
	};

	char oldData[ OLD_INX_SIZE ] = { 0 };
	char newData[ NEW_INX_SIZE ] = { 0 };

	fread_s( &oldData, OLD_INX_SIZE, OLD_INX_SIZE, sizeof( char ), oldInx );
	fclose( oldInx );
	DeleteFileA( InxFile->FullPath );

	fwrite( oldData, OLD_INX_SIZE, sizeof( char ), bakInx );
	fclose( bakInx );

	fopen_s( &newInx, InxFile->FullPath, "wb+" );

	while( oldAddress < OLD_INX_SIZE )
	{
		switch( newAddress )
		{
			case 0x63C:		oldAddress = 0x844;		break;
			case 0x6A8:		oldAddress = 0x8E4;		break;
			case 0x720:		oldAddress = 0x990;		break;
			case 0x798:		oldAddress = 0xA3C;		break;
			case 0x814:		oldAddress = 0xAEC;		break;
			case 0x88C:		oldAddress = 0xB98;		break;
			case 0x904:		oldAddress = 0xC44;		break;
			case 0x97C:		oldAddress = 0xCF0;		break;
			case 0x9F4:		oldAddress = 0xD9C;		break;
			case 0xA6C:		oldAddress = 0xE48;		break;
			case 0xAE4:		oldAddress = 0xB18;		break;
			case 0xB5C:		oldAddress = 0xBC4;		break;
			case 0xBD4:		oldAddress = 0xC70;		break;
			case 0xF18C:	oldAddress = 0x1598C;	break;
			case 0x10068:	oldAddress = 0x16E80;	break;
		};
		newData[ newAddress ] = oldData[ oldAddress ];
		oldAddress++;
		newAddress++;
	};

	fwrite( newData, NEW_INX_SIZE, sizeof( char ), newInx );
	fclose( newInx );
	fprintf( lpDbg, "Convertido: %s\n", InxFile->FullPath );

};

void ConvertInx::ConvertMonster( const char* Directory )
{
	hDirectory = FindFirstFileA( Format( "%s\\char\\monster\\*", Directory ), &DirAttr );
	s_Inx InxFile = { 0 };
	while( true )
	{
		if( hDirectory != INVALID_HANDLE_VALUE )
		{
			if( DirAttr.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY )
				break;

			if( DirAttr.dwFileAttributes == FILE_ATTRIBUTE_HIDDEN )
				break;

			hFile = FindFirstFileA( Format( "%s\\char\\monster\\%s\\*.inx", Directory, DirAttr.cFileName ), &FileAttr );
			while( true )
			{
				if( FileAttr.cFileName[ lstrlenA( FileAttr.cFileName ) - 1 ] == 'x' )
				{
					if( FileAttr.nFileSizeLow == OLD_INX_SIZE )
					{
						StringCbCopyA( InxFile.FileName, 256, FileAttr.cFileName );
						StringCbCopyA( InxFile.FullPath, 512, Format( "%s\\char\\monster\\%s\\%s",
							Directory, DirAttr.cFileName, FileAttr.cFileName ) );
						Convert( &InxFile );
					};
				};

				if( FindNextFileA( hFile, &FileAttr ) == FALSE )
					break;
			};

			if( FindNextFileA( hDirectory, &DirAttr ) == FALSE )
			{
				break;
			};
		}
		else
		{
			break;
		};
	};
	hDirectory = NULL;
	hFile = NULL;
	SecureZeroMemory( &DirAttr, sizeof( WIN32_FIND_DATA ) );
	SecureZeroMemory( &FileAttr, sizeof( WIN32_FIND_DATA ) );
};

void ConvertInx::ConvertNpc( const char* Directory )
{
	hDirectory = FindFirstFileA( Format( "%s\\char\\npc\\*", Directory ), &DirAttr );
	s_Inx InxFile = { 0 };
	while( true )
	{
		if( hDirectory != INVALID_HANDLE_VALUE )
		{
			if( DirAttr.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY )
				break;

			if( DirAttr.dwFileAttributes == FILE_ATTRIBUTE_HIDDEN )
				break;

			hFile = FindFirstFileA( Format( "%s\\char\\npc\\%s\\*.inx", Directory, DirAttr.cFileName ), &FileAttr );
			while( true )
			{
				if( FileAttr.cFileName[ lstrlenA( FileAttr.cFileName ) - 1 ] == 'x' )
				{
					if( FileAttr.nFileSizeLow == OLD_INX_SIZE )
					{
						StringCbCopyA( InxFile.FileName, 256, FileAttr.cFileName );
						StringCbCopyA( InxFile.FullPath, 512, Format( "%s\\char\\npc\\%s\\%s",
							Directory, DirAttr.cFileName, FileAttr.cFileName ) );
						Convert( &InxFile );
					};
				};

				if( FindNextFileA( hFile, &FileAttr ) == FALSE )
					break;
			};

			if( FindNextFileA( hDirectory, &DirAttr ) == FALSE )
			{
				break;
			};
		}
		else
		{
			break;
		};
	};
	hDirectory = NULL;
	hFile = NULL;
	SecureZeroMemory( &DirAttr, sizeof( WIN32_FIND_DATA ) );
	SecureZeroMemory( &FileAttr, sizeof( WIN32_FIND_DATA ) );
};

ConvertInx::ConvertInx( )
{
	char Directory[ 512 ] = { 0 };
	GetCurrentDirectoryA( 512, Directory );
	DeleteFileA( "Logs.txt" );
	fopen_s( &lpDbg, "Logs.txt", "a" );
	ConvertMonster( Directory );
	ConvertNpc( Directory );
	fclose( lpDbg );
}