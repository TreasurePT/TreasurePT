#pragma once

#define LOW 3
#define MEDIUM 2
#define HIGH 1
#define VERYHIGH 0

#define ON 0
#define OFF 1

#define _NEAR 1
#define _FAR 0

class CWideScreen
{
private:
	struct s_Config
	{
		int Width;
		int Height;
		char FullScreen[ 16 ];
		char Graphics[ 16 ];
		int ColorDepth;
		char CammInvert[ 32 ];
		char CammFog[ 16 ];
		char Sound[ 16 ];
		char InternalProtocal[ 32 ];
		bool isWide;
	};

	struct s_NewConfig
	{
		int Width;
		int Height;
		int FullScreen;
		int Graphics;
		int ColorDepth;
		int CammInvert;
		int CammFog;
		int Sound;
		bool isWide;
	} NewConfig;

public:
	CWideScreen( );

	void DefaultConfig( s_Config* Config, bool CreateIni = false );
	void ReadConfig( s_Config* Config );
	bool CheckConfig( s_Config* Config );
	void SetConfig( s_Config* Config );
};