#include "stdafx.h"
#include "wide_screen.h"
#include "file_manager.h"

CWideScreen::CWideScreen( )
{
	s_Config Config = { 0 };
	DefaultConfig( &Config );
	ReadConfig( &Config );
	if( CheckConfig( &Config ) )
	{
		SetConfig( &Config );
	}
	else
	{
		DefaultConfig( &Config, true );
		SetConfig( &Config );
		MessageBoxA( 0, "A configuração é inválida ou não foi possível encontrar o arquivo \"Game\\Game.ini\". Um novo arquivo foi criado.\n"
					 "Resolução: 800x600 - Modo Janela.\n"
					 "\n"
					 "Resoluções suportadas:\n"
					 "800x600 - 1024x768 - 1152x864\n"
					 "1280x720 - 1360x768 - 1400x1050\n"
					 "1600x1200 - 1920x1080.", "Treasure Priston Tale", MB_OK | MB_ICONEXCLAMATION );
	};
}

void CWideScreen::DefaultConfig( s_Config* Config, bool CreateIni )
{
	if( CreateIni )
	{
		std::shared_ptr<CFileManager> lpFile = std::make_shared<CFileManager>( "game\\game.ini" );
		DeleteFileA( "Game\\Game.ini" );
		lpFile->SetString( "Video", "Largura", "800" );
		lpFile->SetString( "Video", "Altura", "600" );
		lpFile->SetString( "Video", "Tela Cheia", "Desativada" );
		lpFile->SetString( "Video", "Graficos", "Muito Alto" );
		lpFile->SetString( "Video", "Profundidade das Cores", "32" );
		lpFile->SetString( "Usuario", "Camera Invertida", "Desativada" );
		lpFile->SetString( "Usuario", "Fog de Camera", "inte" );
		lpFile->SetString( "Usuario", "Som", "Ativado" );
		lpFile->SetString( "Servidor", "Protocolo Interno", "127.0.0.1" );
	};
	Config->Width = 800;
	Config->Height = 600;
	StringCbCopyA( Config->FullScreen, 16, "Desativada" );
	StringCbCopyA( Config->Graphics, 16, "Muito Alto" );
	Config->ColorDepth = 32;
	StringCbCopyA( Config->CammInvert, 32, "Desativada" );
	StringCbCopyA( Config->CammFog, 16, "inte" );
	StringCbCopyA( Config->Sound, 16, "Ativado" );
	StringCbCopyA( Config->InternalProtocal, 32, "127.0.0.1" );
	Config->isWide = false;
};

void CWideScreen::ReadConfig( s_Config* Config )
{
	std::shared_ptr<CFileManager> lpFile = std::make_shared<CFileManager>( "Game\\Game.ini" );
	char Buffer[ 256 ] = { 0 };
	lpFile->GetString( "Video", "Largura", Buffer );
	Config->Width = atoi( Buffer );
	lpFile->GetString( "Video", "Altura", Buffer );
	Config->Height = atoi( Buffer );
	lpFile->GetString( "Video", "Tela Cheia", Config->FullScreen );
	lpFile->GetString( "Video", "Graficos", Config->Graphics );
	lpFile->GetString( "Video", "Profundidade das Cores", Buffer );
	Config->ColorDepth = atoi( Buffer );
	lpFile->GetString( "Usuario", "Camera Invertida", Config->CammInvert );
	lpFile->GetString( "Usuario", "Fog de Camera", Config->CammFog );
	lpFile->GetString( "Usuario", "Som", Config->Sound );
	lpFile->GetString( "Servidor", "Protocolo Interno", Config->InternalProtocal );
};

bool CWideScreen::CheckConfig( s_Config* Config )
{
	SecureZeroMemory( &NewConfig, sizeof( s_NewConfig ) );

	struct s_Resolutions
	{
		int Width;
		int Height;
		bool isWide;
	};

	s_Resolutions Resolutions[ ] =
	{
		{ 800, 600, false },
		{ 1024, 768, false },
		{ 1152, 864, false },
		{ 1280, 720, true },
		{ 1360, 768, true },
		{ 1366, 768, true },
		{ 1400, 1050, false },
		{ 1600, 1200, false },
		{ 1920, 1080, true }
	};

	bool isValid = false;

	for( int i = 0; i < 9; i++ )
	{
		if( Config->Width == Resolutions[ i ].Width && Config->Height == Resolutions[ i ].Height )
		{
			if( Resolutions[ i ].isWide )
			{
				Config->isWide = true;
			};
			NewConfig.Width = Config->Width;
			NewConfig.Height = Config->Height;
			NewConfig.isWide = Config->isWide;
			isValid = true;
			break;
		};
	};

	if( !isValid )
		return false;

	if( lstrcmpiA( Config->FullScreen, "Ativada" ) == 0 )
	{
		NewConfig.FullScreen = ON;
	}
	else
	{
		NewConfig.FullScreen = OFF;
	};

	if( lstrcmpiA( Config->Graphics, "Baixo" ) == 0 )
	{
		NewConfig.Graphics = LOW;
	}
	else if( lstrcmpiA( Config->Graphics, "Médio" ) == 0 )
	{
		NewConfig.Graphics = MEDIUM;
	}
	else if( lstrcmpiA( Config->Graphics, "Alto" ) == 0 )
	{
		NewConfig.Graphics = HIGH;
	}
	else
	{
		NewConfig.Graphics = VERYHIGH;
	};

	if( Config->ColorDepth == 16 )
	{
		NewConfig.ColorDepth = 16;
	}
	else
	{
		NewConfig.ColorDepth = 32;
	};

	if( lstrcmpiA( Config->CammInvert, "Ativada" ) == 0 )
	{
		NewConfig.CammInvert = TRUE;
	}
	else
	{
		NewConfig.CammInvert = FALSE;
	};

	if( lstrcmpiA( Config->CammFog, "Perto" ) == 0 )
	{
		NewConfig.CammFog = _NEAR;
	}
	else
	{
		NewConfig.CammFog = _FAR;
	};

	if( lstrcmpiA( Config->Sound, "Desativado" ) == 0 )
	{
		NewConfig.Sound = OFF;
	}
	else
	{
		NewConfig.Sound = ON;
	};

	return true;

};

void CWideScreen::SetConfig( s_Config* Config )
{
	if( NewConfig.ColorDepth != 0 )
	{
		*( int* )( 0x00D0A550 ) = NewConfig.Graphics;
		if( NewConfig.ColorDepth == 16 )
			*( int* )( 0x00D0A54C ) = NewConfig.ColorDepth;
		*( int* )( 0x00A45590 ) = NewConfig.CammInvert;
		*( int* )( 0x00A45594 ) = NewConfig.CammFog;
		*( int* )( 0x00D0A544 ) = NewConfig.Width;
		*( int* )( 0x00D0A548 ) = NewConfig.Height;
		*( int* )( 0x00D0A554 ) = NewConfig.Sound;
		*( int* )( 0x00D0A540 ) = NewConfig.FullScreen;
		StringCbCopyA( ( char* )( 0x00D0C1D8 ), 32, Config->InternalProtocal );
		StringCbCopyA( ( char* )( 0x00D0C1B4 ), 32, Config->InternalProtocal );
		StringCbCopyA( ( char* )( 0x00D0C1FC ), 32, Config->InternalProtocal );
	}
	else
	{
		*( int* )( 0x00D0A550 ) = VERYHIGH;
		*( int* )( 0x00D0A54C ) = 0;
		*( int* )( 0x00A45590 ) = 0;
		*( int* )( 0x00A45594 ) = _FAR;
		*( int* )( 0x00D0A544 ) = 800;
		*( int* )( 0x00D0A548 ) = 600;
		*( int* )( 0x00D0A554 ) = ON;
		*( int* )( 0x00D0A540 ) = OFF;
		StringCbCopyA( ( char* )( 0x00D0C1D8 ), 32, Config->InternalProtocal );
		StringCbCopyA( ( char* )( 0x00D0C1B4 ), 32, Config->InternalProtocal );
		StringCbCopyA( ( char* )( 0x00D0C1FC ), 32, Config->InternalProtocal );
	};

	if( Config->isWide )
	{
		DWORD VP = 0;

		WriteMemory( 0x00433FB9 + 6, NULL );
		WriteMemory( 0x004340F0 + 6, NULL );
		WriteMemory( 0x004571DF + 6, NULL );
		WriteMemory( 0x00457238 + 6, NULL );
		WriteMemory( 0x00457DBA + 6, NULL );

		*( DWORD* )( 0x03511C68 ) = NULL;

		// Ajustar a visão.
		double NewDistZ = ( double )( NewConfig.Width / 4 );
		NewDistZ *= 3;
		*( DWORD* )( 0x0083F25C ) = ( DWORD )NewDistZ;
	}
	else
	{
		*( DWORD* )( 0x0083F25C ) = *( DWORD* )( 0x00D0A544 );
	};

	*( int* )( 0x00D0C1F8 ) = TCP_PORT;
	*( int* )( 0x00D0C1D4 ) = TCP_PORT;
	*( int* )( 0x00D0C21C ) = TCP_PORT;
	*( int* )( 0x00D0C240 ) = TCP_PORT;

	DWORD Time = GetTickCount( );
	DWORD XorTime = *( DWORD* )( 0x00D0C244 );
	XorTime = XorTime ^ Time;
	*( DWORD* )( 0x00A4408C ) = Time;
	*( DWORD* )( 0x00A441C0 ) = XorTime;
};

int __cdecl _ReadConfiguration( )
{
	std::shared_ptr<CWideScreen> lpWide = std::make_shared<CWideScreen>( );
	return 0x00D0A540;
};