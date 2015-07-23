#pragma once

class Main
{
public:
	LRESULT CALLBACK Proc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	static LRESULT CALLBACK s_Proc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	HWND NewWindow( DWORD dwExStyle,
					LPCSTR lpClassName,
					LPCSTR lpWindowName,
					DWORD dwStyle,
					int X,
					int Y,
					int nWidth,
					int nHeight,
					HWND hWndParent,
					HMENU hMenu,
					HINSTANCE hInstance,
					LPVOID lpParam );

private:
	HWND hMain, hButton;
};

typedef std::shared_ptr<Main> Main_ptr;

Main_ptr lpMain = std::make_shared<Main>( );