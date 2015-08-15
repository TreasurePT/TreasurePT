#include "stdafx.h"
#include "main.h"
#include "convert_inx.h"

HWND hWnd = 0;

#define ScreenX GetSystemMetrics(SM_CXSCREEN)
#define ScreenY GetSystemMetrics(SM_CYSCREEN)

typedef HMENU COMMAND;
#define CONVERT_INX 1

#define BUTTON_A 10
#define BUTTON_B 11
#define BUTTON_C 12
#define BUTTON_D 13
#define BUTTON_MA 14
#define BUTTON_MB 15
#define BUTTON_MC 16
#define BUTTON_MD 17

LRESULT CALLBACK Main::Proc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
		// Mensagem lida ao criar a aplicação.
		case WM_CREATE:
			{
				hMain = hWnd;
				//hButton = NewWindow( NULL, "BUTTON", "Converter .inx's", WS_VISIBLE | WS_CHILD,
				//					 10, 10, 120, 30,
				//					 hWnd, ( COMMAND )( CONVERT_INX ), NULL, NULL );

				hA = NewWindow( NULL, "BUTTON", "A", WS_VISIBLE | WS_CHILD,
								10, 10, 25, 30,
								hWnd, ( COMMAND )( BUTTON_A ), NULL, NULL );

				hB = NewWindow( NULL, "BUTTON", "B", WS_VISIBLE | WS_CHILD,
								40, 10, 25, 30,
								hWnd, ( COMMAND )( BUTTON_A ), NULL, NULL );

				hC = NewWindow( NULL, "BUTTON", "C", WS_VISIBLE | WS_CHILD,
								70, 10, 25, 30,
								hWnd, ( COMMAND )( BUTTON_A ), NULL, NULL );

				hD = NewWindow( NULL, "BUTTON", "D", WS_VISIBLE | WS_CHILD,
								100, 10, 25, 30,
								hWnd, ( COMMAND )( BUTTON_A ), NULL, NULL );

				hmA = NewWindow( NULL, "BUTTON", "mA", WS_VISIBLE | WS_CHILD,
								10, 40, 25, 30,
								hWnd, ( COMMAND )( BUTTON_A ), NULL, NULL );

				hmB = NewWindow( NULL, "BUTTON", "mB", WS_VISIBLE | WS_CHILD,
								40, 40, 25, 30,
								hWnd, ( COMMAND )( BUTTON_A ), NULL, NULL );

				hmC = NewWindow( NULL, "BUTTON", "mC", WS_VISIBLE | WS_CHILD,
								70, 40, 25, 30,
								hWnd, ( COMMAND )( BUTTON_A ), NULL, NULL );

				hmD = NewWindow( NULL, "BUTTON", "mD", WS_VISIBLE | WS_CHILD,
								100, 40, 25, 30,
								hWnd, ( COMMAND )( BUTTON_A ), NULL, NULL );


			}
			break;

			// Mensagem lida ao fechar a aplicação.
		case WM_DESTROY:
			{
				PostQuitMessage( 0 );
				return 0;
			}
			break;

			//Mensagem lida ao executar um comando.
		case WM_COMMAND:
			{
				switch( LOWORD( wParam ) )
				{
					case CONVERT_INX:
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

	return DefWindowProcA( hWnd, message, wParam, lParam );
};

LRESULT CALLBACK Main::s_Proc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	return lpMain->Proc( hWnd, message, wParam, lParam );
};

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow )
{
	WNDCLASSEX wc;

	SecureZeroMemory( &wc, sizeof( WNDCLASSEX ) );

	wc.cbSize = sizeof( WNDCLASSEX );
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = lpMain->s_Proc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursorA( NULL, IDC_ARROW );
	wc.hbrBackground = ( HBRUSH )COLOR_WINDOW;
	wc.lpszClassName = "MainClass";

	RegisterClassExA( &wc );


	hWnd = CreateWindowExA( NULL, "MainClass", "Ferramentas TreasurePT",
							WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
							( ScreenX - 300 ) / 2,    // Coordenada X
							( ScreenY - 300 ) / 2,    // Coordenada Y
							400,    // Largura
							200,    // Altura
							NULL, NULL, hInstance, NULL );

	ShowWindow( hWnd, nCmdShow );
	MSG msg;

	while( TRUE )
	{
		while( PeekMessageA( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessageA( &msg );
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