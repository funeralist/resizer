#include <windows.h>

const int HOTKEY_ID = 1;

// WINDOW SIZE
const int T_WIDTH = 1280;
const int T_HEIGHT = 720;

int main() {
	if (RegisterHotKey(NULL, HOTKEY_ID, MOD_CONTROL | MOD_ALT, 0x4C) == 0) 
	{
        MessageBoxW(NULL, L"Failed to register hotkey.", L"Error", MB_ICONERROR);
        return 1;
    }
	
	const int T_X = (GetSystemMetrics(SM_CXSCREEN) - T_WIDTH) / 2;
	const int T_Y = (GetSystemMetrics(SM_CYSCREEN) - T_HEIGHT) / 2;

	MSG msg;

	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		if (msg.message == WM_HOTKEY && msg.wParam == HOTKEY_ID)
		{
            SetWindowPos(GetForegroundWindow(), NULL, T_X, T_Y, T_WIDTH, T_HEIGHT, SWP_NOZORDER | SWP_NOACTIVATE);
        }
		
		TranslateMessage(&msg);
        DispatchMessage(&msg);
	}
	
	UnregisterHotKey(NULL, HOTKEY_ID);
	return 0;
}