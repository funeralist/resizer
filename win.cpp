#include <windows.h>

int main() {
    constexpr int HOTKEY_ID = 1, WIDTH = 1280, HEIGHT = 720;
    
    if (!RegisterHotKey(NULL, HOTKEY_ID, MOD_CONTROL | MOD_ALT, 0x4C)) {
        return 1;
    }
    
    const int x = (GetSystemMetrics(SM_CXSCREEN) - WIDTH) / 2;
    const int y = (GetSystemMetrics(SM_CYSCREEN) - HEIGHT) / 2;

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        if (msg.message == WM_HOTKEY && msg.wParam == HOTKEY_ID)
            SetWindowPos(GetForegroundWindow(), NULL, x, y, WIDTH, HEIGHT, SWP_NOZORDER | SWP_NOACTIVATE);
        
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    
    UnregisterHotKey(NULL, HOTKEY_ID);
    return 0;
}