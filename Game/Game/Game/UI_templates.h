#pragma once
class CUITemplates
{
private:
	typedef int( __cdecl* t_TextOut ) ( HDC DeviceHandle, int PosiX, int PosiY,
										const char* Text, int Length );
	typedef void( __cdecl* t_SetGameError )( int Error );
public:

protected:
	t_TextOut ShowTextA = ( t_TextOut )0x00409C50;
	t_SetGameError SetGameError = ( t_SetGameError )0x005891D0;
private:
};