#pragma once
class Settings
{
public:
	Settings( );
	void Read( );
	void Write( );
	void CreateIni( );

protected:

private:
	struct s_Settings
	{
		bool WindowMode;
		int Width;
		int Height;
		int Bpp;
		int Quality;
		bool Blur;
		bool Distance;
		bool Inverted;
		bool Sound;
		bool isWide;
		char Macro[ 10 ][ 256 ];
		bool isGm;
	} Setting;

	bool FileExists;

};