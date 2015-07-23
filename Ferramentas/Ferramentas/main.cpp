#include "stdafx.h"
#include "main.h"
#include "convert_inx.h"

HWND hWnd = 0;

#define ScreenX GetSystemMetrics(SM_CXSCREEN)
#define ScreenY GetSystemMetrics(SM_CYSCREEN)

LRESULT CALLBACK Main::Proc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
		// Mensagem lida ao criar a aplicação.
		case WM_CREATE:
			{
				hMain = hWnd;
				hButton = NewWindow( NULL, "BUTTON", "Converter .inx's", WS_VISIBLE | WS_CHILD,
									 10, 10, 120, 30,
									 hWnd, ( HMENU )( 1 ), NULL, NULL );
			}
			break;

			// Mensagem lida ao fechar a aplicação.
		case WM_DESTROY:
			{
				PostQuitMessage( 0 );
				return 0;
			}
			break;

		case WM_COMMAND:
			{
				switch( LOWORD( wParam ) )
				{
					case 1:
						{
							EnableWindow( hButton, false );
							std::shared_ptr<ConvertInx> lpInx = std::make_shared<ConvertInx>( );
							MessageBoxA( hWnd, "Finalizado, verifique os Logs.", "Ferramentas", MB_OK );
							EnableWindow( hButton, true );
						}
						break;

				};

			}
			break;
	}

	return DefWindowProc( hWnd, message, wParam, lParam );
};

LRESULT CALLBACK Main::s_Proc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	return lpMain->Proc( hWnd, message, wParam, lParam );
};

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow )
{
	WNDCLASSEX wc;

	ZeroMemory( &wc, sizeof( WNDCLASSEX ) );

	wc.cbSize = sizeof( WNDCLASSEX );
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = lpMain->s_Proc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = ( HBRUSH )COLOR_WINDOW;
	wc.lpszClassName = "MainClass";

	RegisterClassEx( &wc );


	hWnd = CreateWindowEx( NULL, "MainClass", "Ferramentas TreasurePT",
						   WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
						   ( ScreenX - 300 ) / 2,    // Coordenada X
						   ( ScreenY - 300 ) / 2,    // Coordenada Y
						   300,    // Largura
						   100,    // Altura
						   NULL, NULL, hInstance, NULL );

	ShowWindow( hWnd, nCmdShow );
	MSG msg;

	while( TRUE )
	{
		while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		};

		if( msg.message == WM_QUIT )
			break;


	};

	return msg.wParam;
};

HWND Main::NewWindow( DWORD dwExStyle,
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
					  LPVOID lpParam )
{
	hWnd = CreateWindowExA( dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu,
							hInstance, lpParam );
	MoveWindow( hWnd, X, Y, nWidth, nHeight, true );
	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );
	return hWnd;
};